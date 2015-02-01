
#ifndef GAUDIO2x
#define GAUDIO2x

#define DIRECTSOUND_VERSION	0x0800
#define GAUDIO_VERSION		0x0200

	#include <windows.h>	
	#include <mmsystem.h>
	#include <mmreg.h>
	#include <dsound.h>
	#include <msacm.h>

#define MAKERROR(error) MAKE_HRESULT(1, NULL, error)
#define DllImport __declspec( dllimport )

#ifndef ulong
typedef unsigned long ulong;
#endif
#ifndef ushort
typedef unsigned short ushort;
#endif
#ifndef uchar
typedef unsigned char uchar;
#endif
#ifndef uint
typedef unsigned int uint;
#endif
#ifndef LPULONG
typedef ULONG* LPULONG;
#endif
#ifndef LPFLOAT
typedef float* LPFLOAT;
#endif
#ifndef LPCHAR
typedef char* LPCHAR;
#endif

#define GA_ERRCODE	long
#ifndef TRUE
#define TRUE	-1
#endif
#ifndef FALSE
#define FALSE	0
#endif

#if DIRECTSOUND_VERSION < 0x0800
#define LPDIRECTSOUND8 LPVOID
#define LPDIRECTSOUND3DBUFFER8 LPVOID
#define LPDIRECTSOUND3DLISTENER8 LPVOID
#endif

#define GA_OK						TRUE

#define GA_FILENOTFOUND				MAKERROR(0x000010)
#define GA_BADFORMAT				MAKERROR(0x000011)
#define GA_DSOUNDERROR				MAKERROR(0x000012)
#define GA_SYSERROR					MAKERROR(0x000013)
#define GA_CANTADDCLASS				MAKERROR(0x000014)
#define GA_INVALIDARG				MAKERROR(0x000015)
#define GA_INVALIDPARAM				MAKERROR(0x000016)
#define GA_INVALIDENVIRONMENT		MAKERROR(0x000017)
#define GA_BADCLASSVERSION			MAKERROR(0x000018)
#define GA_UNKNOWNERR				MAKERROR(0x010000)

#define GA_SOUNDCLASS_MOD			0x1
#define GA_SOUNDCLASS_S3M			0x2
#define GA_SOUNDCLASS_XM			0x3
#define GA_SOUNDCLASS_WAV			0x4
#define GA_SOUNDCLASS_MPEG			0x5
#define GA_SOUNDCLASS_RAW			0x6
#define GA_SOUNDCLASS_AUDIOCD		0x7

#define GA_FLAG_FORWARDLOOP			0x1
#define GA_FLAG_PINGPONGLOOP		0x2
#define GA_FLAG_LOOP				0x1
#define GA_FLAG_MEMPROGRESS			0x4
#define GA_FLAG_STANDVOLUME			0x8

#define GA_SAMPTYPE_UBYTE			0x1
#define GA_SAMPTYPE_WORD			0x2
#define GA_SAMPTYPE_FLOAT			0x3

#define GA_INPUT_DISK				0x00000001
#define GA_INPUT_MEMORY				0x00000002

#define GA_OUTPUT_DSOUND			0x00000001
#define GA_OUTPUT_DSOUNDSOFT		0x00000002
#define GA_OUTPUT_DSOUNDHARD		0x00000003
#define GA_OUTPUT_MIXER				0x00000008
#define GA_OUTPUT_MEMORY			0x00000009

#define GA_AUDIOSTAGE_SFX			0x1
#define GA_AUDIOSTAGE_MSX			0x2
#define GA_AUDIOSTAGE_TRK			0x3

#define GA_AUDIOSTAGE_ASYNC			0x1
#define GA_AUDIOSTAGE_SYNC			0x2

#define GA_AUDIOSTATUS_ACTIVE		0x1
#define GA_AUDIOSTATUS_DEACTIVE		0x2

#define GA_DEVICETYPE_MUTE			0x1
#define GA_DEVICETYPE_SYSTEM		0x2
#define GA_DEVICETYPE_DSOUND		0x3

#define GA_DEVICEFREQ_8K			8000
#define GA_DEVICEFREQ_11K			11025
#define GA_DEVICEFREQ_16K			16000
#define GA_DEVICEFREQ_22K			22050
#define GA_DEVICEFREQ_32K			32000
#define GA_DEVICEFREQ_44K			44100
#define GA_DEVICEFREQ_48K			48000

