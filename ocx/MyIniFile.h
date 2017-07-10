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
	// 文件名称
	CString m_strFileName;
	void SetFileName(CString& file)
	{
		m_strFileName = file;
	}
	const CString& GetFileName()
	{
		return m_strFileName;
	}
	// 得到整数数据
	UINT GetProfileInt(const CString& strSection,
		const CString& strKeyName,
		UINT nDefault);
	// 得到字符串数据
	const CString GetProfileString(const CString& strSection,
		const CString& strKeyName,
		const CString& strDefault);
	// 写入数据
	BOOL WriteProfileString(const CString& strSection,
		const CString& strKeyName,
		const CString& strData);
};

#endif // !defined(AFX_INIFILE_H__4CED25EE_852D_4AD0_89E9_2631DE427A43__INCLUDED_)
