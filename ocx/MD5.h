// MD5.h: interface for the MD5 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MD5_H__5CE48E71_D011_48D7_8DDF_BEAAB79F62B1__INCLUDED_)
#define AFX_MD5_H__5CE48E71_D011_48D7_8DDF_BEAAB79F62B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include"MD5_CTX.h"

class MD5  
{
public:
 MD5();
 void MD5Init (MD5_CTX * context);
 void MD5Update(MD5_CTX *context,unsigned char * input,unsigned int  inputLen);
 void MD5Final (unsigned char digest[],MD5_CTX * context);
 static void MD5Transform (UINT4 state[],unsigned char block[]);
 static void Encode (unsigned char *output,UINT4 * input,unsigned int len);
 static void Decode (UINT4 *output,unsigned char * input,unsigned int len);
 static void MD5_memcpy (POINTER output,POINTER value,unsigned int len);
 static void MD5_memset (POINTER output,int value,unsigned int len);
 BOOL MD5Hash(CString m_EditIn,TCHAR szBuffer[]) ;
 virtual ~MD5();

};



#endif // !defined(AFX_MD5_H__5CE48E71_D011_48D7_8DDF_BEAAB79F62B1__INCLUDED_)
