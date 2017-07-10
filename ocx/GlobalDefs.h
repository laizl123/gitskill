//
// GlobalDefs.h
//
#include <map>
using namespace std;

#ifndef __H_GlobalDefs__
#define __H_GlobalDefs__

//-----------------------------------------------------------------------------
// Miscellaneous helper functions
//-----------------------------------------------------------------------------
//#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
//#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
//#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

#ifndef SAFE_DELETE
#define SAFE_DELETE(x)	if( (x)!=NULL ) { delete (x); (x)=NULL; }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x)	if( (x)!=NULL ) { delete[] (x); (x)=NULL; }
#endif

#ifndef SAFE_FREE
#define SAFE_FREE(x)	if( (x)!=NULL ) { free(x); (x)=NULL; }
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x)	if( (x)!=NULL ) { (x)->Release(); (x)=NULL; }
#endif

// Attention: we place TCP listening on the client
#define SERVER_UDP_PORT			10096
#define CLIENT_UDP_PORT			10096
#define RECV_COMMAND_PORT		10999 

#define SERVER_VIDEO_UDP_PORT		12000
#define SERVER_AUDIO_UDP_PORT		13000
#define CLIENT_VIDEO_UDP_PORT		12000
#define CLIENT_AUDIO_UDP_PORT		13000

#ifdef __AudioFormat_20ms
	#define	Audio_EncodeUnit		20	
	#define AUDIODELAY              40 
	#define Audio_EncodeDataSize	38
	#define Audio_DecodeDataSize	320
	#define Audio_DecodeShortSize	160
#else	
	#define	Audio_EncodeUnit		30
	#define AUDIODELAY              30
	#define Audio_EncodeDataSize	50
	#define Audio_DecodeDataSize	480
	#define Audio_DecodeShortSize	240
#endif 

#define AUDIOCOM                (AUDIODELAY/Audio_EncodeUnit*Audio_EncodeDataSize)	//�ɼ�ѹ��������ݴ�С
#define AUDIODECOM              (AUDIODELAY/Audio_EncodeUnit*Audio_DecodeDataSize)	//���ս�ѹ������ݴ�С
// Role definitions

typedef enum 
{
	SERVER = 0, 
	CLIENT
} ROLE;

// Device types
typedef enum
{
	DT_DV = 0,
	DT_USB_Camera,
	DT_Audio_Capture,
	DT_Unknown
} Device_Type;

// How devices config to the peer PCs
typedef enum 
{
	Local_Has_Video  = 1, 
	Local_Has_Audio  = 2,
	Remote_Has_Video = 4,
	Remote_Has_Audio = 8
} Device_Config;

const long Local_Device_Mask	= 0x03;
const long Remote_Device_Mask	= 0x0c;

// Preferred capture size
const long Preferred_Width		= 320;//176;////240;
const long Preferred_Height		= 240;//144;////180;

// TCP stream header
struct Pack_Header
{
	long pack_type;
	long pack_size;

	void my_hton(void) 
	{
		pack_type		= htonl(pack_type);
		pack_size		= htonl(pack_size);
	};

	void my_ntoh(void) 
	{
		pack_type		= ntohl(pack_type);
		pack_size		= ntohl(pack_size);
	};
};

// TCP pack types
const long PT_AudioMediaType	= 10001;
const long PT_VideoMediaType	= 10002;
const long PT_AudioPayload		= 10005;
const long PT_VideoPayload		= 10006;
const long PT_Payload			= 10003;
 
// Messages
const long msg_FilterGraphError		= 'avct' + 1;
const long msg_MediaTypeReceived	= 'avct' + 2;
const long msg_TCPSocketAccepted	= 'avct' + 3;
const long msg_UDPCommandReceived	= 'avct' + 4;
const long msg_ModifyFilterGraph	= 'avct' + 5;

// Let the main thread modify filter graph
#define WM_ModifyFilterGraph		(WM_USER+123)

// UDP command defines
const long MAX_COMMAND_SIZE			= 100;
const long cmd_ClientCalling		= 'avct' + 100;
const long cmd_DeviceConfig			= 'avct' + 101;
const long cmd_BuildFilterGraph		= 'avct' + 102;
const long cmd_DisconnectRequest	= 'avct' + 103;

// UDP command pack
struct UDP_Pack
{
	long command;
	long param1;
	long param2;
	long reserved;

	void my_hton(void) 
	{
		command		= htonl(command);
		param1		= htonl(param1);
		param2		= htonl(param2);
		reserved	= htonl(reserved);
	};

	void my_ntoh(void) 
	{
		command		= ntohl(command);
		param1		= ntohl(param1);
		param2		= ntohl(param2);
		reserved	= ntohl(reserved);
	};
};

#define UDPAUDIOLEN AUDIOCOM
#define UDPVIDEOLEN 1024
#define NO__VIDEO_RESNDMSG

