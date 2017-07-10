#include "stdafx.h"
#include "ImChat.h"
#include "IMlibs/c_includes/tim_c.h"
#include "unity/CommonDef.h"
#include "unity/Utils.h"
CImChat::CImChat()
{

    memset(&chatCallBack, 0, sizeof(ChatCallBack));

    TIMSetEnv(0); //设置为测试环境
    TIMSetMode(1);
    TIMSetPath(UnicodeToAnsi(GetDataFilesPath()).c_str());
    DWORD res = 0;
    res = TIMInit();//在使用SDK进一步操作之前，需要初始SDK
}


CImChat::~CImChat()
{

    Logout();
    TIMUninit();
}

int CImChat::Login(int sdk_app_id, const TIMUserInfo *tim_user, const char* user_sig)
{
    if(chatCallBack.pCBLoginOnError == NULL || chatCallBack.pCBLoginOnSuccess == NULL)
        return 0;

    TIMCommCB callback;
    callback.OnError = chatCallBack.pCBLoginOnError;
    callback.OnSuccess = chatCallBack.pCBLoginOnSuccess;
    int res = TIMLogin(sdk_app_id, tim_user, user_sig, &callback);
    Sleep(1);
    return res;
}

void CImChat::Logout()
{
    if(chatCallBack.pCBLogoutOnSuccess == NULL || chatCallBack.pCBLogoutOnError == NULL)
        return ;

    TIMCommCB callback;
    callback.OnSuccess = chatCallBack.pCBLogoutOnSuccess;
    callback.OnError = chatCallBack.pCBLogoutOnError;
    TIMLogout(&callback);
    Sleep(1);

}

TIMConversationHandle CImChat::CreateC2CConversation(const char * peer)
{
    TIMConversationHandle conv = CreateConversation();
    int rt = TIMGetConversation(conv, kCnvC2C, peer);
    return conv;
}

void CImChat::DestroyC2CConversation(TIMConversationHandle handle)
{
    DestroyConversation(handle);
}

static bool bTxtLastMsg = true;

TIMMessageHandle CImChat::DoSendTxtMessage(const char * peer, const string content)
{
    TIMConversationHandle conv = CreateC2CConversation(peer);

    TIMMessageHandle msg = CreateTIMMessage();
    TIMMsgTextElemHandle elem = CreateMsgTextElem();

    SetContent(elem, content.c_str());
    AddElem(msg, elem);
    TIMCommCB callback;
    callback.OnError = chatCallBack.pCBSendTxtMsgError;
    callback.OnSuccess = chatCallBack.pCBSendTxtMsgOnSuccess;

    SendMsg(conv, msg, &callback);
    Sleep(1);

    DestroyC2CConversation(conv);
    //DestroyTIMMessage(msg);
    DestroyElem(elem);

    return msg;
}

TIMMessageHandle CImChat::DoSendPicMessage(const char * peer, const string path)
{
    if(chatCallBack.pCBSendPicMsgError == NULL || chatCallBack.pCBSendPicMsgOnSuccess == NULL)
        {
            return NULL;
        }

    TIMConversationHandle conv = CreateC2CConversation(peer);
    TIMMessageHandle msg = CreateTIMMessage();
    TIMMsgImageElemHandle elem = CreateMsgImageElem();

    SetImageElemPath(elem, path.c_str(), path.size());
    AddElem(msg, elem);

    TIMCommCB callback;
    callback.OnError = chatCallBack.pCBSendPicMsgError;
    callback.OnSuccess = chatCallBack.pCBSendPicMsgOnSuccess;
    SendMsg(conv, msg, &callback);
    Sleep(1);
    DestroyC2CConversation(conv);
    //DestroyTIMMessage(msg);
    DestroyElem(elem);
    return msg;
}

