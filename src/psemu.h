#pragma once

// header version
#define _PPDK_HEADER_VERSION		3

#define PLUGIN_VERSION				1

// plugin type returned by PSEgetLibType (types can be merged if plugin is multi type!)
#define PSE_LT_CDR					1
#define PSE_LT_GPU					2
#define PSE_LT_SPU					4
#define PSE_LT_PAD					8
#define PSE_LT_NET					16
#define PSE_LT_SIO1					32

// DLL function return codes
#define PSE_ERR_SUCCESS				0	// every function in DLL if completed sucessfully should return this value
#define PSE_ERR_FATAL				-1	// undefined error but fatal one, that kills all functionality

// XXX_Init return values
// Those return values apply to all libraries
// currently obsolete - preserved for compatibilty

#define PSE_INIT_ERR_SUCCESS		0	// initialization went OK
#define PSE_INIT_ERR_NOTCONFIGURED	-2	// this driver is not configured
#define PSE_INIT_ERR_NOHARDWARE		-3	// this driver can not operate properly on this hardware or hardware is not detected

/* Modes bits for NETsendData/NETrecvData */
#define PSE_NET_BLOCKING	0x00000000
#define PSE_NET_NONBLOCKING	0x00000001

typedef unsigned long (CALLBACK* PSEgetLibType)(void);
typedef unsigned long (CALLBACK* PSEgetLibVersion)(void);
typedef char *(CALLBACK* PSEgetLibName)(void);

typedef long (CALLBACK* GPUopen)(HWND);
typedef long (CALLBACK* SPUopen)(HWND);
typedef long (CALLBACK* PADopen)(HWND);
typedef long (CALLBACK* NETopen)(HWND);
typedef long (CALLBACK* SIO1open)(HWND);

// GPU Functions
typedef long (CALLBACK* GPUinit)(void);
typedef long (CALLBACK* GPUshutdown)(void);
typedef long (CALLBACK* GPUclose)(void);
typedef void (CALLBACK* GPUwriteStatus)(uint32_t);
typedef void (CALLBACK* GPUwriteData)(uint32_t);
typedef void (CALLBACK* GPUwriteDataMem)(uint32_t *, int);
typedef uint32_t (CALLBACK* GPUreadStatus)(void);
typedef uint32_t (CALLBACK* GPUreadData)(void);
typedef void (CALLBACK* GPUreadDataMem)(uint32_t *, int);
typedef long (CALLBACK* GPUdmaChain)(uint32_t *,uint32_t);
typedef void (CALLBACK* GPUupdateLace)(void);
typedef long (CALLBACK* GPUconfigure)(void);
typedef long (CALLBACK* GPUtest)(void);
typedef void (CALLBACK* GPUabout)(void);
typedef void (CALLBACK* GPUmakeSnapshot)(void);
typedef void (CALLBACK* GPUkeypressed)(int);
typedef void (CALLBACK* GPUdisplayText)(char *);
typedef struct {
	uint32_t ulFreezeVersion;
	uint32_t ulStatus;
	uint32_t ulControl[256];
	unsigned char psxVRam[1024*512*2];
} GPUFreeze_t;
typedef long (CALLBACK* GPUfreeze)(uint32_t, GPUFreeze_t *);
typedef long (CALLBACK* GPUgetScreenPic)(unsigned char *);
typedef long (CALLBACK* GPUshowScreenPic)(unsigned char *);
typedef void (CALLBACK* GPUclearDynarec)(void (CALLBACK *callback)(void));
typedef void (CALLBACK* GPUhSync)(int);
typedef void (CALLBACK* GPUvBlank)(int);
typedef void (CALLBACK* GPUvisualVibration)(uint32_t, uint32_t);
typedef void (CALLBACK* GPUcursor)(int, int, int);
typedef void (CALLBACK* GPUaddVertex)(short,short,int64_t, int64_t, int64_t);
typedef void (CALLBACK* GPUsetSpeed)(float); // 1.0 = natural speed

// CD-ROM Functions
typedef long (CALLBACK* CDRinit)(void);
typedef long (CALLBACK* CDRshutdown)(void);
typedef long (CALLBACK* CDRopen)(void);
typedef long (CALLBACK* CDRclose)(void);
typedef long (CALLBACK* CDRgetTN)(unsigned char *);
typedef long (CALLBACK* CDRgetTD)(unsigned char, unsigned char *);
typedef long (CALLBACK* CDRreadTrack)(unsigned char *);
typedef unsigned char* (CALLBACK* CDRgetBuffer)(void);
typedef unsigned char* (CALLBACK* CDRgetBufferSub)(void);
typedef long (CALLBACK* CDRconfigure)(void);
typedef long (CALLBACK* CDRtest)(void);
typedef void (CALLBACK* CDRabout)(void);
typedef long (CALLBACK* CDRplay)(unsigned char *);
typedef long (CALLBACK* CDRstop)(void);
typedef long (CALLBACK* CDRsetfilename)(char *);
struct CdrStat {
	uint32_t Type;
	uint32_t Status;
	unsigned char Time[3];
};
typedef long (CALLBACK* CDRgetStatus)(struct CdrStat *);
typedef char* (CALLBACK* CDRgetDriveLetter)(void);
struct SubQ {
	char res0[12];
	unsigned char ControlAndADR;
	unsigned char TrackNumber;
	unsigned char IndexNumber;
	unsigned char TrackRelativeAddress[3];
	unsigned char Filler;
	unsigned char AbsoluteAddress[3];
	unsigned char CRC[2];
	char res1[72];
};
typedef long (CALLBACK* CDRreadCDDA)(unsigned char, unsigned char, unsigned char, unsigned char *);
typedef long (CALLBACK* CDRgetTE)(unsigned char, unsigned char *, unsigned char *, unsigned char *);