#define GA_NOTIFY_POS				0x00000001
#define GA_NOTIFY_BYTEPOS			0x00000005
#define GA_NOTIFY_TRKNOTE			0x00000002
#define GA_NOTIFY_TRKEFFECT			0x00000003
#define GA_NOTIFY_TRKINSTRU			0x00000004
#define GA_NOTIFY_END				0x00000006

#define GA_NOTIFY_WRITETIME			0x000000001
#define GA_NOTIFY_HEARDTIME			0x000000002

#define GA_GETMODE_HEARDTIME		0x1
#define GA_GETMODE_WRITETIME		0x2

enum
{
	GA_CDTRACK_STOP=0,
	GA_CDTRACK_LOOP,
	GA_CDTRACK_NEXT
};

enum
{
	GA_SOUNDSTATUS_STOP = 0,
	GA_SOUNDSTATUS_PAUSE,
	GA_SOUNDSTATUS_PLAY
};

typedef class CGAudio		*LP_GAUDIO;
typedef class CWAVstream	*LP_WAVSTREAM;
typedef class CMP3stream	*LP_MP3STREAM;
typedef class CRAWstream	*LP_RAWSTREAM;
typedef class CTrackerMOD	*LP_TRACKERMOD;
typedef class CTrackerS3M	*LP_TRACKERS3M;
typedef class CTrackerXM	*LP_TRACKERXM;

struct st_GA_ERRORFORMAT;
struct st_GA_DeviceInfo;
struct st_GA_Notify;
struct st_GA_AudioBuffer;

struct st_CTrackerInfo;
struct st_CWAVinfo;
struct st_CMPEGinfo;
struct st_CAudioCDinfo;

struct st_StreamParameters;
struct st_RAWParameters;
struct st_TrackerParameters;

typedef void gAudio_NetworkCallbackFun(DWORD, void*, void*);
typedef void gAudio_NotifyFunction(st_GA_Notify*);
typedef void gAudio_DSPcallback(st_GA_AudioBuffer*, DWORD);

// ============================
//  st_GA_ERRORFORMAT protocol
// ============================
struct st_GA_ErrorFormat
{
	WORD	structSize;
	DWORD	error;
	union		
	{
		DWORD	ext;
		HRESULT	hres;
	} ExtendedError;
};

// =================================
//  Sound device structure protocol
// =================================
struct st_GA_DeviceInfo
{
	WORD			structSize;
	LPCHAR			description;
	DWORD			type;
	HWAVEOUT		hwo;
	HWND			hwnd;
	LPDIRECTSOUND	lpDirectSound;
	LPDIRECTSOUND8	lpDirectSound8;
	GUID			guid;
};

// =================
//	Notify protocol
// =================
struct st_GA_Notify
{
	WORD	structSize;
	BYTE	type;
	DWORD	notifyTime;
	union
	{
		float Float;
		long Long;
	};

	HANDLE Event;
	gAudio_NotifyFunction *function;
};

struct st_GA_AudioBuffer
{
	WORD				structSize;
	st_GA_AudioBuffer	*lpPreviousBuffer;
	LPVOID				lpPCM;
	DWORD				nbrBlocks;
};

struct st_CTrackerMODinfo
{
	WORD	structSize;
	LPCHAR	name;
	UINT	length;
	UINT	nbrPatterns;
	UINT	nbrSamples;
	UINT	nbrVoices;
};

struct st_CTrackerS3Minfo
{
	WORD	structSize;
	LPCHAR	name;
	UINT	length;
	UINT	nbrPatterns;
	UINT	nbrSamples;
	UINT	nbrVoices;
};

struct st_CTrackerXMinfo
{
	WORD	structSize;
	LPCHAR	name;
	UINT	length;
	UINT	nbrPatterns;
	UINT	nbrInstrus;
	UINT	nbrVoices;
};

struct st_CWAVinfo
{
	WORD	structSize;
	UINT	nbrChans;
	UINT	nbrBits;
	USHORT	frequency;
	WORD	formatTag;
	ULONG	dataChunkSize;
	ULONG	avgBytesRate;
	ULONG	unpackedDataSize;
	LPACMDRIVERDETAILS lpDriverDetails;
};

