// RegXVID.h: interface for the CRegXVID class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGXVID_H__B033273D_0892_4DE3_8E47_78821E2EB97C__INCLUDED_)
#define AFX_REGXVID_H__B033273D_0892_4DE3_8E47_78821E2EB97C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRegXVID  
{
public:
	CRegXVID();
	virtual ~CRegXVID();
public:
	bool DisplayXVIDStatus(bool bShow);
	bool XVIDRegistry();
};

#endif // !defined(AFX_REGXVID_H__B033273D_0892_4DE3_8E47_78821E2EB97C__INCLUDED_)
