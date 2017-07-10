// ResourceItem.h: interface for the CResourceItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESOURCEITEM_H__2FA5BFD4_BBAC_4BC4_9831_86CD75E247AE__INCLUDED_)
#define AFX_RESOURCEITEM_H__2FA5BFD4_BBAC_4BC4_9831_86CD75E247AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define RES_TYPE_TEXT	0x01
#define RES_TYPE_IMAGE	0x02
#define RES_TYPE_ICON	0x03

#include "XMLDOMInterface.h"

//CString GetAppPath();


class CResourceItem  
{
public:	
	virtual ~CResourceItem();
	CResourceItem(UINT iType);

public:
	virtual bool ReadResource(CXMLDOMInterface& Dom,IXMLDOMNode* pXMLNode) = 0;
	virtual void FreeResource() = 0;
public:
	UINT m_iResourceType;	

};

#endif // !defined(AFX_RESOURCEITEM_H__2FA5BFD4_BBAC_4BC4_9831_86CD75E247AE__INCLUDED_)
