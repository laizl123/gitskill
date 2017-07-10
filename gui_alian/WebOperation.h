// WebOperation.h: interface for the CWebOperation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WEBOPERATION_H__737F10B6_CC9F_49E5_8734_DD874F3D38DD__INCLUDED_)
#define AFX_WEBOPERATION_H__737F10B6_CC9F_49E5_8734_DD874F3D38DD__INCLUDED_

#include "WinDef.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxhtml.h>
#include <exdispid.h>
#include <tlogstg.h>

#include <string>
using namespace std;

class CWebOperation  
{
public:
	static BOOL XTools(IHTMLDocument2* pDocument2, string sUserName, string sPassword, BOOL bAutoLogin=FALSE);

	CWebOperation();
	virtual ~CWebOperation();

};

#endif // !defined(AFX_WEBOPERATION_H__737F10B6_CC9F_49E5_8734_DD874F3D38DD__INCLUDED_)
