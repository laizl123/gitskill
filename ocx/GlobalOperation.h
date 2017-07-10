#ifndef __GLOBALOPERATION__H__
#define __GLOBALOPERATION__H__

#include <iostream>
#include <sstream>
#include <deque>
#include <string>
using namespace std;


#define _Media_Video 0
#define _Media_Audio 1

#define WM_MEDIADATA_LOSTRATE WM_USER+601

long filesize(FILE *stream);

string GetAppPath();
bool CreateMultipleLevelDirectory(string strDir);
unsigned long ConvertIP(string ip);
unsigned short ConvertPort(int port);
string GetLocalIP();
string IntToString(int ivalue);
bool IsMediaData(const char *buf, int size);

void GetIPConfigInfo();
string GetPhysicalAddrByIP(string ip);
string GetGateWayeInfoByIP(string ip);
bool IsLanIP(string ip);

void Multi_TerminateThread(HANDLE& handle);
void Multi_TerminateTimer(HWND hWnd, int& nTimerID);

string ConvertNatIP2HostIP(unsigned long ip);
int ConvertNatPort2HostPort(unsigned short port);
unsigned long ConvertNatIP2HostIPi(unsigned long ip);

void MySleep(int msCount);
unsigned short GetRandomPort();

int GetLocalTimeInfo(int& hour, int& minute, int& second);

class CCreditUDP;
struct SIPCCMessage;
void SendIPCCMsg(CCreditUDP* pSocket, SIPCCMessage* pMsg, unsigned long iIp, unsigned short iPort);

string getmac_one (int lana_num);

int CalTimeSpan(int begin, int end);

void convert8to16(unsigned char* pre_data, int size, short* post_data);
void convert16to8(short* pre_data, int size, unsigned char* post_data);

static short search(
					int		val,				/* changed from "short" *drago* */
					short	*table,
					int		size);
static inline unsigned char linear2alaw(int pcm_val);
int linear2pcma(unsigned char* pOut, short* pIn, int iSizeIn);

void StringMakeLower(string &originString);
void StringMakeUpper(string &originString);

string NewGlobalInvokeID();


string DecryptBase64NDes(string sCode, char sKey[8]);
bool IsMobilePhone(string sPhone);
bool IsLocolPhone(string sPhone, string sLocolCode);

/*
#ifdef MAKEMSGLOG
void PushMsgLog(string sLog, char* pBuf, int iLen, unsigned long ip=0, unsigned short port=0);
void WriteMsgLog(string sLog, unsigned long ip=0, unsigned short port=0);
#endif
*/

// TestMsgError
struct AgentInfoStruct;
void AddAgentInfoToMap(string agentID, string corpName, unsigned long ip, unsigned short port);
void DelAgentInfoFromMap(string agentID);
AgentInfoStruct* FindAgentInfoByIP(unsigned long ip, unsigned short port);
AgentInfoStruct* FindAgentInfoByAgent(string agentID);
void WriteMsgError(string msg, string reason, unsigned long ip=0, unsigned short port=0, string agentID="");
void WriteMsgErrorAcd(string msg, string reason, int currentLen, unsigned long ip=0, unsigned short port=0, string agentID="");
void WriteMsgErrorAcd(string msg, string reason, int currentTotalLen, int realTotalLen, unsigned long ip=0, unsigned short port=0, string agentID="");
void WriteMsgError(string msg, string reason, int currentLen, unsigned long ip=0, unsigned short port=0);
void WriteMsgError(string msg, string reason, int currentTotalLen, int realTotalLen, unsigned long ip=0, unsigned short port=0);
string GetLocalTimeTemp();
//string GetMsgLogPath();
//bool IsACDServer();
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
bool VerifyData(int currentLen, int maxLen, string msg="", string field="", unsigned long ip=0, unsigned short port=0, bool isAcd=false, string agentID="");
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
bool VerifyTotalLen(int currentTotalLen, int realPackLen, string msg, string field, unsigned long ip=0, unsigned short port=0, bool isAcd=false, string agentID="");
void FixPhoneNo(char* src, char* dest);

int encrypt_string(const char *string, int buflen, char*& encstring);
int decrypt_string(const char *string, int length, char*& decstring);

string GetNewVersionInvokeID(unsigned long myIP=0);

#endif // __GLOBALOPERATION__H__