struct st_CMPEGinfo
{
	WORD	structSize;
	UINT	nbrChans;
	UINT	nbrBits;
	USHORT	frequency;
	UINT	layerVersion;
	ULONG	dataChunkSize;
	ULONG	unpackedDataSize;
};

struct st_CAudioCDinfo
{
	WORD		classID;
	UINT		nbrTracks;
	USHORT		totalLength;
	USHORT		*tracksLength;
};

struct st_GA_StreamParameters
{
	WORD		classID;
	LPCHAR		fileName;
	LPVOID		lpSrcMem;
	DWORD		sizeSrcMem;
	DWORD		flag;
	DWORD		input;
	DWORD		output;
	DWORD		audioStage;
	DWORD		loopStart, loopEnd;
};

struct st_GA_RAWParameters
{
	WORD		classID;
	DWORD		flag;
	DWORD		output;
	DWORD		audioStage;
	WORD		nbrChannels;
	WORD		nbrBits;
	DWORD		size;
};

struct st_GA_TrackerParameters
{
	WORD		classID;
	LPCHAR		fileName;
	LPVOID		lpSrcMem;
	DWORD		sizeSrcMem;
	DWORD		flag;
	DWORD		input;
	DWORD		output;
	DWORD		audioStage;
};

// ===================================
//	G-Audio general interface (ver.2)
// ===================================
#define CLASS_GAUDIO_ID		0x0200

class CGAudio
{
	LPVOID				lpReserved;
public:
	CGAudio();
	~CGAudio();
	GA_ERRCODE			init(DWORD, DWORD, BOOL);
	GA_ERRCODE			init(st_GA_DeviceInfo*, DWORD, BOOL);
	GA_ERRCODE			getSoundClass(DWORD, LPVOID, LPVOID*);
	DWORD				getNbrDevice();
	st_GA_DeviceInfo*	getDeviceInfo(int);
	GA_ERRCODE			installSoftwareMixer();
	void				setGlobalVolume(float);
	void				setGlobalPan(float);
	GA_ERRCODE			setAudioStageStatus(DWORD, DWORD);
	DWORD				createAudioStage(ULONG, DWORD);
	GA_ERRCODE			removeAudioStage(DWORD);
	GA_ERRCODE			setPreDSPcallback(gAudio_DSPcallback*, DWORD, DWORD);
	GA_ERRCODE			setPostDSPcallback(gAudio_DSPcallback*, DWORD, DWORD);
	GA_ERRCODE			getLastMixerAudioBlock(st_GA_AudioBuffer**);
	GA_ERRCODE			retrieveLPDS3DListener(LPDIRECTSOUND3DLISTENER*);
	GA_ERRCODE			retrieveLPDS3DListener8(LPDIRECTSOUND3DLISTENER8*);
	GA_ERRCODE			retrieveMixerLPDSBuffer(LPDIRECTSOUNDBUFFER*);
	void				setDSoundSWBufferFlag(DWORD);
	void				setDSoundHWBufferFlag(DWORD);
	GA_ERRCODE			set3DAlgorithm(GUID);
	GA_ERRCODE			mixerEnterCriticalSection();
	GA_ERRCODE			mixerLeaveCriticalSection();
	st_GA_ERRORFORMAT	getLastError();
	LPCHAR				getLastErrorString();
};

// ========================
//  COMMON AUDIO INTERFACE
// ========================
class CAudio
{
public:
	GA_ERRCODE	virtual play()=0;
	GA_ERRCODE	virtual pause()=0;
	GA_ERRCODE	virtual stop()=0;
	void		virtual release()=0;
};

