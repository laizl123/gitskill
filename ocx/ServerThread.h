#if !defined(AFX_SERVERTHREAD_H__9705F883_4DCA_40A8_8FA2_F80806CD9AA2__INCLUDED_)
#define AFX_SERVERTHREAD_H__9705F883_4DCA_40A8_8FA2_F80806CD9AA2__INCLUDED_

/////////////////////////////////////////////////////////////////////////////
// CServerThread thread

class CServerThread : public CWinThread
{
	DECLARE_DYNCREATE(CServerThread)
protected:
	CServerThread();           // protected constructor used by dynamic creation

// Attributes
public:
	void StopThread();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CServerThread();

	// Generated message map functions
	//{{AFX_MSG(CServerThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

protected:
	// 停止线程
	BOOL  m_bStopThread;
public:
	// 消息通信窗口
	CWnd* m_pMessageWnd;
	UINT  m_uMessageID;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERTHREAD_H__9705F883_4DCA_40A8_8FA2_F80806CD9AA2__INCLUDED_)
