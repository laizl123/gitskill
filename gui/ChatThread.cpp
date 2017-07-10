#include "StdAfx.h"
#include "ChatThread.h"
#include "resource.h"
#include "unity/Path.h"
#include "unity/Utils.h"
#include "ImChat.h"


extern HMODULE global_hModule;

Gdiplus::GdiplusStartupInput g_gdiplusStartupInput;
ULONG_PTR g_gdiplusToken;


CChatThread::CChatThread(void)
{
    m_bRunning = false;
    m_ThreadId = 0;
    m_ChatWindowHwnd = NULL;
}


CChatThread::~CChatThread(void)
{
}

int CChatThread::StartThread()
{
    if(m_bRunning == true)
        {
            return  1;
        }

    std::thread thread(&CChatThread::ThreadProcess, this);
    m_MainThread.swap(thread);

    return 0;
}

int CChatThread::StopThread()
{
    if(!m_bRunning)
        return S_FALSE;

    PostThreadMessage(m_ThreadId, WM_QUIT, 0, 0);
    m_bRunning = false;
    m_MainThread.join();
    return S_OK;
}

int CChatThread::ThreadProcess()
{

    m_bRunning = true;

    tstring strFileName = unity::CPath::GetAppPath() + _T("ImageOleCtrl.dll");

    BOOL bRet = DllRegisterServer(strFileName.c_str());	// 注册COM组件

    if(!bRet)
        {
            ::MessageBox(NULL, _T("COM组件注册失败，应用程序无法完成初始化操作！"), _T("提示"), MB_OK);
            return 0;
        }

    HRESULT hr = ::OleInitialize(NULL);

    if(FAILED(hr))
        return 0;

    GdiplusStartup(&g_gdiplusToken, &g_gdiplusStartupInput, NULL);	// 初始化GDI+

    HMODULE hRichEditDll = ::LoadLibrary(_T("Riched20.dll"));	// 加载RichEdit控件DLL

    CPaintManagerUI::SetInstance(global_hModule);
    CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());

    m_ThreadId = GetCurrentThreadId();

    {
        unique_ptr<CChatWindowMsgHandle> pChatWindowMsgHandle = NULL;
        pChatWindowMsgHandle.reset(new CChatWindowMsgHandle);

        if(pChatWindowMsgHandle)
            {
                pChatWindowMsgHandle->StartThread();
                m_WindowThreadId = pChatWindowMsgHandle->GetThreadId();

                pQTBMsgFun = bind(&CChatWindowMsgHandle::AddQTBMessage, pChatWindowMsgHandle.get(), std::placeholders::_1);
            }


        unique_ptr<ManageChatWindow> pManageChatWindow = NULL;
        pManageChatWindow.reset(new ManageChatWindow);

        if(pManageChatWindow && pChatWindowMsgHandle)
            {
                pManageChatWindow->CreateWindows();
                //pManageChatWindow->ShowWindow(NOTIFY);
                //pManageChatWindow->ShowWindow(WORKMATE);
                pManageChatWindow->SetCallBackFunction(std::bind(&CChatWindowMsgHandle::SendMessageToIM,
                                                       pChatWindowMsgHandle.get(),
                                                       std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));


                //将窗口的回调函数传给IM
                pChatWindowMsgHandle->SetWindowCallBackFuncion(std::bind(&ManageChatWindow::AddMessageToChatWindow, pManageChatWindow.get(), std::placeholders::_1));

                pSetClientName = bind(&ManageChatWindow::SetClientName, pManageChatWindow.get(), std::placeholders::_1);
            }

        CPaintManagerUI::MessageLoop();
    }

    CPaintManagerUI::Term();
    WindowImplBase::Cleanup();

    if(hRichEditDll != NULL)					// 卸载RichEdit控件DLL
        ::FreeLibrary(hRichEditDll);

    Gdiplus::GdiplusShutdown(g_gdiplusToken);	// 反初始化GDI+
    ::OleUninitialize();
    _CrtDumpMemoryLeaks();
    return S_OK;
}

DWORD CChatThread::GetThreadId() const
{
    return m_ThreadId;
}

DWORD CChatThread::GetChatWindowThreadId() const
{
    return m_WindowThreadId;
}

void CChatThread::AddQTBMessage(MESSAGE_ENTITY msg)
{
    if(pQTBMsgFun)
        {
            pQTBMsgFun(msg);
        }
}


