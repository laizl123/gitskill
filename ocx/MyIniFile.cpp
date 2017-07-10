// IniFile.cpp: implementation of the CMyIniFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyIniFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyIniFile::CMyIniFile(const CString& file)
{
	m_strFileName = file;	
}

CMyIniFile::~CMyIniFile()
{

}
/************************************************************************/
// �õ���������
/************************************************************************/
UINT CMyIniFile::GetProfileInt(const CString& strSection,
							 const CString& strKeyName,
							 UINT nDefault)
{
	return GetPrivateProfileInt(strSection, strKeyName, nDefault, m_strFileName);
}
/************************************************************************/
// �õ��ַ�������
/************************************************************************/
const CString CMyIniFile::GetProfileString(const CString& strSection,
										 const CString& strKeyName,
										 const CString& strDefault)
{
	char szData[_MAX_PATH];
	memset(szData, 0, sizeof(szData));
	// �õ�����
	GetPrivateProfileString(strSection,
		strKeyName,
		strDefault,
		szData,
		sizeof(szData),
		m_strFileName);
	return szData;
}
/************************************************************************/
// д������
/************************************************************************/
BOOL CMyIniFile::WriteProfileString(const CString& strSection,
								  const CString& strKeyName,
								  const CString& strData)
{
	WritePrivateProfileString(strSection, strKeyName, strData, GetMoudlePath() + "\\Disco_Client.ini");
	return WritePrivateProfileString(strSection, strKeyName, strData, m_strFileName);
}