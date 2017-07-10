#pragma once


/**单实例锁，可以锁定系统只运行程序的一个实例，并支持自动激活上一个运行的实例
*/
class SingleInstanceLock
{
public:
	SingleInstanceLock();
	~SingleInstanceLock();

	/**创建进程锁，如果返回FALSE，表示已经有实例在运行，应该退出当前的实例。
	   szApplicationLockName: 程序的名称，并注册一个同名的窗口类;
	   bUseClassName: 是否使用窗口类名查找窗口；
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
