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
	// �Ƿ��������г���
	static BOOL IsHasPrivilege();
	static BOOL IsHasPrivilege(LPCWSTR szUser);
	// �õ���Ȩ�޵��û�
	static void GetPrivilegeUser(CStringArray& arrUser);
	// �����û�Ȩ��
	static BOOL SetThreadPrivilege(CString& strUser, CString& strPswd);
	// �õ��ͱ����û�Ȩ��
	static BOOL GetPrivilegeInfo(CString& strUser, CString& strPswd);
	static BOOL SavePrivilegeInfo(CString& strUser, CString& strPswd);
public:
	static BOOL AdjustPrivilege();

public:
	static CString m_strUser;
	static CString m_strPwd;

};

#endif // !defined(AFX_PRIVILEGEADJUST_H__8E416E5B_3698_4C5C_A453_CD754A2A91A2__INCLUDED_)
