/*
 * Восстановленная работа с DirectSound в эмуляторе SPU.
 * Вместо сырых указателей и вызовов по смещениям vtbl используются
 * стандартные COM-интерфейсы IDirectSound и IDirectSoundBuffer.
 *
 * Переименованы все глобальные переменные, связанные с аудиобуфером.
 */

#include <windows.h>
#include <dsound.h>
#include <stdio.h>

// Глобальные объекты DirectSound
static LPDIRECTSOUND        g_pDS = NULL;           // бывший ppDS
static LPDIRECTSOUNDBUFFER  g_pDSBuffer = NULL;    // бывший dword_45B8FC

// Параметры звукового буфера (устанавливаются в spu_dsound_init)
static int audio_sample_rate_mode;      // бывший dword_44F710 (0..6)
static int audio_stereo_flag;           // бывший dword_44F714 (0=моно, 1=стерео)
static int audio_buffer_size_bytes;     // бывший dword_44F708 (размер в байтах)
static int audio_buffer_delay;          // бывший dword_44F70C (не используется)

// Состояние буфера вывода
static int buffer_write_pos;            // бывший dword_4F7598 (текущая позиция записи в байтах)
static int mute_flag;                   // бывший dword_4F7594 (если !=0, выводим тишину)
static int update_pending;              // бывший dword_4F75A0 (1 = идёт обработка, 0 = готов)
static int update_counter;              // бывший dword_4F75A4 (счётчик задержки обновления)

// Вспомогательные буферы для передачи данных в звуковой буфер
static unsigned char temp_samples[512]; // бывший byte_463910 (256 сэмплов * 2 байта = 512 байт)
static void *lock_ptr1;                 // бывший dword_463908
static DWORD lock_size1;                // бывший dword_4F7590
static void *lock_ptr2;                 // бывший dword_46390C
static DWORD lock_size2;                // бывший dword_4F758C

// Внешние зависимости
extern HWND hOutputWnd;                 // окно для кооперативного уровня
extern void spu_generate_samples(void); // бывший sub_40C8B0 (заполняет byte_4F7150)
extern unsigned char output_buffer[];   // бывший byte_4F7150 (выходной буфер эмулятора)

// === Инициализация DirectSound (бывший spucore_init_dsound) ===
static int spu_dsound_init(void)
{
    HRESULT hr;
    DSBUFFERDESC dsbd;
    WAVEFORMATEX wfx;
    int sample_rate;

    // Создаём объект DirectSound
    if (DirectSoundCreate(NULL, &g_pDS, NULL) != DS_OK)
        return 0;

    // Устанавливаем кооперативный уровень (приоритетный)
    if (g_pDS->SetCooperativeLevel(hOutputWnd, DSSCL_PRIORITY) != DS_OK)
        return 0;

    // Определяем параметры буфера в зависимости от выбранного режима
    // (режим задаётся через dword_44F710, который устанавливается вне этой функции)
    switch (audio_sample_rate_mode)
    {
        case 0: audio_buffer_size_bytes = 2048; sample_rate = 8000;  break;
        case 1: audio_buffer_size_bytes = 2048; sample_rate = 11025; break;
        case 2: audio_buffer_size_bytes = 4096; sample_rate = 22050; break;
        case 3: audio_buffer_size_bytes = 8192; sample_rate = 44100; break;
        case 4: audio_buffer_size_bytes = 4096; sample_rate = 16000; break;
        case 5: audio_buffer_size_bytes = 8192; sample_rate = 32000; break;
        case 6: audio_buffer_size_bytes = 8192; sample_rate = 48000; break;
        default: audio_buffer_size_bytes = 2048; sample_rate = 11025; break;
    }

    // Если стерео – удваиваем размер буфера (так как данных в 2 раза больше)
    if (audio_stereo_flag)
        audio_buffer_size_bytes *= 2;

    // Заполняем структуру WAVEFORMATEX
    ZeroMemory(&wfx, sizeof(wfx));
    wfx.wFormatTag      = WAVE_FORMAT_PCM;
    wfx.nChannels       = audio_stereo_flag ? 2 : 1;
    wfx.nSamplesPerSec  = sample_rate;
    wfx.wBitsPerSample  = 16;
    wfx.nBlockAlign     = wfx.nChannels * wfx.wBitsPerSample / 8;
    wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;

    // Заполняем описание буфера
    ZeroMemory(&dsbd, sizeof(dsbd));
    dsbd.dwSize          = sizeof(DSBUFFERDESC);
    dsbd.dwFlags         = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY;
    dsbd.dwBufferBytes   = audio_buffer_size_bytes;
    dsbd.lpwfxFormat     = &wfx;
    dsbd.dwReserved      = 0;

    // Создаём звуковой буфер
    if (g_pDS->CreateSoundBuffer(&dsbd, &g_pDSBuffer, NULL) != DS_OK)
        return 0;

    // Запускаем воспроизведение с зацикливанием (флаг DSBPLAY_LOOPING = 1)
    if (g_pDSBuffer->Play(0, 0, DSBPLAY_LOOPING) != DS_OK)
        return 0;

    audio_buffer_delay = 0;
    return 1;
}

