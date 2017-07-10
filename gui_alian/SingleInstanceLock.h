#pragma once


/**��ʵ��������������ϵͳֻ���г����һ��ʵ������֧���Զ�������һ�����е�ʵ��
*/
class SingleInstanceLock
{
public:
	SingleInstanceLock();
	~SingleInstanceLock();

	/**�������������������FALSE����ʾ�Ѿ���ʵ�������У�Ӧ���˳���ǰ��ʵ����
	   szApplicationLockName: ��������ƣ���ע��һ��ͬ���Ĵ�����;
	   bUseClassName: �Ƿ�ʹ�ô����������Ҵ��ڣ�
	*/
	BOOL Create( LPCSTR szApplicationLockName,BOOL bUseClassName, 
		LPCSTR szWindowsName= NULL,UINT iShowMode=SW_RESTORE);

	CString	GetClassName() const{
		return m_strClassName;
	};

protected:
	HANDLE	m_hMutex;
	CString	m_strClassName;
};