// SPU Functions
#if 0
typedef long (CALLBACK* SPUinit)(void);
typedef long (CALLBACK* SPUshutdown)(void);
typedef long (CALLBACK* SPUclose)(void);
typedef void (CALLBACK* SPUplaySample)(unsigned char);
typedef void (CALLBACK* SPUwriteRegister)(unsigned long, unsigned short);
typedef unsigned short (CALLBACK* SPUreadRegister)(unsigned long);
typedef void (CALLBACK* SPUwriteDMA)(unsigned short);
typedef unsigned short (CALLBACK* SPUreadDMA)(void);
typedef void (CALLBACK* SPUwriteDMAMem)(unsigned short *, int);
typedef void (CALLBACK* SPUreadDMAMem)(unsigned short *, int);
typedef void (CALLBACK* SPUplayADPCMchannel)(xa_decode_t *);
typedef void (CALLBACK* SPUregisterCallback)(void (CALLBACK *callback)(void));
typedef long (CALLBACK* SPUconfigure)(void);
typedef long (CALLBACK* SPUtest)(void);
typedef void (CALLBACK* SPUabout)(void);
typedef struct {
	unsigned char PluginName[8];
	uint32_t PluginVersion;
	uint32_t Size;
	unsigned char SPUPorts[0x200];
	unsigned char SPURam[0x80000];
	xa_decode_t xa;
	unsigned char *SPUInfo;
} SPUFreeze_t;
typedef long (CALLBACK* SPUfreeze)(uint32_t, SPUFreeze_t *);
typedef void (CALLBACK* SPUasync)(uint32_t);
typedef void (CALLBACK* SPUplayCDDAchannel)(short *, int);
#endif

// PAD Functions
#if 0
typedef long (CALLBACK* PADconfigure)(void);
typedef void (CALLBACK* PADabout)(void);
typedef long (CALLBACK* PADinit)(long);
typedef long (CALLBACK* PADshutdown)(void);
typedef long (CALLBACK* PADtest)(void);
typedef long (CALLBACK* PADclose)(void);
typedef long (CALLBACK* PADquery)(void);
typedef long (CALLBACK* PADreadPort1)(PadDataS*);
typedef long (CALLBACK* PADreadPort2)(PadDataS*);
typedef long (CALLBACK* PADkeypressed)(void);
typedef unsigned char (CALLBACK* PADstartPoll)(int);
typedef unsigned char (CALLBACK* PADpoll)(unsigned char);
#endif
typedef void (CALLBACK* PADsetSensitive)(int);
typedef void (CALLBACK* PADregisterVibration)(void (CALLBACK *callback)(uint32_t, uint32_t));
typedef void (CALLBACK* PADregisterCursor)(void (CALLBACK *callback)(int, int, int));

// NET Functions
typedef long (CALLBACK* NETinit)(void);
typedef long (CALLBACK* NETshutdown)(void);
typedef long (CALLBACK* NETclose)(void);
typedef long (CALLBACK* NETconfigure)(void);
typedef long (CALLBACK* NETtest)(void);
typedef void (CALLBACK* NETabout)(void);
typedef void (CALLBACK* NETpause)(void);
typedef void (CALLBACK* NETresume)(void);
typedef long (CALLBACK* NETqueryPlayer)(void);
typedef long (CALLBACK* NETsendData)(void *, int, int);
typedef long (CALLBACK* NETrecvData)(void *, int, int);
typedef long (CALLBACK* NETsendPadData)(void *, int);
typedef long (CALLBACK* NETrecvPadData)(void *, int);

typedef struct {
	char EmuName[32];
	char CdromID[9];	// ie. 'SCPH12345', no \0 trailing character
	char CdromLabel[11];
	void *psxMem;
	GPUshowScreenPic GPU_showScreenPic;
	GPUdisplayText GPU_displayText;
	PADsetSensitive PAD_setSensitive;
	char GPUpath[256];	// paths must be absolute
	char SPUpath[256];
	char CDRpath[256];
	char MCD1path[256];
	char MCD2path[256];
	char BIOSpath[256];	// 'HLE' for internal bios
	char Unused[1024];
} netInfo;

typedef long (CALLBACK* NETsetInfo)(netInfo *);
typedef long (CALLBACK* NETkeypressed)(int);