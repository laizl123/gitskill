#include "stdafx.h"
#include "GlobalOperation.h"
#ifdef USE_WINSOCK2
#include "winsock2.h"
#else
#include "WinSock.h"
#endif

#include <string>
#include <sys/timeb.h>
#include <Iprtrmib.h>
#include <iphlpapi.h>
#include <Nb30.h>
using namespace std;

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Netapi32.lib")

#pragma warning(disable:4786)

#include "IPCCMessage.h"
#include "CreditUDP.h"
//#include "ServerInfoDef.h"
#include "base64.h"
#include "DES.h"

bool g_bIsACDServer = false;
string g_strMsgLogPath = "";

string GetAppPath()
{
	char szFullPath[255];
	char szDir[255];
	char szDrive[255];

	memset(szFullPath, 0, 255);
	memset(szDir, 0, 255);
	memset(szDrive, 0, 255);

	::GetModuleFileName(NULL,szFullPath,255);
	::_tsplitpath(szFullPath,szDrive,szDir,NULL,NULL);

	string sPathName;
	sPathName = string(szDrive) + string(szDir);

	if( sPathName[sPathName.length()-1] != '\\' )
		sPathName += "\\";

	return sPathName;
}

string NewGlobalInvokeID()
{
	static string sComputer = "";
	if ( sComputer == "" )
	{
		char cComputer[32];
		DWORD iSize = 32;
		GetComputerName( cComputer, &iSize );
		sComputer = cComputer;
	}

	static int iCount = 0;
	static long iTime = (long)time(NULL);

	char c[50] = {0};
	int iLen = sprintf(c,"%s%08X%08X", sComputer.c_str(), iTime, iCount );

	iCount++;

	return c;
}

