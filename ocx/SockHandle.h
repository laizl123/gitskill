// SockHandle.h: interface for the CSockHandle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOCKHANDLE_H__48E3CBE0_6FF6_49E1_B050_B52E797DC1E9__INCLUDED_)
#define AFX_SOCKHANDLE_H__48E3CBE0_6FF6_49E1_B050_B52E797DC1E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSockHandle  
{
public:
	CSockHandle();
	virtual ~CSockHandle();
public:
	virtual void HandleRecvMsg(char* data, int nlen) = 0;
	virtual void HandleHeartTimeOut() = 0;

};

#endif // !defined(AFX_SOCKHANDLE_H__48E3CBE0_6FF6_49E1_B050_B52E797DC1E9__INCLUDED_)
