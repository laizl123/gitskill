// FuncReturnObject.h: interface for the CFuncReturnObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FUNCRETURNOBJECT_H__BEC74D36_D61D_4C3E_8106_65C4CBF7EE97__INCLUDED_)
#define AFX_FUNCRETURNOBJECT_H__BEC74D36_D61D_4C3E_8106_65C4CBF7EE97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <comdef.h>

class CFuncReturnObject  
{
public:
	CFuncReturnObject();
	virtual ~CFuncReturnObject();

	const CFuncReturnObject& operator=(const CFuncReturnObject& info);	
	CFuncReturnObject(const CFuncReturnObject& info);
public:
	// FUNCTION ID
	UINT		m_nFuncdispID;
	// 序列号
	CString		m_nSeqenceID;
	// 事件
	HANDLE		m_hWaitEvent;
	// 窗口
	HWND		m_hMsgWnd;
	// 返回值
	_variant_t	m_varReturn;
};

#endif // !defined(AFX_FUNCRETURNOBJECT_H__BEC74D36_D61D_4C3E_8106_65C4CBF7EE97__INCLUDED_)
