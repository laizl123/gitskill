// ResourceItem.cpp: implementation of the CResourceItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ResourceItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// 
// CString GetAppPath()
// {
// 	char szFullPath[255];
// 	char szDir[255];
// 	char szDrive[255];
// 	
// 	memset(szFullPath, 0, 255);
// 	memset(szDir, 0, 255);
// 	memset(szDrive, 0, 255);
// 	
// 	::GetModuleFileName(NULL,szFullPath,255);
// 	::_tsplitpath(szFullPath,szDrive,szDir,NULL,NULL);
// 	
// 	CString sPathName;
// 	sPathName = CString(szDrive) + CString(szDir);
// 	
// 	if( sPathName[sPathName.GetLength()-1] != '\\' )
// 		sPathName += "\\";
// 	
// 	return sPathName;
// }

CResourceItem::CResourceItem(UINT iType) : 
m_iResourceType(iType)
{

}

CResourceItem::~CResourceItem()
{

}
