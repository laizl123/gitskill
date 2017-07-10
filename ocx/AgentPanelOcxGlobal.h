// AgentPanelOcxGlobal.h: interface for the CAgentPanelOcxGlobal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AGENTPANELOCXGLOBAL_H__3E8DAC85_A1AC_4006_96A7_270A5B7338A7__INCLUDED_)
#define AFX_AGENTPANELOCXGLOBAL_H__3E8DAC85_A1AC_4006_96A7_270A5B7338A7__INCLUDED_

#include "GlobalOperation.h"

CString GetMoudlePath();
CString GetDataFilesPath();
BOOL KillTheProcess(CString exeName);
BOOL StartTheProcess(CString fileName,string s_port);
BOOL QueryProcessExsit(CString fileName);

#endif // !defined(AFX_AGENTPANELOCXGLOBAL_H__3E8DAC85_A1AC_4006_96A7_270A5B7338A7__INCLUDED_)