// ==================
//  STREAM INTERFACE
// ==================
class CStream : public CAudio
{
public:
	void		virtual setGetMode(DWORD)=0;
	void		virtual getStreamPos(ULONG*)=0;
	GA_ERRCODE	virtual seekStreamPos(ULONG)=0;
	void		virtual setFrequency(ULONG)=0;
	void		virtual getFrequency(ULONG*)=0;
	void		virtual setVolume(float)=0;
	void		virtual getVolume(LPFLOAT)=0;
	void		virtual setPan(float)=0;
	void		virtual getPan(LPFLOAT)=0;
	GA_ERRCODE	virtual retrievePCMdata(LPVOID*)=0;
	GA_ERRCODE	virtual retrieveLPDSBuffer(LPDIRECTSOUNDBUFFER*)=0;
	GA_ERRCODE	virtual retrieveLPDS3DBuffer(LPDIRECTSOUND3DBUFFER*)=0;
	GA_ERRCODE	virtual retrieveLPDS3DBuffer8(LPDIRECTSOUND3DBUFFER8*)=0;
	GA_ERRCODE	virtual clone(CStream**)=0;
	GA_ERRCODE	virtual getStatus(LPDWORD)=0;
	GA_ERRCODE	virtual writeSample(ULONG, ULONG, LPVOID, DWORD)=0;
	GA_ERRCODE	virtual setNotifyList(st_GA_Notify*, int)=0;
};

#define CLASS_WAVSTREAM_ID		0x0200
#define CLASS_MPEGSTREAM_ID		0x0200
#define CLASS_RAWSTREAM_ID		0x0200

// =========================
//  WAVSTREAM CLASS (ver.2)
// =========================
class CWAVstream : public CStream
{
	LPVOID			lpReserved;
public:
	GA_ERRCODE		retrieveInfo(st_CWAVinfo*);
};

// ====================
//  MPEG CLASS (ver.2)
// ====================
class CMPEGstream : public CStream
{
	LPVOID			lpReserved;
public:
	GA_ERRCODE		retrieveInfo(st_CMPEGinfo*);
	GA_ERRCODE		getBitsRate(LPUINT);
};

// ===================
//  RAW CLASS (ver.2)
// ===================
class CRAWstream : public CStream
{
	LPVOID			lpReserved;
public:
	void			clear();
};

// ======================================================
//            TRACKER INTERFACE (MOD, S3M, XM)
// ======================================================
class CTracker : public CAudio
{
public:
	void		virtual setGetMode(DWORD)=0;
	void		virtual setPanPower(float)=0;
	void		virtual getRow(LPINT)=0;
	void		virtual getPattern(LPINT)=0;
	void		virtual getPatternLength(LPINT)=0;
	void		virtual getPos(LPINT)=0;
	void		virtual getSpeed(LPINT)=0;
	void		virtual getTempo(LPINT)=0;
	GA_ERRCODE	virtual seekPos(int)=0;
	void		virtual setVolume(float)=0;
	float		virtual getVolume()=0;
	GA_ERRCODE	virtual getStatus(LPDWORD)=0;
	GA_ERRCODE	virtual setNotifyList(st_GA_Notify*, int)=0;
};

#define CLASS_TRACKERMOD_ID	0x0200
#define CLASS_TRACKERS3M_ID	0x0200
#define CLASS_TRACKERXM_ID	0x0200

// ===================
//  MOD CLASS (ver.2)
// ===================
class CTrackerMOD : public CTracker
{
	LPVOID			lpReserved;
public:
	GA_ERRCODE		retrieveInfo(st_CTrackerMODinfo*);
};

// ===================
//  S3M CLASS (ver.2)
// ===================
class CTrackerS3M : public CTracker
{
	LPVOID			lpReserved;
public:
	GA_ERRCODE		retrieveInfo(st_CTrackerS3Minfo*);
};

// ==================
//  XM CLASS (ver.2)
// ==================
class CTrackerXM : public CTracker
{
	LPVOID			lpReserved;
public:
	GA_ERRCODE		retrieveInfo(st_CTrackerXMinfo*);
};

// =================
//  AUDIO CD PLAYER
// =================
class CAudioCD : public CAudio
{
	LPVOID			lpReserved;
public:
	GA_ERRCODE		informPos(UINT, UINT, UINT, DWORD);
	GA_ERRCODE		getPos(LPUINT, LPUINT, LPUINT);
	GA_ERRCODE		open();
	GA_ERRCODE		close();
	BOOL			isCDpresent();
	GA_ERRCODE		getStatus(LPDWORD);
	void			retrieveInfo(st_CAudioCDinfo*);
};

// ===================
//	CONSTANT FUNCTION
// ===================
WORD	GA_getLibVersion();
WORD	GA_getLibID();

#endif

