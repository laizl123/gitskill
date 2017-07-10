// Resources.h: interface for the CResources class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESOURCES_H__82F2B18E_D878_4704_80B7_5A3C4B0771F8__INCLUDED_)
#define AFX_RESOURCES_H__82F2B18E_D878_4704_80B7_5A3C4B0771F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <map>
using namespace std;

#include "TextResource.h"
#include "IconResource.h"
#include "ImageResource.h"

class CResources  
{
public:
	CResources();
	virtual ~CResources();

public:
	static bool LoadResources(CString strXMLFile);
	static void FreeResources();
	
	static HBITMAP GetImageResource(CString sImageName);
	static HICON GetIconResource(CString sIconName);
	static CString GetTextResource(CString sTextName);

public:
	static CTextResource* m_pTextResource;
	static CImageResource* m_pImageResource;
	static CIconResource* m_pIconResource;

};

#endif // !defined(AFX_RESOURCES_H__82F2B18E_D878_4704_80B7_5A3C4B0771F8__INCLUDED_)