// === Обновление буфера DirectSound (бывший spucore_update_dsound) ===
static int spu_update_buffer(void)
{
    // Если идёт обработка задержки (update_pending == 1) – просто считаем такты
    if (update_pending)
    {
        update_counter++;
        update_pending = (update_counter <= 0x40); // задержка ~64 вызова
        return 0;
    }
    else
    {
        update_counter = 0;

        // Получаем текущие позиции воспроизведения и записи
        DWORD play_pos, write_pos;
        if (g_pDSBuffer->GetCurrentPosition(&play_pos, &write_pos) != DS_OK)
            return 0;

        // Вычисляем, сколько байт можно записать в буфер (без перекрытия с play_pos)
        int bytes_available;
        if (buffer_write_pos > play_pos)
            bytes_available = play_pos + audio_buffer_size_bytes - buffer_write_pos;
        else
            bytes_available = play_pos - buffer_write_pos;

        // Обрабатываем блоками по 256 байт
        while (bytes_available >= 256)
        {
            if (update_pending)
                break;

            // Генерируем новые сэмплы (функция заполняет глобальный буфер output_buffer)
            // В оригинале здесь вызывалась sub_40C8B0 (spu_generate_samples)
            spu_generate_samples();

            // Копируем из output_buffer в temp_samples с клиппингом и учётом mute_flag
            // (в оригинале был цикл do-while, копировались пары 16-битных значений)
            for (int i = 0; i < 256; i++)
            {
                int sample = *(short*)(output_buffer + i*2);
                if (mute_flag)
                    sample = 0;
                if (sample > 32767) sample = 32767;
                if (sample < -32767) sample = -32767;
                ((short*)temp_samples)[i] = (short)sample;
            }

            // Блокируем часть буфера DirectSound для записи
            LPVOID ptr1, ptr2;
            DWORD size1, size2;
            if (g_pDSBuffer->Lock(buffer_write_pos, 256, &ptr1, &size1, &ptr2, &size2, 0) == DS_OK)
            {
                // Копируем данные в полученные области
                memcpy(ptr1, temp_samples, size1);
                if (ptr2 && size2)
                    memcpy(ptr2, temp_samples + size1, size2);

                // Разблокируем буфер
                g_pDSBuffer->Unlock(ptr1, size1, ptr2, size2);
            }

            // Сдвигаем позицию записи
            buffer_write_pos += 256;
            if (buffer_write_pos >= audio_buffer_size_bytes)
                buffer_write_pos = 0;

            bytes_available -= 256;
        }
    }
    return 0;
}

// === Остановка и освобождение ресурсов (бывший spucore_destroy) ===
static int spu_dsound_destroy(void)
{
    if (g_pDSBuffer)
    {
        g_pDSBuffer->Stop();
        // Ждём, пока буфер действительно остановится (проверка статуса)
        DWORD status;
        while (g_pDSBuffer->GetStatus(&status) == DS_OK && (status & DSBSTATUS_PLAYING))
            Sleep(1);
        g_pDSBuffer->Release();
        g_pDSBuffer = NULL;
    }
    if (g_pDS)
    {
        g_pDS->Release();
        g_pDS = NULL;
    }
    return 0;
}

// Экспортируемые функции (обёртки)
int spucore_init_dsound(void) { return spu_dsound_init(); }
int spucore_update_dsound(void) { return spu_update_buffer(); }
int spucore_destroy_dsound(void) { return spu_dsound_destroy(); }