void CImChat::DoSendFaceMessage(const char * peer, const int Index)
{
    TIMConversationHandle conv = CreateC2CConversation(peer);
    TIMMessageHandle msg = CreateTIMMessage();
    TIMMsgFaceElemHandle elem = CreateFaceElemHandle();

    SetFaceElemIndex(elem, Index);
    AddElem(msg, elem);

    TIMCommCB callback;
    callback.OnError = chatCallBack.pCBOnError;
    callback.OnSuccess = chatCallBack.pCBOnSuccess;
    SendMsg(conv, msg, &callback);
    Sleep(1);

    DestroyC2CConversation(conv);
    DestroyTIMMessage(msg);
    DestroyElem(elem);
}


void CImChat::DoGetFriendList()
{
    TIMGetFriendListCallback timCB;

    if(chatCallBack.pCBGetFriendListCallbackOnSuccess == NULL || chatCallBack.pCBGetFriendListCallbackOnError == NULL)
        {
            return;
        }

    TIMGetFriendList(&timCB);
}

void CImChat::SetChatCallBack(ChatCallBack *pCallback)
{
    if(pCallback  != NULL)
        {
            chatCallBack.SetCBFunction(pCallback);
            SetNewMsgCallBack();
            SetConnCallBack();
        }
}

void CImChat::SetNewMsgCallBack()
{
    if(chatCallBack.pCBOnNewMessage == NULL)
        return;

    static TIMMessageCB callback;
    callback.OnNewMessage = chatCallBack.pCBOnNewMessage;
    TIMSetMessageCallBack(&callback);
}


void CImChat::SetConnCallBack()
{
    if(chatCallBack.pCBConnOnConnected == NULL || chatCallBack.pCBConnOnDisconnected == NULL)
        {
            return;
        }

    static TIMConnCB callback;
    callback.OnConnected = chatCallBack.pCBConnOnConnected;
    callback.OnDisconnected = chatCallBack.pCBConnOnDisconnected;
    callback.data = &callback;
    TIMSetConnCallBack(&callback);
}

void CImChat::SetKickOfflineCallBack()
{
    if(chatCallBack.pCBKickOffline == NULL)
        {
            return;
        }

    static TIMForceOfflineCB callback;
    callback.OnKickOffline = chatCallBack.pCBKickOffline;
    TIMSetKickOfflineCallBack(&callback);
}

void CImChat::GetSelfProfile()
{
    if(chatCallBack.pCBGetSelfProfileCallbackOnSuccess == NULL ||
            chatCallBack.pCBGetSelfProfileCallbackOnError == NULL)
        return;

    static TIMGetSelfProfileCallback  callback;
    callback.OnSuccess = chatCallBack.pCBGetSelfProfileCallbackOnSuccess;
    callback.OnError = chatCallBack.pCBGetSelfProfileCallbackOnError;
    TIMGetSelfProfile(&callback);
}

int CImChat::SetSelfNickName(string name)
{
    uint32_t len = name.length() + 1;
    char *pBuf = new char[len];
    memset(pBuf, 0, len);
    memcpy(pBuf, name.data(), len);

    static TIMCommCB callback;
    callback.OnSuccess = chatCallBack.pCBOnSuccess;
    callback.OnError = chatCallBack.pCBOnError;
    TIMSetNickName(pBuf, len, &callback);
    delete []pBuf;
    return S_OK;
}

std::string CImChat::GetSelfNickName(TIMSelfProfileHandle handle)
{
    char *p = new char[256];
    memset(p, 0, 256);
    uint32_t len = 0;

    if(handle)
        {
            GetNickName4SlefProfileHandle(handle, p, &len);
        }

    string str(p);
    delete []p;
    return str;
}

std::string CImChat::GetFriendNickName(TIMSelfProfileHandle handle)
{
    return "";
}

void CImChat::DoGetLocalStoreMsgs(tstring name, int count, TIMMessageHandle last_msg)
{
    TIMConversationHandle conv = CreateC2CConversation(UnicodeToAnsi(name).c_str());
    static TIMGetMsgCB cb;
    cb.OnSuccess = chatCallBack.pCBGetLocalMsgOnSuccess;
    cb.OnError = chatCallBack.pCBGetLocalMsgOnError;
    GetLocalMsgs(conv, count, last_msg, &cb);
}
