// IniFile.h: interface for the CMyIniFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIFILE_H__4CED25EE_852D_4AD0_89E9_2631DE427A43__INCLUDED_)
#define AFX_INIFILE_H__4CED25EE_852D_4AD0_89E9_2631DE427A43__INCLUDED_

class CMyIniFile  
{
public:
	CMyIniFile(const CString& file = "");
	virtual ~CMyIniFile();
public:
	// �ļ�����
	CString m_strFileName;
	void SetFileName(CString& file)
	{
		m_strFileName = file;
	}
	const CString& GetFileName()
	{
		return m_strFileName;
	}
	// �õ���������
	UINT GetProfileInt(const CString& strSection,
		const CString& strKeyName,
		UINT nDefault);
	// �õ��ַ�������
	const CString GetProfileString(const CString& strSection,
		const CString& strKeyName,
		const CString& strDefault);
	// д������
	BOOL WriteProfileString(const CString& strSection,
		const CString& strKeyName,
		const CString& strData);
};

#endif // !defined(AFX_INIFILE_H__4CED25EE_852D_4AD0_89E9_2631DE427A43__INCLUDED_)