bool CreateMultipleLevelDirectory(string strDir)
{
	HANDLE		fFile;					// File Handle
	WIN32_FIND_DATA fileinfo;			// File Information Structure
	deque<string>	m_arr;				// deque to hold Directory Structures
	bool tt;							// BOOL used to test if Create Directory was successful
	string::size_type x1 = 0;							// Counter
	string tem = "";					// Temporary string Object

	//进行容错处理，使之能处理以"\"结尾的路径
	if (strDir.length() >0 )
	{
		if (strDir[strDir.length()-1]== '\\')
		{
			strDir.erase(strDir.end()-1); //最后是一个反斜杠
		}
	}

	// Before we go to a lot of work.  
	// Does the file exist
	fFile = FindFirstFile(strDir.c_str(),&fileinfo);
	if(INVALID_HANDLE_VALUE != fFile)
	{
		if(fileinfo.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		{
			//  Directory Exists close file and return
			FindClose(fFile);
			return TRUE;
		}
	}
	// if the file exists and it is a directory

	m_arr.clear();			// Not really necessary - Just habit
	for(x1=0;x1<strDir.length();x1++)	// Parse the supplied string Directory String
	{									
		if(strDir[x1] != '\\')		// if the Charachter is not a \ 
			tem += strDir[x1];		// else add character to Temp String
		else
		{
			m_arr.push_back(tem);			// if the Character is a \ Add the Temp string to the deque
			tem += "\\";				// Now add the \ to the temp string
		}
		if(x1 == strDir.length()-1)		// If we reached the end of the file add the remaining string
			m_arr.push_back(tem);
	}

	// Close the file
	FindClose(fFile);

	// Now lets cycle through the String Array and create each directory in turn
	deque<string>::iterator itItem = m_arr.begin();
	while(itItem != m_arr.end())
	{
		tem = *itItem; itItem++;
		tt = (::CreateDirectory(tem.c_str(),NULL)==FALSE)?false:true;
		// If the Directory exists it will return a false
		if(tt)
		{
			SetFileAttributes(tem.c_str(),FILE_ATTRIBUTE_NORMAL);
		}
		// If we were successful we set the attributes to normal
	}
	m_arr.clear();
	//  Now lets see if the directory was successfully created
	fFile = FindFirstFile(strDir.c_str(),&fileinfo);

	// if the file exists and it is a directory
	if(fileinfo.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
	{
		//  Directory Exists close file and return
		FindClose(fFile);
		return TRUE;
	}
	else
	{
		FindClose(fFile);	
		return FALSE;
	}
}

unsigned long ConvertIP(string ip)
{
	if(ip.empty())
		return -1;

	int iIp = inet_addr(ip.c_str());

	return iIp;
}

unsigned short ConvertPort(int port)
{
	return htons(port);
}

string IntToString(int ivalue)
{
	string svalue("");

	ostringstream ostream;
	ostream.str("");
	ostream << ivalue;
	svalue = ostream.str();

	return svalue;
}

bool IsMediaData(const char *buf, int size)
{
	//判断是否 CreditUDP 消息
	char headInfo[8];
	memset(headInfo, 0, 8);
	if(size>=8)
		memcpy(headInfo, buf, 8);
	else
		return false;

	if(0!=memcmp(headInfo, "HartPack", 8) && 0!=memcmp(headInfo, "CreditUD", 8))
		return true;

	return false;
}

string GetLocalIP()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	string sLocalIP = "";

	char szHostName[128];
	struct hostent * pHost;
	szHostName[0]=0;
	int error;
	error = gethostname(szHostName,128);

	if(!szHostName[0]) {sLocalIP.empty();return sLocalIP;}
	pHost=gethostbyname(szHostName);
	if(pHost==NULL) {sLocalIP.empty();return sLocalIP;}

	sLocalIP = inet_ntoa(*(struct in_addr *)pHost->h_addr_list[0]);

	string sTempIP("");
	string sTempPhysicalAddr("");
	string sGateWayIP("");

	string sFirstLanIP_HaveGateWay("");	//第一个符合条件的 LanIP
	string sFirstLanIP_NoGateWay("");	//第一个符合条件的 LanIP
	string sFirstInternetIP_HaveGateWay("");
	string sFirstInternetIP_NoGateWay("");

	for(int i = 0; pHost!= NULL && pHost->h_addr_list[i]!= NULL; i++ ) 	
	{
		sTempIP = inet_ntoa(*(struct in_addr *)pHost->h_addr_list[i]);
		sTempPhysicalAddr = GetPhysicalAddrByIP(sTempIP);
		sGateWayIP = GetGateWayeInfoByIP(sTempIP);
		if(sTempPhysicalAddr=="" || sTempPhysicalAddr=="00-00-00-00-00-00")
			continue;
		if(sGateWayIP != "")
		{
			if(!IsLanIP(sTempIP))	//不是局域网 ip
			{
				sFirstInternetIP_HaveGateWay = sTempIP;
				break;
			}
			if(sFirstLanIP_HaveGateWay == "")
				sFirstLanIP_HaveGateWay = sTempIP;
		}
		else
		{
			if(!IsLanIP(sTempIP))
				sFirstInternetIP_NoGateWay = sTempIP;
			else if(sFirstLanIP_NoGateWay == "")
				sFirstLanIP_NoGateWay = sTempIP;
		}
	}

	if(sFirstInternetIP_HaveGateWay != "")
		sLocalIP = sFirstInternetIP_HaveGateWay;
	else if(sFirstLanIP_HaveGateWay != "")
		sLocalIP = sFirstLanIP_HaveGateWay;
	else if(sFirstInternetIP_NoGateWay != "")
		sLocalIP = sFirstInternetIP_NoGateWay;
	else if(sFirstLanIP_NoGateWay != "")
		sLocalIP = sFirstLanIP_NoGateWay;

	return sLocalIP;
}

void GetIPConfigInfo()
{
	SECURITY_ATTRIBUTES sa; 
	HANDLE hRead,hWrite; 

	sa.nLength = sizeof(SECURITY_ATTRIBUTES); 
	sa.lpSecurityDescriptor = NULL; 
	sa.bInheritHandle = TRUE; 
	if (!CreatePipe(&hRead,&hWrite,&sa,0)) { 
		printf("Error On CreatePipe() \n"); 
		return; 
	} 
	STARTUPINFO si; 
	PROCESS_INFORMATION pi; 
	si.cb = sizeof(STARTUPINFO); 
	GetStartupInfo(&si); 
	si.hStdError = hWrite; 
	si.hStdOutput = hWrite; 
	si.wShowWindow = SW_HIDE; 
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES; 
	if (!CreateProcess(NULL,"ipconfig /all" 
		,NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi)) { 
			printf("Error on CreateProcess() \n"); 
			return; 
	} 

	Sleep(100);
	CloseHandle(hWrite); 

	string sss;
	char all[8000]={0};
	DWORD bytesRead; 
	int i = 0;
	while (true) 
	{ 
		if (ReadFile(hRead,all, 8000, &bytesRead,NULL) == NULL) 
			break; 
		i++;
	} 	
	CloseHandle(hRead);

	sss = all;
	printf(sss.c_str());
}

string GetPhysicalAddrByIP(string ip)
{
	int hr;
	IPAddr  ipAddr;
	ULONG   pulMac[2];
	ULONG   ulLen;

	ipAddr = inet_addr (ip.c_str());
	memset (pulMac, 0xff, sizeof (pulMac));
	ulLen = 6;

	hr = SendARP (ipAddr, 0, pulMac, &ulLen);

	size_t i, j;
	char * szMac = new char[ulLen*3];
	PBYTE pbHexMac = (PBYTE) pulMac;

	//
	// Convert the binary MAC address into human-readable
	//
	if(ulLen == 0)
	{
		delete [] szMac;
		return "";
	}

	for (i = 0, j = 0; i < ulLen - 1; ++i) {
		j += sprintf (szMac + j, "%02X-", pbHexMac[i]);
	}

	sprintf (szMac + j, "%02X", pbHexMac[i]);

	string sPhysicalAddr = szMac;
	delete [] szMac;

	return sPhysicalAddr;
}

string GetGateWayeInfoByIP(string ip)
{	
	IP_ADAPTER_INFO* pAdapterInfo=NULL;
	ULONG ulSize=0;
	GetAdaptersInfo(pAdapterInfo,&ulSize);				//获取 ulSize 的值
	pAdapterInfo=(PIP_ADAPTER_INFO)new(char[ulSize]);
	int ret = GetAdaptersInfo(pAdapterInfo,&ulSize);	//填充 pAdapterInfo

	if(ret != ERROR_SUCCESS)
	{
		delete pAdapterInfo;
		return "";
	}

	IP_ADAPTER_INFO* pAdapterInfoTemp = pAdapterInfo;

	string tempIP("");
	string gatewayip("");
	while(pAdapterInfo)
	{
		tempIP = pAdapterInfo->IpAddressList.IpAddress.String;
		if(ip == tempIP)
		{
			gatewayip = pAdapterInfo->GatewayList.IpAddress.String;
			break;
		}
		pAdapterInfo = pAdapterInfo->Next;
	}
	delete pAdapterInfoTemp;

	return gatewayip;
}

bool IsLanIP(string ip)
{
	if(ip.length() < 7)
		return false;
	int firstPos = ip.find_first_of(".");
	string firstValue = ip.substr(0, firstPos);

	string sTemp = ip.substr(firstPos+1, ip.length());
	int secondPos = sTemp.find_first_of(".");
	string secondValue = sTemp.substr(0, firstPos);

	if(firstValue=="10")
		return true;

	if(firstValue=="192" && secondValue=="168")
		return true;

	if(firstValue=="172")
	{
		int iSecond = atoi(secondValue.c_str());
		if(iSecond>=16 && iSecond<=31)
			return true;
	}

	return false;
}

void Multi_TerminateThread(HANDLE& handle)
{
	if(handle)
	{	
		DWORD lpExitCode;
		BOOL ret;

		ret = ::GetExitCodeThread(handle,&lpExitCode);

		if(lpExitCode==STILL_ACTIVE)
		{		
			ret = ::TerminateThread(handle,1122);
			for(int i=3; i>0 && !ret;--i) // && !ret && i!=0
			{
				ret = ::TerminateThread(handle,1122);
			}
		}
		handle = NULL;
	}
}

void Multi_TerminateTimer(HWND hWnd, int& nTimerID)
{
	if(nTimerID>0 && hWnd)
	{
		BOOL bkill = KillTimer(hWnd,nTimerID);
		for (int i=3; i>0 && !bkill; --i) 
		{
			bkill = KillTimer(hWnd,nTimerID);
		}
		nTimerID = -1;
	}
}

string ConvertNatIP2HostIP(unsigned long ip)
{
	in_addr addr;
	addr.S_un.S_addr=ip;
	return inet_ntoa(addr);
}

unsigned long ConvertNatIP2HostIPi(unsigned long ip)
{
	return ntohl(ip);
}

int ConvertNatPort2HostPort(unsigned short port)
{
	return ntohs(port);
}

void MySleep(int msCount)
{
	if(msCount <= 0)
		return;

	for(int i=0; i<msCount; i++)
	{
		LARGE_INTEGER litmp; 
		LONGLONG QPart1,QPart2;
		double dfMinus, dfFreq, dfTim; 
		QueryPerformanceFrequency(&litmp);
		dfFreq = (double)litmp.QuadPart;// 获得计数器的时钟频率
		QueryPerformanceCounter(&litmp);
		QPart1 = litmp.QuadPart;// 获得初始值
		do
		{
			QueryPerformanceCounter(&litmp);
			QPart2 = litmp.QuadPart;//获得中止值
			dfMinus = (double)(QPart2-QPart1);
			dfTim = dfMinus / dfFreq;// 获得对应的时间值，单位为秒
		}while(dfTim<0.001);
	}
}

int GetLocalTimeInfo(int& hour, int& minute, int& second)
{
	SYSTEMTIME t1;
	::GetLocalTime(&t1);

	hour = t1.wHour;
	minute = t1.wMinute;
	second = t1.wSecond;

	return 0;
}

unsigned short GetRandomPort()
{
	unsigned short iTemp = 0;
	while ( 1 )
	{
		iTemp = rand();
		iTemp += rand();
		if( ( iTemp > 1024 ) && ( iTemp%1000 != 0 )
			&& ( iTemp > 30000 || iTemp < 10000 )
			&& (iTemp != 12581 /*ServerInfoDef::Port_AreaCodeServer*/))
			/*			&& iTemp != ServerInfoDef::Port_ACDServer
			&& iTemp != ServerInfoDef::Port_CheckNatServerA
			&& iTemp != ServerInfoDef::Port_CheckNatServerB
			&& iTemp != ServerInfoDef::Port_DataCollectServer
			&& iTemp != ServerInfoDef::Port_GatewayManageDataServer
			&& iTemp != ServerInfoDef::Port_GatewayManageServer
			&& iTemp != ServerInfoDef::Port_GuideServer
			&& iTemp != ServerInfoDef::Port_LoginServer
			&& iTemp != ServerInfoDef::Port_RecordServer
			&& iTemp != ServerInfoDef::Port_RelayServer
			&& iTemp != ServerInfoDef::Port_SmartRouteDataServer
			&& iTemp != ServerInfoDef::Port_SmartRouteServer
			&& iTemp != ServerInfoDef::Port_SysManageServer
			&& iTemp != ServerInfoDef::Port_TransmitServer
			&& iTemp != ServerInfoDef::Port_UStateServer )
			*/
			break;
	}
	return iTemp;
}

void SendIPCCMsg(CCreditUDP* pSocket, SIPCCMessage* pMsg, unsigned long iIp, unsigned short iPort)
{
	CIPCCMsgExchanger msgExchanger;

	char* buf;
	int iSize;
	msgExchanger.SerializeMsg(*pMsg, buf, iSize);

	string sErrInfo("");
	pSocket->SendData( iIp, iPort, buf, iSize, sErrInfo );

	if( buf != NULL )
		delete buf;
}
typedef struct _ASTAT_ 
{ 
	ADAPTER_STATUS adapt; 
	NAME_BUFFER    NameBuff [30]; 
}ASTAT, * PASTAT; 


string getmac_one (int lana_num) 
{ 
	NCB ncb; 
	UCHAR uRetCode;
	ASTAT Adapter; 

	memset( &ncb, 0, sizeof(ncb) ); 
	ncb.ncb_command = NCBRESET; 
	ncb.ncb_lana_num = lana_num;    
	// 指定网卡号 

	// 首先对选定的网卡发送一个NCBRESET命令，以便进行初始化  
	uRetCode = Netbios( &ncb ); 
	//    TRACE( "The NCBRESET return code is: 0x%x \n", uRetCode ); 

	memset( &ncb, 0, sizeof(ncb) ); 
	ncb.ncb_command = NCBASTAT; 
	ncb.ncb_lana_num = lana_num;  // 指定网卡号 

	strcpy( (char *)ncb.ncb_callname, "*               " ); 
	ncb.ncb_buffer = (unsigned char *) &Adapter; 

	// 指定返回的信息存放的变量  
	ncb.ncb_length = sizeof(Adapter); 

	// 接着，可以发送NCBASTAT命令以获取网卡的信息  
	uRetCode = Netbios( &ncb ); 
	//    TRACE( "The NCBASTAT  return code is: 0x%x \n", uRetCode ); 
	//	CString sMACAddress;
	string strMACAddress;
	if ( uRetCode == 0 ) 
	{ 	
		char* chMac = new char[16];
		sprintf (chMac, "%02X%02X-%02X%02X-%02X%02X", 
			Adapter.adapt.adapter_address[0], 
			Adapter.adapt.adapter_address[1], 
			Adapter.adapt.adapter_address[2], 
			Adapter.adapt.adapter_address[3], 
			Adapter.adapt.adapter_address[4], 
			Adapter.adapt.adapter_address[5] );

		strMACAddress = chMac;
		delete [] chMac;
		/*
		sMACAddress.Format( "%02X%02X-%02X%02X-%02X%02X", 
		Adapter.adapt.adapter_address[0], 
		Adapter.adapt.adapter_address[1], 
		Adapter.adapt.adapter_address[2], 
		Adapter.adapt.adapter_address[3], 
		Adapter.adapt.adapter_address[4], 
		Adapter.adapt.adapter_address[5] );
		*/
		// 把网卡MAC地址格式化成常用的16进制形式，如0010-A4E4-5802  
		/*
		TRACE( "The Ethernet Number[%d] is: %02X%02X-%02X%02X-%02X%02X\n", 
		lana_num, 
		Adapter.adapt.adapter_address[0], 
		Adapter.adapt.adapter_address[1], 
		Adapter.adapt.adapter_address[2], 
		Adapter.adapt.adapter_address[3], 
		Adapter.adapt.adapter_address[4], 
		Adapter.adapt.adapter_address[5] ); 
		*/
	} 
	return strMACAddress;
} 

int CalTimeSpan(int begin, int end)
{
	int timeSpan = end - begin;
	if(timeSpan <0)
		timeSpan = timeSpan + (int)4294967695;

	return timeSpan;
}

void StringMakeLower(string &originString)
{
	//ctype<char> ct;
	//ct.tolower(originString.begin(),originString.end());
}

void StringMakeUpper(string &originString)
{
	//ctype<char> ct;
	//ct.toupper(originString.begin(),originString.end());
}
void convert8to16(unsigned char* pre_data, int size, short* post_data)
{
	int S = 0;
	while (S<size)
	{	
		unsigned char alaw;
		memcpy(&alaw, (pre_data + S), 1);

		alaw ^= 0x55;  // A-law has alternate bits inverted for transmission

		unsigned short sign = alaw&0x80;

		short linear = alaw&0x1f;
		linear <<= 4;
		linear += 8;  // Add a 'half' bit (0x08) to place PCM value in middle of range

		alaw &= 0x7f;
		if(alaw>=0x20)
		{
			linear |= 0x100;  // Put in MSB
			unsigned short shift = (alaw>>4)-1;
			linear <<= shift;
		}

		if(!sign)
		{
			linear = -linear;
			memcpy(post_data+S, &linear,2);
		}
		else
			memcpy(post_data+S, &linear,2);

		S++;
	}
}
void convert16to8(short* pre_data, int size, unsigned char* post_data)
{
	int S = 0;
	while (S<size)
	{	
		short p;
		memcpy(&p, (pre_data + S), 2);
		unsigned short	a;  // A-law value we are forming
		unsigned char b;
		if(p<0)
		{
			// -ve value
			// Note, ones compliment is used here as this keeps encoding symetrical
			// and equal spaced around zero cross-over, (it also matches the standard).
			p = ~p;
			a = 0x00; // sign = 0
		}
		else
		{
			// +ve value
			a = 0x80; // sign = 1
		}

		// Calculate segment and interval numbers
		p >>= 4;
		if(p>=0x20)
		{
			if(p>=0x100)
			{
				p >>= 4;
				a += 0x40;
			}
			if(p>=0x40)
			{
				p >>= 2;
				a += 0x20;
			}
			if(p>=0x20)
			{
				p >>= 1;
				a += 0x10;
			}
		}
		// a&0x70 now holds segment value and 'p' the interval number

		a += p;  // a now equal to encoded A-law value


		a = a^0x55;
		b = unsigned char(a);
		memcpy(post_data+S, &b,1);
		S++;
	}

}

#define	SIGN_BIT	(0x80)		/* Sign bit for a A-law byte. */
#define	QUANT_MASK	(0xf)		/* Quantization field mask. */
#define	NSEGS		(8)			/* Number of A-law segments. */
#define	SEG_SHIFT	(4)			/* Left shift for segment number. */
#define	SEG_MASK	(0x70)		/* Segment field mask. */
static short seg_aend[8] = {0x1F, 0x3F, 0x7F, 0xFF,
0x1FF, 0x3FF, 0x7FF, 0xFFF};
static short seg_uend[8] = {0x3F, 0x7F, 0xFF, 0x1FF,
0x3FF, 0x7FF, 0xFFF, 0x1FFF};











static short search(
					int		val,				/* changed from "short" *drago* */
					short	*table,
					int		size)				/* changed from "short" *drago* */
{
	int		i;									/* changed from "short" *drago* */

	for (i = 0; i < size; i++) {
		if (val <= *table++)
			return (i);
	}
	return (size);
}

static inline unsigned char linear2alaw(int pcm_val)	/* 2's complement (16-bit range) */
/* changed from "short" *drago* */
{
	int		mask;	/* changed from "short" *drago* */
	int		seg;	/* changed from "short" *drago* */
	unsigned char	aval;

	pcm_val = pcm_val >> 3;

	if (pcm_val >= 0) {
		mask = 0xD5;		/* sign (7th) bit = 1 */
	} else {
		mask = 0x55;		/* sign bit = 0 */
		pcm_val = -pcm_val - 1;
	}

	/* Convert the scaled magnitude to segment number. */
	seg = search(pcm_val, seg_aend, 8);

	/* Combine the sign, segment, and quantization bits. */

	if (seg >= 8)		/* out of range, return maximum value. */
		return (unsigned char) (0x7F ^ mask);
	else {
		aval = (unsigned char) seg << SEG_SHIFT;
		if (seg < 2)
			aval |= (pcm_val >> 1) & QUANT_MASK;
		else
			aval |= (pcm_val >> seg) & QUANT_MASK;
		return (aval ^ mask);
	}
}

int linear2pcma(unsigned char* pOut, short* pIn, int iSizeIn)
{
	int iTemp = iSizeIn;
	while ( --iTemp )
	{
		(*pOut++) = linear2alaw(*pIn++);
	}
	return iSizeIn;
}

long filesize(FILE *stream) 
{ 
	long curpos, length; 

	curpos = ftell(stream); 
	fseek(stream, 0L, SEEK_END); 
	length = ftell(stream); 
	fseek(stream, curpos, SEEK_SET); 
	return length; 
}

string DecryptBase64NDes(string sCode, char sKey[8])
{
	char ch[256] = {0};
	int i = Base64Decode( ch, sCode.c_str(), sCode.length() );
	char ch2[256] = {0};
	CDES::RunDes( 1, false, ch, ch2, i, sKey, 8);

	return ch2;
}

bool IsMobilePhone(string sPhone)
{
	if ( sPhone == "" )
	{
		return false;
	}
	
	if ( (sPhone.length() == 11 && sPhone[0] == '1') || (sPhone.length() == 12 && sPhone.substr(0, 2) == "01") )
	{
		return true;
	}
	
	return false;
}

bool IsLocolPhone(string sPhone, string sLocolCode)
{
	if ( sPhone.substr( 0, 1 ) == "0" )
	{
		if ( sPhone.substr( 0, sLocolCode.length() ) == sLocolCode )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
}

/*
#ifdef MAKEMSGLOG
struct LogStruct 
{
	string sLog;
	//char pBuf[1500];
	unsigned char pBuf[1500];	// [scq/2010-09-17]
	int iLen;
	unsigned long ip;
	unsigned short port;
};
static queue<LogStruct> g_queueLog;
static CRITICAL_SECTION g_LogQueueLock;
static bool g_bIsInit = false;

void PushMsgLog(string sLog, char* pBuf, int iLen, unsigned long ip, unsigned short port)
{
	if (iLen > 1500)
	{
		return;
	}

	if (!g_bIsInit)
	{
		InitializeCriticalSection(&g_LogQueueLock);
		g_bIsInit = true;
	}

	EnterCriticalSection(&g_LogQueueLock);
	if (g_queueLog.size() >= 20)
	{
		g_queueLog.pop();
	}
	LogStruct s;
	s.sLog = sLog;
	memcpy(s.pBuf, pBuf, iLen);
	s.iLen = iLen;
	s.port = port;
	s.ip = ip;
	g_queueLog.push(s);
	LeaveCriticalSection(&g_LogQueueLock);
}

void WriteMsgLog(string sLog, unsigned long ip, unsigned short port)
{
	FILE * fp = fopen("c:\\IbLog.txt","a");
	if(fp == NULL)
	{
		return;
	}

	fprintf(fp, "\r\n\r\n%s(IP:%d; Port:%d)\r\n\r\n", sLog.c_str(), ip, port);

	EnterCriticalSection(&g_LogQueueLock);
	while(!g_queueLog.empty())
	{
		LogStruct& s = g_queueLog.front();

		ostringstream os;
		os << s.sLog << endl;
		fprintf(fp, "%s(IP:%d; Port:%d)\r\n", os.str().c_str(), s.ip, s.port);	// [scq/2010-09-17]
		//char c[4000] = {0};
		unsigned char c[4000] = {0};	// [scq/2010-09-17]
		for (int i = 0; i < s.iLen; i++)
		{
			int iLen = sprintf((char *)(c + i * 2), "%02X", (unsigned int)s.pBuf[i]);
		}
		//os << c << endl << endl;
		//fprintf(fp, "%s\r\n", os.str().c_str());
		fprintf(fp, "%s\r\n", c);	// [scq/2010-09-17]

		g_queueLog.pop();
	}
	LeaveCriticalSection(&g_LogQueueLock);

	fclose(fp);
}
#endif*/

// TestMsgError
struct AgentInfoStruct 
{
	string m_sAgentID;
	string m_sCorporation;
	unsigned long m_ulAgentIP;
	unsigned short m_usAgentPort;
};
static map<string, AgentInfoStruct*> g_mapAgentInfoList;
static CRITICAL_SECTION g_mapAgentInfoListLock;
static bool g_bIsInitEx = false;

void AddAgentInfoToMap(string agentID, string corpName, unsigned long ip, unsigned short port)
{
	if(agentID.length() <= 0 )
	{
		return;
	}

	if (!g_bIsInitEx)
	{
		InitializeCriticalSection(&g_mapAgentInfoListLock);
		g_bIsInitEx = true;
	}

	EnterCriticalSection(&g_mapAgentInfoListLock);
	AgentInfoStruct* pAgentInfo = NULL;
	if(g_mapAgentInfoList.find(agentID) != g_mapAgentInfoList.end())
	{
		pAgentInfo = g_mapAgentInfoList[agentID];
		if(pAgentInfo != NULL)
		{
			pAgentInfo->m_sAgentID = agentID;
			pAgentInfo->m_sCorporation = corpName;
			pAgentInfo->m_ulAgentIP = ip;
			pAgentInfo->m_usAgentPort = port;
			LeaveCriticalSection(&g_mapAgentInfoListLock);
			return;
		}
	}
	pAgentInfo = new AgentInfoStruct();
	pAgentInfo->m_sAgentID = agentID;
	pAgentInfo->m_sCorporation = corpName;
	pAgentInfo->m_ulAgentIP = ip;
	pAgentInfo->m_usAgentPort = port;
	g_mapAgentInfoList.insert(map<string, AgentInfoStruct*>::value_type(agentID, pAgentInfo));
	LeaveCriticalSection(&g_mapAgentInfoListLock);
}

void DelAgentInfoFromMap(string agentID)
{
	if(agentID.length() <= 0 )
	{
		return;
	}

	if (!g_bIsInitEx)
	{
		InitializeCriticalSection(&g_mapAgentInfoListLock);
		g_bIsInitEx = true;
	}

	EnterCriticalSection(&g_mapAgentInfoListLock);
	map<string, AgentInfoStruct*>::iterator pIter = g_mapAgentInfoList.find(agentID);
	if( pIter!=g_mapAgentInfoList.end() )
	{
		AgentInfoStruct* pAgentInfo = (AgentInfoStruct*)pIter->second;
		if(pAgentInfo != NULL)
		{
			delete pIter->second;
		}	
		g_mapAgentInfoList.erase(agentID);
	}
	LeaveCriticalSection(&g_mapAgentInfoListLock);
}

AgentInfoStruct* FindAgentInfoByIP(unsigned long ip, unsigned short port)
{
	if( (ip<=0)||(port<=0)||(port>65535) )
	{
		return NULL;
	}

	if (!g_bIsInitEx)
	{
		InitializeCriticalSection(&g_mapAgentInfoListLock);
		g_bIsInitEx = true;
	}

	EnterCriticalSection(&g_mapAgentInfoListLock);
	map<string, AgentInfoStruct*>::iterator pIter;
	for ( pIter=g_mapAgentInfoList.begin(); pIter!=g_mapAgentInfoList.end(); ++pIter )
	{
		AgentInfoStruct* pAgentInfo = (AgentInfoStruct*)pIter->second;
		if ( pAgentInfo != NULL )
		{
			if ( (pAgentInfo->m_ulAgentIP==ip)&&(pAgentInfo->m_usAgentPort==port) )
			{
				LeaveCriticalSection(&g_mapAgentInfoListLock);
				return pAgentInfo;
			}
		}
	}
	LeaveCriticalSection(&g_mapAgentInfoListLock);

	return NULL;
}

AgentInfoStruct* FindAgentInfoByAgent(string agentID)
{
	if(agentID.length() <= 0)
	{
		return NULL;
	}

	if (!g_bIsInitEx)
	{
		InitializeCriticalSection(&g_mapAgentInfoListLock);
		g_bIsInitEx = true;
	}

	EnterCriticalSection(&g_mapAgentInfoListLock);
	map<string, AgentInfoStruct*>::iterator pIter;
	if((pIter=g_mapAgentInfoList.find(agentID)) == g_mapAgentInfoList.end())
	{
		LeaveCriticalSection(&g_mapAgentInfoListLock);
		return NULL;
	}

	AgentInfoStruct* pAgentInfo = (AgentInfoStruct*)pIter->second;
	if ( pAgentInfo == NULL )
	{
		LeaveCriticalSection(&g_mapAgentInfoListLock);
		return NULL;
	}
	LeaveCriticalSection(&g_mapAgentInfoListLock);

	return pAgentInfo;
}

void WriteMsgError(string msg, string reason, unsigned long ip, unsigned short port, string agentID)
{
	AgentInfoStruct* pAgentInfo = NULL;
	if(agentID.length()>0)
	{
		pAgentInfo = FindAgentInfoByAgent(agentID);
	}
	else
	{
		if( (ip>0)&&(port>0)&&(port<=65535) )
		{
			pAgentInfo = FindAgentInfoByIP(ip, port);
		}
	}

	ostringstream os;
	if ( pAgentInfo==NULL )
	{
		os << GetLocalTimeTemp() << " msg:" << msg 
			<< "; reason:" << reason
			<< "; agentID:" << agentID 
			<< "; ip:" << ip 
			<< "; port:" << port << endl;
	}
	else
	{
		os << GetLocalTimeTemp() << " msg:" << msg 
			<< "; reason:" << reason
			<< "; corpName:" << pAgentInfo->m_sCorporation 
			<< "; agentID:" << pAgentInfo->m_sAgentID 
			<< "; ip:" << pAgentInfo->m_ulAgentIP 
			<< "; port:" << pAgentInfo->m_usAgentPort << endl;
	}

	try{
		FILE * fp;
		//if(fp = fopen(GetMsgLogPath().c_str(),"a"))
		if(fp = fopen(g_strMsgLogPath.c_str(),"a"))
		{
			fprintf(fp,"%s\r\n", os.str().c_str());
			fclose(fp);
		}
	}
	catch(...){}
}

void WriteMsgErrorAcd(string msg, string reason, int currentLen, unsigned long ip, unsigned short port, string agentID)
{
	AgentInfoStruct* pAgentInfo = NULL;
	if(agentID.length()>0)
	{
		pAgentInfo = FindAgentInfoByAgent(agentID);
	}
	else
	{
		if( (ip>0)&&(port>0)&&(port<=65535) )
		{
			pAgentInfo = FindAgentInfoByIP(ip, port);
		}
	}

	ostringstream os;
	if ( pAgentInfo==NULL )
	{
		os << GetLocalTimeTemp() << " msg:" << msg 
			<< "; reason:" << reason
			<< "; currentLen:" << currentLen
			<< "; agentID:" << agentID 
			<< "; ip:" << ip 
			<< "; port:" << port << endl;
	}
	else
	{
		os << GetLocalTimeTemp() << " msg:" << msg 
			<< "; reason:" << reason
			<< "; currentLen:" << currentLen
			<< "; corpName:" << pAgentInfo->m_sCorporation 
			<< "; agentID:" << pAgentInfo->m_sAgentID 
			<< "; ip:" << pAgentInfo->m_ulAgentIP 
			<< "; port:" << pAgentInfo->m_usAgentPort << endl;
	}

	try{
		FILE * fp;
		//if(fp = fopen(GetMsgLogPath().c_str(),"a"))
		if(fp = fopen(g_strMsgLogPath.c_str(),"a"))
		{
			fprintf(fp,"%s\r\n", os.str().c_str());
			fclose(fp);
		}
	}
	catch(...){}
}

void WriteMsgErrorAcd(string msg, string reason, int currentTotalLen, int realTotalLen, unsigned long ip, unsigned short port, string agentID)
{
	AgentInfoStruct* pAgentInfo = NULL;
	if(agentID.length()>0)
	{
		pAgentInfo = FindAgentInfoByAgent(agentID);
	}
	else
	{
		if( (ip>0)&&(port>0)&&(port<=65535) )
		{
			pAgentInfo = FindAgentInfoByIP(ip, port);
		}
	}

	ostringstream os;
	if ( pAgentInfo==NULL )
	{
		os << GetLocalTimeTemp() << " msg:" << msg 
			<< "; reason:" << reason
			<< "; currentTotalLen:" << currentTotalLen
			<< "; realTotalLen:" << realTotalLen
			<< "; agentID:" << agentID
			<< "; ip:" << ip 
			<< "; port:" << port << endl;
	}
	else
	{
		os << GetLocalTimeTemp() << " msg:" << msg 
			<< "; reason:" << reason
			<< "; currentTotalLen:" << currentTotalLen
			<< "; realTotalLen:" << realTotalLen
			<< "; corpName:" << pAgentInfo->m_sCorporation 
			<< "; agentID:" << pAgentInfo->m_sAgentID 
			<< "; ip:" << pAgentInfo->m_ulAgentIP 
			<< "; port:" << pAgentInfo->m_usAgentPort << endl;
	}

	try{
		FILE * fp;
		//if(fp = fopen(GetMsgLogPath().c_str(),"a"))
		if(fp = fopen(g_strMsgLogPath.c_str(),"a"))
		{
			fprintf(fp,"%s\r\n", os.str().c_str());
			fclose(fp);
		}
	}
	catch(...){}
}

void WriteMsgError(string msg, string reason, int currentLen, unsigned long ip, unsigned short port)
{
	ostringstream os;
	os << GetLocalTimeTemp() << " msg:" << msg 
		<< "; reason:" << reason
		<< "; currentLen:" << currentLen
		<< "; ip:" << ip 
		<< "; port:" << port << endl;

	try{
		FILE * fp;
		//if(fp = fopen(GetMsgLogPath().c_str(), "a"))
		if(fp = fopen(g_strMsgLogPath.c_str(),"a"))
		{
			fprintf(fp,"%s\r\n", os.str().c_str());
			fclose(fp);
		}
	}
	catch(...){}
}

void WriteMsgError(string msg, string reason, int currentTotalLen, int realTotalLen, unsigned long ip, unsigned short port)
{
	ostringstream os;
	os << GetLocalTimeTemp() << " msg:" << msg 
		<< "; reason:" << reason
		<< "; currentTotalLen:" << currentTotalLen
		<< "; realTotalLen:" << realTotalLen
		<< "; ip:" << ip 
		<< "; port:" << port << endl;

	try{
		FILE * fp;
		//if(fp = fopen(GetMsgLogPath().c_str(), "a"))
		if(fp = fopen(g_strMsgLogPath.c_str(),"a"))
		{
			fprintf(fp,"%s\r\n", os.str().c_str());
			fclose(fp);
		}
	}
	catch(...){}
}

string GetLocalTimeTemp()
{
	ostringstream strStream;
	SYSTEMTIME t1;
	::GetLocalTime(&t1);
	strStream.str("");

	char year[5];
	char month[3];
	char day[3];
	char hour[3];
	char minute[3];
	char second[3];
	memset(year, 0, 5);
	memset(month, 0, 3);
	memset(day, 0, 3);
	memset(hour, 0, 3);
	memset(minute, 0, 3);
	memset(second, 0, 3);

	sprintf(year, "%4d", t1.wYear);
	sprintf(month, "%02d", t1.wMonth);
	sprintf(day, "%02d", t1.wDay);
	sprintf(hour, "%02d", t1.wHour);
	sprintf(minute, "%02d", t1.wMinute);
	sprintf(second, "%02d", t1.wSecond);

	strStream << year << "-" << month << "-" << day << " ";
	strStream << hour << ":" << minute << ":" << second;

	string sTime = strStream.str();

	return sTime;
}

/*string GetMsgLogPath()
{
	char szFullPath[255];
	char szFileName[255];
	memset(szFullPath, 0, 255);
	memset(szFileName, 0, 255);

	::GetModuleFileName(NULL, szFullPath, 255);
	::_tsplitpath(szFullPath, NULL, NULL, szFileName, NULL);

	string sPathName;
	sPathName = "C:\\" + string(szFileName) + ".txt";

	return sPathName;
}*/

/*bool IsACDServer()
{
	char szFullPath[255];
	char szFileName[255];
	memset(szFullPath, 0, 255);
	memset(szFileName, 0, 255);

	::GetModuleFileName(NULL, szFullPath, 255);
	::_tsplitpath(szFullPath, NULL, NULL, szFileName, NULL);

	if ( 0==strcmp(szFileName, "ACDServer") )
	{
		return true;
	}

	return false;
}*/

/*
VerifyData:
	currentLen: 当前需要校验的字段长度
	maxLen: 当前字段最大长度
	msg: 信令名称
	field: 需要校验的字段名称
	ip: 源IP
	port: 源端口
	agentID: 发送信令的座席ID（不是必须的，主要是ACDServer）
*/
bool VerifyData(int currentLen, int maxLen, string msg, string field, unsigned long ip, unsigned short port, bool isAcd, string agentID)
{
	if ( (currentLen>maxLen)||(currentLen<0) )
	{
		if ( !(msg.empty()) )
		{
			if ( isAcd )
			{
				WriteMsgErrorAcd(msg, field + "is error", currentLen, ip, port, agentID);
			}
			else
			{
				WriteMsgError(msg, field + "is error", currentLen, ip ,port);
			}
		}
		return false;
	}

	return true;
}

/*
VerifyData:
	currentTotalLen: 已解析的包长
	realPackLen: 实际包的总长	
	msg: 信令名称
	field: 需要校验的字段名称	
	ip: 源IP
	port: 源端口
	agentID: 发送信令的座席ID（不是必须的，主要是ACDServer）
*/
bool VerifyTotalLen(int currentTotalLen, int realPackLen, string msg, string field, unsigned long ip, unsigned short port, bool isAcd, string agentID)
{
	if ( (currentTotalLen>realPackLen)||(realPackLen<=0) )
	{
		if ( isAcd )
		{
			WriteMsgErrorAcd(msg, field + "is error(currentTotalLen>realTotalLen)", currentTotalLen, realPackLen, ip, port, agentID);
		}
		else
		{
			WriteMsgError(msg, field + "is error(currentTotalLen>realTotalLen)", currentTotalLen, realPackLen, ip ,port);
		}
		return false;
	}

	return true;
}
// TestMsgError

void FixPhoneNo(char* src, char* dest)
{
	char* p = NULL;

	if( (src==NULL) || (dest==NULL) )
		return;

	strcpy( dest, src );

	size_t srclen = strlen( src );

	if( (srclen<1) || (src[0] == '0') || (srclen<=8) || (srclen>12))
		return;

	if( srclen == 12 )
		p = &src[1];
	else
		p = src;

	if( (strlen(p) == 11) &&
		(src[0] == '1') && 
		(src[1] != '0') )
        return;

	dest[0] = '0';

	strcpy( &dest[1], src );   
}

char skey[] = "jklsgfjklmzvm,>a3fjkl@sf4iwioer2.;349723fsdff";
int encrypt_string(const char *string, int buflen, char*& encstring)
{
	int i=0;
	int j=strlen(skey);
	
	for(;i<buflen;i++) 
	{
		int k = i/j;
		if(i>=j)
		{
			encstring[i]= (string[i] ^ skey[i-j*k]) + i % j;
		}
		else
		{
			encstring[i]= (string[i] ^ skey[i]) + i;
		}
		
	} 
	
	encstring[buflen] = '\0'; 
	return buflen;
}

int decrypt_string(const char *string, int length, char*& decstring)
{
	int j=strlen(skey);
	
	for(int i=0; i<length ; i++)
	{
		int k = i/j;
		if(i>=j)
		{
			decstring[i]= (string[i]-i % j) ^ skey[i-j*k];
		}
		else
		{
			decstring[i]= (string[i] -i)^ skey[i];
		}
	}
	decstring[length] = '\0';
	return length;
}

string GetNewVersionInvokeID(unsigned long myIP)
{
	static unsigned long loopup = 0;

	_timeb systime;
	_ftime(&systime);		
	static long lTime = (long)systime.time;
	static short iMillitm = (short)systime.millitm;

	if ( myIP == 0 )
	{
		srand(lTime);
	}
	else
	{
		srand(myIP);
	}
	static short iRand = rand() % 1000;

	char c[30] = {0};
	int iLen = sprintf(c,"N%08X%04X%04X%08X", lTime, iMillitm, iRand, loopup );

	loopup++;

	return c;
}