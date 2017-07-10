#pragma once
#include <functional>
#include <list>
#include <mutex>
#include <map>
#include <memory>
#include <thread>
#include "ImChat.h"
#include "ChatCBImpl.h"

#include "message/MessageQueue.h"

typedef std::function < void(const string content)> WindowCallBack;

class CChatWindowMsgHandle : public CChatCBImpl
{
    public:
        CChatWindowMsgHandle();
        virtual ~CChatWindowMsgHandle();

        int StartThread();
        int StopThread();
        DWORD GetThreadId() const;
        void SendMessageToIM(int type, tstring name, tstring content);
        void SetWindowCallBackFuncion(const WindowCallBack pWindowCallBack);
        //添加启通宝消息
        void AddQTBMessage(MESSAGE_ENTITY msg);
    public:
        //回调函数
        void CBOnNewMessage(TIMMessageHandle* handles, uint32_t msg_num, void* data);
        void CBConnOnConnected(void * data);
        void CBConnOnDisconnected(void *data);
        void CBKickOffLine(void *data);
        void LoginOnSuccess(void *data);
        void	LoginOnError(int code, const char* desc, void* data);
        void LogoutOnSuccess(void *data);
        void LogoutOnError(int code, const char* desc, void* data);
        void GetFriendListCallbackOnSuccess(void** handles, uint32_t num,  void* data);
        void GetFriendListCallbackOnError(int code, const char* desc, void*  data);
        void SendTxtMsgOnSuccess(void* data) ;
        void SendTxtMsgError(int code, const char* desc, void* data);
        void SendPicMsgOnSuccess(void* data) ;
        void SendPicMsgError(int code, const char* desc, void *data);
        void RecvPicMsgOnSucess(void *data);
        void RecvPicMsgError(int code, const char* desc, void* data);
        void CBGetMsgOnSuccess(TIMMessageHandle* handle_array, int size, void* data);
        void CBGetMsgOnError(int code, const char* desc, void* data);
        void CBOnSuccess(void *data);
        void CBOnError(int code, const char* desc, void* data);
        void CBGetSelfProfileCallbackOnSuccess(TIMSelfProfileHandle* handles, uint32_t num, void* data);
        void CBGetSelfProfileCallbackOnError(int code, const char* desc, void* data);
        void CBGetFriendProfileCallbackOnSuccess(TIMFriendProfileHandle* handles, uint32_t num, void* data);
        void CBGetFriendProfileCallbackOnError(int code, const char* desc, void* data);
        void CBGetLocalMsgOnSuccess(TIMMessageHandle* handle_array, int size, void* data);
        void CBGetLocalMsgOnError(int code, const char* desc, void* data);
    protected:

        //消息处理
        void HandleThreadMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
        void HandldRecvMsg();
        void HandldQTBMsg();
        void HandleLocalMsg();
        void RecvTxtMessage(const TIMMessageHandle handle, bool bLocalMsg = false);
        void RecvPicMessage(const TIMMessageHandle handle, bool bLocalMsg = false);
        void RecvFaceMessage(const TIMMsgFaceElemHandle handle);
        void SendPicMessage(tstring name, tstring txt);
        void SendFaceMessage(tstring name, tstring txt);
        void GetSelfProfile();
        void GetLocalStoreMsgs(tstring name, int count, TIMMessageHandle last_msg);

        string GetItemContent(const TIMMsgTextElemHandle handle);
        string GetItemUser(const TIMMsgTextElemHandle handle);
        string GetItemTime(const TIMMsgTextElemHandle handle);
        string GetTxtContent(const string content);
        string GetPicContent(const string content);

        int ThreadProcess();
        int GetMessageType(tstring msg);
    protected:
        unique_ptr<CImChat> m_pImChat;
        std::list<TIMMessageHandle> m_RecvMsgHandleList;
        TIMSelfProfileHandle     m_TIMSelfProfileHandle;
        std::mutex  m_imtx;
        //图片缓存路径，先写到这里，以后有合适的的地方再移动吧，不纠结了。
        tstring  m_strCachePicPath;
        //存储每个ID获取本地会话的last_name
        std::mutex  m_LocalMsgMtx;
        std::map<tstring, TIMMessageHandle> m_Map_Name_TIMmsg;
        std::string                         m_LocalMsgUserName;
    private:
        bool     m_bRunning;
        DWORD    m_ThreadId;
        thread   m_MainThread;
        ChatCallBack m_ChatCallBack;
        WindowCallBack m_WindowCallBack;

        //与启通宝通讯消息存放
        std::list<MESSAGE_ENTITY> m_MessageEntityList;

        std::mutex  m_metx;
        std::string m_CurrentAgentName;
        std::string m_NickName;
};

