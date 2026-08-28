// zip_test.cpp : unit tests for the ZIP archive reader module (src/zip.c).
//
// The module under test is plain C (decompiled from the original ePSXe 1.6.0);
// these tests drive its public API (zip_extract_file / zip_load_file) against
// real ZIP archives generated on the fly (stored and deflated entries), plus
// the usual error cases (missing file, not a zip, empty archive, entry not
// found).  Deflated entries are produced with the zlib deflate in raw mode,
// which is what the module's own inflate implementation must decode.
//
// Test archives are written to the system temp directory and removed after
// each test.

#include "pch.h"
#include "CppUnitTest.h"

#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <string>
#include <vector>

// The module under test is plain C; declare its API with C linkage so the
// C++ test code links against the C objects (no name mangling).
extern "C" {
#include "../../src/zip.h"
#include "../../src/loader.h"       // zip_entry_names / zip_num_entries_loaded
#include "../../src/spu_plugin.h"   // Size[]
}
#include "../../zlib-1.1.3/zlib.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
    namespace
    {
        struct TestZipEntry
        {
            std::string name;
            std::vector<uint8_t> data;
            uint16_t method;    // 0 = stored, 8 = deflated
        };

        void put16(std::vector<uint8_t> &v, uint16_t x)
        {
            v.push_back((uint8_t)(x & 0xFF));
            v.push_back((uint8_t)(x >> 8));
        }

        void put32(std::vector<uint8_t> &v, uint32_t x)
        {
            v.push_back((uint8_t)(x & 0xFF));
            v.push_back((uint8_t)((x >> 8) & 0xFF));
            v.push_back((uint8_t)((x >> 16) & 0xFF));
            v.push_back((uint8_t)((x >> 24) & 0xFF));
        }

        // Raw DEFLATE (no zlib/gzip wrapper) via zlib's deflateInit2.
        std::vector<uint8_t> rawDeflate(const std::vector<uint8_t> &input)
        {
            z_stream zs;
            memset(&zs, 0, sizeof(zs));
            if (deflateInit2(&zs, Z_DEFAULT_COMPRESSION, Z_DEFLATED, -MAX_WBITS, 8, Z_DEFAULT_STRATEGY) != Z_OK)
                return std::vector<uint8_t>();

            std::vector<uint8_t> out(input.size() + (input.size() >> 2) + 1024);
            zs.next_in = const_cast<Bytef *>(input.data());
            zs.avail_in = (uInt)input.size();
            zs.next_out = out.data();
            zs.avail_out = (uInt)out.size();
            int ret = deflate(&zs, Z_FINISH);
            size_t produced = out.size() - zs.avail_out;
            deflateEnd(&zs);
            if (ret != Z_STREAM_END)
                return std::vector<uint8_t>();
            out.resize(produced);
            return out;
        }

        // Builds a complete ZIP archive (local headers + data + central
        // directory + end-of-central-directory record).
        std::vector<uint8_t> buildZip(const std::vector<TestZipEntry> &entries)
        {
            std::vector<uint8_t> local;
            std::vector<uint8_t> central;
            uint32_t offset = 0;

            for (size_t e = 0; e < entries.size(); ++e)
            {
                const TestZipEntry &entry = entries[e];
                std::vector<uint8_t> comp = (entry.method == 8) ? rawDeflate(entry.data) : entry.data;
                uint32_t crc = crc32(0L, entry.data.data(), (uInt)entry.data.size());
                Assert::IsFalse(comp.empty());

                // Local file header + name + data
                put32(local, ZIP_LOCAL_FILE_HEADER_SIG);
                put16(local, 20);                       // version needed (2.0)
                put16(local, 0);                        // general purpose bit flag
                put16(local, entry.method);
                put16(local, 0);                        // last mod time
                put16(local, 0);                        // last mod date
                put32(local, crc);
                put32(local, (uint32_t)comp.size());
                put32(local, (uint32_t)entry.data.size());
                put16(local, (uint16_t)entry.name.size());
                put16(local, 0);                        // extra field length
                local.insert(local.end(), entry.name.begin(), entry.name.end());
                local.insert(local.end(), comp.begin(), comp.end());

                // Central directory entry + name
                put32(central, ZIP_CENTRAL_DIR_HEADER_SIG);
                put16(central, 20);                     // version made by (OS 0)
                put16(central, 20);                     // version needed (2.0)
                put16(central, 0);                      // general purpose bit flag
                put16(central, entry.method);
                put16(central, 0);                      // last mod time
                put16(central, 0);                      // last mod date
                put32(central, crc);
                put32(central, (uint32_t)comp.size());
                put32(central, (uint32_t)entry.data.size());
                put16(central, (uint16_t)entry.name.size());
                put16(central, 0);                      // extra field length
                put16(central, 0);                      // file comment length
                put16(central, 0);                      // disk number start
                put16(central, 0);                      // internal attributes
                put32(central, 0);                      // external attributes
                put32(central, offset);                 // local header offset
                central.insert(central.end(), entry.name.begin(), entry.name.end());

                offset += (uint32_t)(30 + entry.name.size() + comp.size());
            }

            std::vector<uint8_t> zip = local;
            uint32_t cd_offset = (uint32_t)local.size();
            zip.insert(zip.end(), central.begin(), central.end());
            put32(zip, ZIP_END_OF_CD_SIGNATURE);
            put16(zip, 0);                              // disk number
            put16(zip, 0);                              // cd start disk
            put16(zip, (uint16_t)entries.size());       // entries on this disk
            put16(zip, (uint16_t)entries.size());       // total entries
            put32(zip, (uint32_t)central.size());
            put32(zip, cd_offset);
            put16(zip, 0);                              // comment length
            return zip;
        }

        // Writes the archive to the temp directory; returns the file name.
        std::string writeTempZip(int id, const std::vector<uint8_t> &bytes)
        {
            char dir[MAX_PATH];
            char path[MAX_PATH];
            DWORD len = GetTempPathA(MAX_PATH, dir);
            Assert::IsTrue(len > 0 && len < MAX_PATH);
            sprintf_s(path, "%szip_ut_%lu_%d.zip", dir, GetCurrentProcessId(), id);
            FILE *f = fopen(path, "wb");
            Assert::IsNotNull((void *)f);
            fwrite(bytes.data(), 1, bytes.size(), f);
            fclose(f);
            return std::string(path);
        }

        void removeTempZip(const std::string &path)
        {
            if (!path.empty())
                DeleteFileA(path.c_str());
        }

        std::vector<uint8_t> makeRepeatedPattern(size_t size)
        {
            std::vector<uint8_t> data;
            data.reserve(size);
            static const char *pattern = "ePSXe ZIP unit test payload 0123456789 ";
            size_t plen = strlen(pattern);
            for (size_t i = 0; i < size; ++i)
                data.push_back((uint8_t)pattern[i % plen]);
            return data;
        }

        std::vector<uint8_t> makePseudoRandom(size_t size)
        {
            std::vector<uint8_t> data;
            data.reserve(size);
            uint32_t x = 0x12345678;
            for (size_t i = 0; i < size; ++i)
            {
                x = x * 1664525u + 1013904223u;
                data.push_back((uint8_t)(x >> 24));
            }
            return data;
        }
    }

    TEST_CLASS(ZipTest)
    {
    public:
        TEST_METHOD_INITIALIZE(ResetZipState)
        {
            zip_num_entries_loaded = 0;
        }

        // ------------------------------------------------------------------
        // zip_load_file()
        // ------------------------------------------------------------------

        TEST_METHOD(LoadFile_LoadsStoredAndDeflatedEntries)
        {
            std::vector<TestZipEntry> entries;
            TestZipEntry stored;
            stored.name = "demo.exe";
            stored.data = makeRepeatedPattern(4096);
            stored.method = 0;
            TestZipEntry deflated;
            deflated.name = "readme.txt";
            deflated.data = makeRepeatedPattern(5000);
            deflated.method = 8;
            entries.push_back(stored);
            entries.push_back(deflated);

            std::string path = writeTempZip(0, buildZip(entries));
            try
            {
                Assert::AreEqual(0, zip_load_file((char *)path.c_str()));
                Assert::AreEqual((unsigned int)2, zip_num_entries_loaded);
                Assert::AreEqual(std::string("DEMO.EXE"), std::string((char *)&zip_entry_names[0]));
                Assert::AreEqual(std::string("README.TXT"), std::string((char *)&zip_entry_names[256]));
                Assert::AreEqual((unsigned int)stored.data.size(), Size[0]);
                Assert::AreEqual((unsigned int)deflated.data.size(), Size[1]);
            }
            catch (...)
            {
                removeTempZip(path);
                throw;
            }
            removeTempZip(path);
        }

        TEST_METHOD(LoadFile_EntryNamesAreUpperCased)
        {
            std::vector<TestZipEntry> entries;
            TestZipEntry e;
            e.name = "SubDir/My_Game.exe";
            e.data = makeRepeatedPattern(100);
            e.method = 0;
            entries.push_back(e);

            std::string path = writeTempZip(1, buildZip(entries));
            try
            {
                Assert::AreEqual(0, zip_load_file((char *)path.c_str()));
                Assert::AreEqual((unsigned int)1, zip_num_entries_loaded);
                Assert::AreEqual(std::string("SUBDIR/MY_GAME.EXE"), std::string((char *)&zip_entry_names[0]));
            }
            catch (...)
            {
                removeTempZip(path);
                throw;
            }
            removeTempZip(path);
        }

        TEST_METHOD(LoadFile_MissingArchive)
        {
            Assert::AreNotEqual(0, zip_load_file((char *)"Z:\\no_such_archive_34.zip"));
        }

        TEST_METHOD(LoadFile_NotAZip)
        {
            char path[MAX_PATH];
            char dir[MAX_PATH];
            GetTempPathA(MAX_PATH, dir);
            sprintf_s(path, "%szip_ut_notazip_%lu.txt", dir, GetCurrentProcessId());
            FILE *f = fopen(path, "wb");
            Assert::IsNotNull((void *)f);
            fwrite("this is definitely not a zip archive\n", 1, 38, f);
            fclose(f);
            Assert::AreNotEqual(0, zip_load_file(path));
            DeleteFileA(path);
        }

        TEST_METHOD(LoadFile_EmptyArchive)
        {
            std::string path = writeTempZip(2, buildZip(std::vector<TestZipEntry>()));
            try
            {
                Assert::AreNotEqual(0, zip_load_file((char *)path.c_str()));
                Assert::AreEqual((unsigned int)0, zip_num_entries_loaded);
            }
            catch (...)
            {
                removeTempZip(path);
                throw;
            }
            removeTempZip(path);
        }

        // ------------------------------------------------------------------
        // zip_extract_file()
        // ------------------------------------------------------------------

        TEST_METHOD(ExtractFile_StoredEntry)
        {
            std::vector<TestZipEntry> entries;
            TestZipEntry e;
            e.name = "stored.bin";
            e.data = makeRepeatedPattern(20000);    // > 8 KB read buffer
            e.method = 0;
            entries.push_back(e);

            std::string path = writeTempZip(3, buildZip(entries));
            try
            {
                LPVOID data = NULL;
                size_t size = 0;
                Assert::AreEqual(0, zip_extract_file((char *)path.c_str(), (char *)"stored.bin", &data, &size));
                Assert::IsNotNull(data);
                Assert::AreEqual(e.data.size(), size);
                Assert::AreEqual(0, memcmp(e.data.data(), data, e.data.size()));
                free(data);
            }
            catch (...)
            {
                removeTempZip(path);
                throw;
            }
            removeTempZip(path);
        }

        TEST_METHOD(ExtractFile_DeflatedEntry)
        {
            // > 32 KB of highly compressible data: exercises dynamic Huffman
            // blocks, long matches, sliding window flushes and large distances.
            std::vector<TestZipEntry> entries;
            TestZipEntry e;
            e.name = "game.exe";
            e.data = makeRepeatedPattern(100000);
            e.method = 8;
            entries.push_back(e);

            std::string path = writeTempZip(4, buildZip(entries));
            try
            {
                LPVOID data = NULL;
                size_t size = 0;
                Assert::AreEqual(0, zip_extract_file((char *)path.c_str(), (char *)"game.exe", &data, &size));
                Assert::IsNotNull(data);
                Assert::AreEqual(e.data.size(), size);
                Assert::AreEqual(0, memcmp(e.data.data(), data, e.data.size()));
                free(data);
            }
            catch (...)
            {
                removeTempZip(path);
                throw;
            }
            removeTempZip(path);
        }

        TEST_METHOD(ExtractFile_DeflatedIncompressibleData)
        {
            // Pseudo-random data: zlib emits stored blocks inside the
            // DEFLATE stream, exercising the stored-block path of the decoder.
            std::vector<TestZipEntry> entries;
            TestZipEntry e;
            e.name = "random.bin";
            e.data = makePseudoRandom(50000);
            e.method = 8;
            entries.push_back(e);

            std::string path = writeTempZip(5, buildZip(entries));
            try
            {
                LPVOID data = NULL;
                size_t size = 0;
                Assert::AreEqual(0, zip_extract_file((char *)path.c_str(), (char *)"random.bin", &data, &size));
                Assert::IsNotNull(data);
                Assert::AreEqual(e.data.size(), size);
                Assert::AreEqual(0, memcmp(e.data.data(), data, e.data.size()));
                free(data);
            }
            catch (...)
            {
                removeTempZip(path);
                throw;
            }
            removeTempZip(path);
        }

        TEST_METHOD(ExtractFile_CaseInsensitiveName)
        {
            std::vector<TestZipEntry> entries;
            TestZipEntry e;
            e.name = "demo.exe";
            e.data = makeRepeatedPattern(1024);
            e.method = 8;
            entries.push_back(e);

            std::string path = writeTempZip(6, buildZip(entries));
            try
            {
                LPVOID data = NULL;
                size_t size = 0;
                Assert::AreEqual(0, zip_extract_file((char *)path.c_str(), (char *)"DEMO.EXE", &data, &size));
                Assert::IsNotNull(data);
                Assert::AreEqual(e.data.size(), size);
                free(data);
            }
            catch (...)
            {
                removeTempZip(path);
                throw;
            }
            removeTempZip(path);
        }

        TEST_METHOD(ExtractFile_MatchesFinalPathComponent)
        {
            // Archive entry carries a directory prefix; the module matches
            // the final path component.
            std::vector<TestZipEntry> entries;
            TestZipEntry e;
            e.name = "demos/race/game.exe";
            e.data = makeRepeatedPattern(2048);
            e.method = 0;
            entries.push_back(e);

            std::string path = writeTempZip(7, buildZip(entries));
            try
            {
                LPVOID data = NULL;
                size_t size = 0;
                Assert::AreEqual(0, zip_extract_file((char *)path.c_str(), (char *)"GAME.EXE", &data, &size));
                Assert::IsNotNull(data);
                Assert::AreEqual(e.data.size(), size);
                free(data);
            }
            catch (...)
            {
                removeTempZip(path);
                throw;
            }
            removeTempZip(path);
        }

        TEST_METHOD(ExtractFile_EntryNotFound)
        {
            std::vector<TestZipEntry> entries;
            TestZipEntry e;
            e.name = "demo.exe";
            e.data = makeRepeatedPattern(64);
            e.method = 0;
            entries.push_back(e);

            std::string path = writeTempZip(8, buildZip(entries));
            try
            {
                LPVOID data = NULL;
                size_t size = 0;
                Assert::AreNotEqual(0, zip_extract_file((char *)path.c_str(), (char *)"missing.exe", &data, &size));
                Assert::IsNull(data);
            }
            catch (...)
            {
                removeTempZip(path);
                throw;
            }
            removeTempZip(path);
        }

        TEST_METHOD(ExtractFile_MissingArchive)
        {
            LPVOID data = NULL;
            size_t size = 0;
            Assert::AreNotEqual(0, zip_extract_file((char *)"Z:\\no_such_archive_34.zip", (char *)"x.exe", &data, &size));
            Assert::IsNull(data);
        }

        TEST_METHOD(ExtractFile_NotAZip)
        {
            char path[MAX_PATH];
            char dir[MAX_PATH];
            GetTempPathA(MAX_PATH, dir);
            sprintf_s(path, "%szip_ut_notazip2_%lu.bin", dir, GetCurrentProcessId());
            FILE *f = fopen(path, "wb");
            Assert::IsNotNull((void *)f);
            std::vector<uint8_t> junk = makePseudoRandom(1000);
            fwrite(junk.data(), 1, junk.size(), f);
            fclose(f);

            LPVOID data = NULL;
            size_t size = 0;
            Assert::AreNotEqual(0, zip_extract_file(path, (char *)"x.exe", &data, &size));
            Assert::IsNull(data);
            DeleteFileA(path);
        }

        TEST_METHOD(ExtractFile_EmptyArchive)
        {
            std::string path = writeTempZip(9, buildZip(std::vector<TestZipEntry>()));
            try
            {
                LPVOID data = NULL;
                size_t size = 0;
                Assert::AreNotEqual(0, zip_extract_file((char *)path.c_str(), (char *)"x.exe", &data, &size));
                Assert::IsNull(data);
            }
            catch (...)
            {
                removeTempZip(path);
                throw;
            }
            removeTempZip(path);
        }
    };
}
