// AgentPanelOcxHead.h: interface for the CAgentPanelOcxHead class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AGENTPANELOCXHEAD_H__82E00540_0308_40B1_B90C_FB7B9969B639__INCLUDED_)
#define AFX_AGENTPANELOCXHEAD_H__82E00540_0308_40B1_B90C_FB7B9969B639__INCLUDED_

// 心跳发送时间
#define TIME_HEARTBEAT_SEND 2000
// 心跳超时时间
#define TIMEOUT_HEARTBEAT	10000
// 等待函数返回超时
#define TIMEOUT_WAITFUNC	5000
// FUNCTION的数据缓冲区
#define SIZE_FUNCBUF		1024
// FUNCTION的数据缓冲区
#define TIME_HEARTCHECK		1000

// 消息响应
#define WM_HIDEDLG	WM_USER+100  
#define WM_SOCKMSG	WM_USER+101


#endif // !defined(AFX_AGENTPANELOCXHEAD_H__82E00540_0308_40B1_B90C_FB7B9969B639__INCLUDED_)
