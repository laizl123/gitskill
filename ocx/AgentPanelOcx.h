#if !defined(AFX_AGENTPANELOCX_H__D6A0606A_BD21_4AA6_835E_38FD59C7B773__INCLUDED_)
#define AFX_AGENTPANELOCX_H__D6A0606A_BD21_4AA6_835E_38FD59C7B773__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// AgentPanelOcx.h : main header file for AGENTPANELOCX.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAgentPanelOcxApp : See AgentPanelOcx.cpp for implementation.

class CAgentPanelOcxApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AGENTPANELOCX_H__D6A0606A_BD21_4AA6_835E_38FD59C7B773__INCLUDED)