#define UDPREDUNDANCY_COUNT	1	//�������
#define UDPAUDIOLEN_MINE (UDPAUDIOLEN+UDPAUDIOLEN%sizeof(int))	//int ����

class CAudioData	//��Ƶ���ݰ�
{
public:
	int iDataSeq;						//�����
	BYTE DataBuffer[(UDPREDUNDANCY_COUNT+1)*UDPAUDIOLEN_MINE];	//����
};
enum AudioDataFlag
{
	AudioDataFlag_None = 0,
	AudioDataFlag_Current = 1,
	AudioDataFlag_Last = 2,
	AudioDataFlag_All = AudioDataFlag_Current | AudioDataFlag_Last,
};

#pragma pack(push, 1)

class CAudioDataHead
{
public:
	char Ver[4];
	int Flag;
	unsigned long Seq;
	//	unsigned long TimeStamp;
	
	CAudioDataHead()
	{
		memcpy(Ver, "newv", 4);
	}
};

class CAudioData2 : public CAudioDataHead
{
public:
	unsigned short VadSeq;
	unsigned short VadSeq2;
	BYTE Data[AUDIOCOM];
};

class CAudioData3 : public CAudioData2
{
public:
	BYTE Data2[AUDIOCOM];
};

#pragma pack(pop)
//by yan add
//class CVideoData
//{
//public:
//	int totalcount;    //�ܿ���
//	int iLastLen;
//	int iDataSeq;
//	int iSequence;
//	int iLen;
//	BYTE DataBuffer[UDPVIDEOLEN];
//};

//by yan add
struct CVideoData
{
public:
	int totalcount;		//һ�βɼ����ݷְ����͵İ���
	int iLastLen;		//һ�βɼ����ݷְ����͵����һ������С
	int iDataSeq;		//���ݰ������
	int iSequence;		//һ�βɼ����ݷְ��İ����
	int iLen;			//һ�βɼ����ݷְ��İ���С
	bool bIsKeyFrame;	//�Ƿ�ؼ���
	char * DataBuffer;	//һ�βɼ����ݷְ��İ�����
};

struct VData
{
    int inum;
    BYTE buffer[UDPVIDEOLEN];
	int iRepirePos;	//����λ��
};

class OneTimeVideoData
{
public:
	VData buf[50];
	int totalcount;
	int iLastLen;
	int iLastDataLen;
	int iMaxData;
	int iTime;
	int iRealRecvCount;
	bool bIsKeyFrame;
	int iSeq;
	OneTimeVideoData()
	{
		iRealRecvCount=0;
		totalcount=0;
		iLastLen=0;
		iTime=0;
		iLastDataLen=0;
		iMaxData = 0;
		bIsKeyFrame = false;
		
		for (int i=0;i<50;i++)
		{
			buf[i].inum=0;
			//memset(buf[i].buffer,RGB(0,0,0),UDPVIDEOLEN);
			buf[i].iRepirePos=-1;
		}
	}
};

class OneTimeAudioData
{
public:
	BYTE buffer[UDPAUDIOLEN];
	int iTime;
	OneTimeAudioData()
	{
		memset(buffer,0,UDPAUDIOLEN);
	}
};

#define LOCALAUDIOBUF_COUNT		6		//��Ƶ�������
#define LOCALAUDIOREPAIR_COUNT	1		//��������

//��Ƶ�Ľ�
#define LOCALVIDEOBUF_COUNT		5		//������Ƶ���ݻ���buf����
#define RESND_VIDEOBUF_COUNT	32		//�ط���Ƶ���ݻ���buf����
#define RESNDVID_REQ_INTERVAL	500		//�ط������� ms

typedef struct __ResendVideoDataMsg
{
	char	dataHead[8];
	int		dataSeq_BeginPos;		//�ط����ݰ���ʼ���
	int		dataSeq_EndPos;			//�ط����ݰ��������
	int		subDataSeq_BeginPos;	//���ݰ��ڲ���ʼ���
	int		subDataSeq_EndPos;		//���ݰ��ڲ��������

	__ResendVideoDataMsg()
	{
		memcpy(dataHead, "VidReSnd", 8);
		dataSeq_BeginPos = 0;
		dataSeq_EndPos = 0;
		subDataSeq_BeginPos = 0;
		subDataSeq_EndPos = 0;
	}
}ResendVideoDataMsg;

typedef struct __ResendSubVideoData	//��Ƶ�ְ�С������ݽṹ
{
	int		len;			//���ݴ�С
	char*	data;			//����ָ��
}ResendSubVideoData;

typedef map<int, ResendSubVideoData*> MAP_RESNDSUBVIDDATA;
typedef map<int, MAP_RESNDSUBVIDDATA*> MAP_RESNDVIDDATA;

//����Ƶ��
#define __HEARTBEAT_INTERVAL	1000   //ԭ������Ϊ5000

#endif // __H_GlobalDefs__