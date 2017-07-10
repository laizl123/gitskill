#pragma once

#include "ui/ManageChatWindow.h"
#include "ChatWindowMsgHandle.h"
using namespace std;

class CChatThread
{
    public:
        CChatThread(void);
        ~CChatThread(void);

    public:
        int StartThread();
        int StopThread();

        DWORD GetThreadId() const;
        DWORD  GetChatWindowThreadId() const;

        void AddQTBMessage(MESSAGE_ENTITY msg);
        function<void(tstring name)> pSetClientName;//≤‚ ‘”√
    private:
        int  ThreadProcess();
    private:
        bool     m_bRunning;
        thread   m_MainThread;
        DWORD    m_ThreadId;
        DWORD    m_WindowThreadId;
        HWND     m_ChatWindowHwnd;

        function<void(MESSAGE_ENTITY msg)> pQTBMsgFun;

};

