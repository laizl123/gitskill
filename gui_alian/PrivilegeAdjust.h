// PrivilegeAdjust.h: interface for the CPrivilegeAdjust class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRIVILEGEADJUST_H__8E416E5B_3698_4C5C_A453_CD754A2A91A2__INCLUDED_)
#define AFX_PRIVILEGEADJUST_H__8E416E5B_3698_4C5C_A453_CD754A2A91A2__INCLUDED_

class CPrivilegeAdjust  
{
public:
	CPrivilegeAdjust();

	virtual ~CPrivilegeAdjust();
public:
	// 是否允许运行程序
	static BOOL IsHasPrivilege();
	static BOOL IsHasPrivilege(LPCWSTR szUser);
	// 得到有权限的用户
	static void GetPrivilegeUser(CStringArray& arrUser);
	// 提升用户权限
	static BOOL SetThreadPrivilege(CString& strUser, CString& strPswd);
	// 得到和保存用户权限
	static BOOL GetPrivilegeInfo(CString& strUser, CString& strPswd);
	static BOOL SavePrivilegeInfo(CString& strUser, CString& strPswd);
public:
	static BOOL AdjustPrivilege();

public:
	static CString m_strUser;
	static CString m_strPwd;

};

#endif // !defined(AFX_PRIVILEGEADJUST_H__8E416E5B_3698_4C5C_A453_CD754A2A91A2__INCLUDED_)
