
#include "stdafx.h"
#include "ChatWindowMsgHandle.h"
#include "unity/Path.h"
CImChat *g_pImChat = NULL;
CChatWindowMsgHandle *g_chat = NULL;
// //定义回调函数
void staticCBOnNewMessage(TIMMessageHandle* handles, uint32_t msg_num, void* data)
{
    if(g_chat)
        {
            g_chat->CBOnNewMessage(handles, msg_num, data);
        }
}


void staticCBConnOnConnected(void * data)
{
    //     if(g_pChatWindow != NULL)
    //         g_pChatWindow->ChatCBConnOnConnected(data);
}

void staticCBConnOnDisconnected(void *data)
{
    //     if(g_pChatWindow != NULL)
    //         g_pChatWindow->ChatCBConnOnDisconnected(data);
}

void staticCBKickOffLine(void *data)
{
    //     if(g_pChatWindow != NULL)
    //         g_pChatWindow->ChatCBKickOffLine(data);
}

void staticLoginOnSuccess(void* data)
{
    if(g_chat)
        {
            g_chat->LoginOnSuccess(data);
        }
}

void staticLoginOnError(int code, const char* desc, void* data)
{
    string str(desc);
    int i = code;
}

void staticLogoutOnSuccess(void* data)
{
    int i = 0;
}

void staticLogoutOnError(int code, const char* desc, void* data)
{
    string str(desc);
    int i = code;
}

void staticGetFriendListCallbackOnSuccess(void** handles, uint32_t num, void* data)
{
    //     char buf[1024] = { 0 };
    //
    //     for(uint32_t i = 0; i < num; i++)
    //         {
    //             auto handle = handles[i];
    //             uint32_t id_len = 1024;
    //             GetID4FriendListElemHandle(handle, buf, &id_len);
    //             uint32_t nick_len = 1024;
    //             GetID4FriendListElemHandle(handle, buf, &nick_len);
    //
    //
    //         }
}

void staticGetFriendListCallbackOnError(int code, const char* desc, void* data)
{
    /*   int i = 0;*/
}



void staticSendTxtMsgOnSuccess(void* data)
{

}

void staticSendTxtMsgError(int code, const char* desc, void* data)
{
}

void staticSendPicMsgOnSuccess(void * data)
{
    //int i = 0;
}

void staticSendPicMsgError(int code, const char* desc, void* data)
{
    //int i = 0;
}

void  staticRecvPicMsgOnSucess(void * data)
{
    //int i = 0;
}

void   staticRecvPicMsgError(int code, const char* desc, void* data)
{
    // int i = 0;
}

void staticCBGetMsgOnSuccess(TIMMessageHandle* handle_array, int size, void* data)
{

}

void staticCBGetMsgOnError(int code, const char* desc, void* data)
{

}

void staticCBOnSuccess(void* data)
{
    int i = 0;
}

void staticCBGOnError(int code, const char* desc, void* data)
{
    int i = 0;
}

void staticCBGetSelfProfileCallbackOnSuccess(TIMSelfProfileHandle* handles, uint32_t num, void* data)
{
    if(g_chat)
        {
            g_chat->CBGetSelfProfileCallbackOnSuccess(handles, num, data);
        }
}

void staticCBGetSelfProfileCallbackOnError(int code, const char* desc, void* data)
{
    if(g_chat)
        {
            g_chat->CBGetSelfProfileCallbackOnError(code, desc, data);
        }
}

void staticCBGetFriendProfileCallbackOnSuccess(TIMFriendProfileHandle* handles, uint32_t num, void* data)
{

}

void staticCBGetFriendProfileCallbackOnError(int code, const char* desc, void* data)
{

}

void staticCBGetLocalMsgOnSuccess(TIMMessageHandle* handle_array, int size, void* data)
{
    if(g_chat)
        {
            g_chat->CBGetLocalMsgOnSuccess(handle_array, size, data);
        }
}

void staticCBGetLocalMsgOnError(int code, const char* desc, void* data)
{
    if(g_chat)
        {
            g_chat->CBGetLocalMsgOnError(code, desc, data);
        }
}

CChatWindowMsgHandle::CChatWindowMsgHandle()
{
    g_chat = this;
    m_ChatCallBack.pCBOnNewMessage = &staticCBOnNewMessage;
    m_ChatCallBack.pCBConnOnConnected = &staticCBConnOnConnected;
    m_ChatCallBack.pCBConnOnDisconnected = &staticCBConnOnDisconnected;
    m_ChatCallBack.pCBKickOffline = &staticCBKickOffLine;
    m_ChatCallBack.pCBLoginOnSuccess = &staticLoginOnSuccess;
    m_ChatCallBack.pCBLoginOnError = &staticLoginOnError;
    m_ChatCallBack.pCBLogoutOnSuccess = &staticLogoutOnSuccess;
    m_ChatCallBack.pCBLogoutOnError = &staticLoginOnError;
    m_ChatCallBack.pCBGetFriendListCallbackOnSuccess = &staticGetFriendListCallbackOnSuccess;
    m_ChatCallBack.pCBGetFriendListCallbackOnError = &staticGetFriendListCallbackOnError;
    m_ChatCallBack.pCBSendTxtMsgOnSuccess = &staticSendTxtMsgOnSuccess;
    m_ChatCallBack.pCBSendTxtMsgError = &staticSendTxtMsgError;
    m_ChatCallBack.pCBSendPicMsgOnSuccess = &staticSendPicMsgOnSuccess;
    m_ChatCallBack.pCBSendPicMsgError = &staticSendPicMsgError;
    m_ChatCallBack.pCBRecvPicMsgOnSucess = &staticRecvPicMsgOnSucess;
    m_ChatCallBack.pCBRecvPicMsgError = &staticRecvPicMsgError;
    m_ChatCallBack.pCBGetMsgOnSuccess = &staticCBGetMsgOnSuccess;
    m_ChatCallBack.pCBGetMsgOnError = &staticCBGetMsgOnError;
    m_ChatCallBack.pCBOnSuccess = &staticCBOnSuccess;
    m_ChatCallBack.pCBOnError = &staticCBGOnError;
    m_ChatCallBack.pCBGetSelfProfileCallbackOnSuccess = &staticCBGetSelfProfileCallbackOnSuccess;
    m_ChatCallBack.pCBGetSelfProfileCallbackOnError = &staticCBGetSelfProfileCallbackOnError;
    m_ChatCallBack.pCBGetFriendProfileCallbackOnSuccess = &staticCBGetFriendProfileCallbackOnSuccess;
    m_ChatCallBack.pCBGetFriendProfileCallbackOnError = &staticCBGetFriendProfileCallbackOnError;
    m_ChatCallBack.pCBGetLocalMsgOnSuccess = &staticCBGetLocalMsgOnSuccess;
    m_ChatCallBack.pCBGetLocalMsgOnError = &staticCBGetLocalMsgOnError;
    m_TIMSelfProfileHandle = NULL;

    m_strCachePicPath = unity::CPath::GetCurDir() + _T("PicCache");
    m_ThreadId = 0;
}

CChatWindowMsgHandle::~CChatWindowMsgHandle()
{
    StopThread();
}

string CChatWindowMsgHandle::GetItemContent(const TIMMsgTextElemHandle handle)
{
    string content;

    uint32_t len = GetContentLen(handle) + 1;

    char *pstr = new char[len + 1];

    memset(pstr, 0, len);

    GetContent(handle, pstr, &len);

    content.append(pstr);

    content = UnicodeToAnsi(Utf8ToUnicode(content));

    delete [] pstr;

    pstr = NULL;

    return content;
}

string CChatWindowMsgHandle::GetItemUser(const TIMMsgTextElemHandle handle)
{
    string content;

    uint32_t len = 1024;

    char *pstr = new char[len + 1];

    memset(pstr, 0, len + 1);

    GetMsgSender(handle, pstr, &len);

    content.append(pstr);

    delete [] pstr;

    pstr = NULL;

    return content;
}

string CChatWindowMsgHandle::GetItemTime(const TIMMsgTextElemHandle handle)
{
    uint32_t itime = GetMsgTime(handle);

    time_t t_t = itime;

    tm *t = localtime(&t_t);

    SYSTEMTIME sm = TimetToSystemTime((time_t)itime);

    char str[100];
    sprintf(str, "%d/%d/%d %d:%d:%d", sm.wYear, sm.wMonth, sm.wDay, t->tm_hour, t->tm_min, t->tm_sec);

    return string(str);
}

int CChatWindowMsgHandle::GetMessageType(tstring msg)
{

    if(msg.size() < 2)
        return ERR_TYPE;

    if(msg.at(0) == _T('/'))
        {
            if(msg.at(1) == _T('/'))
                {
                    return TXT_TYPE;
                }
            else if(msg.at(1) == _T('f'))
                {
                    return FACE_TYPE;
                }
            else if(msg.at(1) == _T('s'))
                {
                    return SYS_TYPE;
                }
            else if(msg.at(1) == _T('c'))
                {
                    return PIC_TYPE;
                }
        }

    return TXT_TYPE;
}

void CChatWindowMsgHandle::SendPicMessage(tstring name, tstring txt)
{
    int startIndex = 0;

    if(m_pImChat && !name.empty() && txt.size() > 2)
        {
            tstring strFileName;
            TIMMessageHandle handle;

            do
                {
                    startIndex += 2;

                    strFileName = GetBetweenString(txt.data() + startIndex, _T("[\""), _T("\"]"));

                    handle = m_pImChat->DoSendPicMessage(UnicodeToAnsi(name).c_str(), UnicodeToAnsi(strFileName).c_str());

                    startIndex = txt.find(_T("/c"), startIndex);
                }
            while(startIndex != -1);

            if(m_Map_Name_TIMmsg.find(name) == m_Map_Name_TIMmsg.end())
                {
                    m_Map_Name_TIMmsg[name] = handle;
                }
            else
                {
                    DestroyTIMMessage(handle);
                }
        }
}

void CChatWindowMsgHandle::RecvTxtMessage(const TIMMessageHandle handle, bool bLocalMsg)
{
    if(handle)
        {
            if(m_WindowCallBack)
                {
                    RECEIVE_MSG msg;
                    msg.windowType = WORKMATE;
                    msg.localMsgType = bLocalMsg;
                    {
                        m_LocalMsgMtx.lock();
                        std::lock_guard<std::mutex> lck(m_LocalMsgMtx, std::adopt_lock);
                        msg.msgLocalMsgUser = m_LocalMsgUserName;
                    }
                    msg.msgType = TXT_TYPE;
                    msg.msgUser = GetItemUser(handle);
                    msg.msgTime = GetItemTime(handle);

                    if(m_Map_Name_TIMmsg.find(AnsiToUnicode(msg.msgUser)) == m_Map_Name_TIMmsg.end())
                        {
                            m_Map_Name_TIMmsg[AnsiToUnicode(msg.msgUser)] = handle;
                        }

                    msg.msgContent.push_back(GetItemContent(GetElem(handle, 0)));
                    string content;
                    msg.toString(content);
                    m_WindowCallBack(content);
                }
        }
}

void CChatWindowMsgHandle::RecvPicMessage(const TIMMsgImageElemHandle handle, bool bLocalMsg)
{
    if(handle)
        {
            RECEIVE_MSG msg;
            msg.windowType = WORKMATE;
            msg.msgType = PIC_TYPE;
            msg.localMsgType = bLocalMsg;
            {
                m_LocalMsgMtx.lock();
                std::lock_guard<std::mutex> lck(m_LocalMsgMtx, std::adopt_lock);
                msg.msgLocalMsgUser = m_LocalMsgUserName;
            }

            msg.msgTime = GetItemTime(handle);
            msg.msgUser = GetItemUser(handle);

            if(m_Map_Name_TIMmsg.find(AnsiToUnicode(msg.msgUser)) == m_Map_Name_TIMmsg.end())
                {
                    m_Map_Name_TIMmsg[AnsiToUnicode(msg.msgUser)] = handle;
                }

            uint32_t num = GetImageNum(GetElem(handle, 0));
            TIMImageHandle* handles = new TIMImageHandle[num];
            GetImages(GetElem(handle, 0), handles, &num);

            for(int i = 0; i < num; i++)
                {
                    RECEIVE_PIC_MSG pic_msg;
                    pic_msg.imgType = GetImageType(handles[i]);
                    pic_msg.imgHeight = GetImageHeight(handles[i]);
                    pic_msg.imgWeight = GetImageWidth(handles[i]);
                    pic_msg.imgSize = GetImageSize(handles[i]);

                    uint32_t len = GetImageURLLen(handles[i]) + 1 ;

                    if(len > 0)
                        {
                            char *path = new char[len];
                            memset(path, 0, len);
                            GetImageURL(handles[i], path, &len);
                            pic_msg.strImgURL.append(path);
                            int startIndex = pic_msg.strImgURL.rfind('/');
                            int endIndex = pic_msg.strImgURL.rfind('/', startIndex - 1);
                            string strName = pic_msg.strImgURL.substr(endIndex + 1, startIndex - endIndex - 1);
                            pic_msg.strImgFileName = strName;
                            strName = pic_msg.strImgURL.substr(startIndex + 1, len - startIndex - 1);
                            pic_msg.strImgFileName += "_";
                            pic_msg.strImgFileName += strName;
                            pic_msg.strImgFileName += ".image";
                            delete [] path;
                            path = NULL;
                        }

                    //下载图片 可能会卡死，现在这样吧，标记一下，以后在改吧
                    string strTempPath = UnicodeToAnsi(m_strCachePicPath);
                    pic_msg.strImgFileName = strTempPath + "\\" + pic_msg.strImgFileName;

                    pic_msg.bLoadImage = GetImageFromURL(AnsiToUnicode(pic_msg.strImgURL),
                                                         AnsiToUnicode(pic_msg.strImgFileName));

                    string strContent;
                    pic_msg.toString(strContent);
                    msg.msgContent.push_back(strContent);
                }


            if(m_WindowCallBack)
                {
                    string content;
                    msg.toString(content);
                    m_WindowCallBack(content);
                }

            delete handles;
        }

}

void CChatWindowMsgHandle::HandldRecvMsg()
{
    while(m_RecvMsgHandleList.size() > 0)
        {
            TIMMessageHandle tempHandle = m_RecvMsgHandleList.front();
            {
                m_imtx.lock();
                std::lock_guard<std::mutex> lck(m_imtx, std::adopt_lock);
                m_RecvMsgHandleList.pop_front();
            }
			
            for(int j = 0; j < GetElemCount(tempHandle); j++)
                {
                    auto type = GetElemType(GetElem(tempHandle, j));

                    switch(type)
                        {
                            case kElemText:
                                {
                                    RecvTxtMessage(tempHandle);
                                    break;
                                }

                            case kElemImage:
                                {
                                    RecvPicMessage(tempHandle);
                                    break;
                                }

                            case  kElemFace:
                                {
                                    RecvFaceMessage(tempHandle);
                                    break;
                                }

                            default:
                                break;
                        }
                }

            DestroyElem(tempHandle);
        }
}

std::string CChatWindowMsgHandle::GetTxtContent(const string content)
{
    RECEIVE_TXT_MSG msg;
    msg.unString(content);
    return msg.content;
}

std::string CChatWindowMsgHandle::GetPicContent(const string content)
{
    RECEIVE_PIC_MSG msg;
    msg.unString(content);
    return msg.strImgFileName;
}

int CChatWindowMsgHandle::StartThread()
{
    if(m_bRunning == true)
        {
            return  1;
        }

    std::thread thread(&CChatWindowMsgHandle::ThreadProcess, this);
    m_MainThread.swap(thread);
    return 0;
}

int CChatWindowMsgHandle::StopThread()
{

    if(!m_bRunning)
        return S_FALSE;

    PostThreadMessage(m_ThreadId, WM_QUIT, 0, 0);
    m_bRunning = false;
    m_MainThread.join();
    return S_OK;
    return 0;
}

int CChatWindowMsgHandle::ThreadProcess()
{
    m_bRunning = true;
    m_ThreadId = GetCurrentThreadId();

    m_pImChat.reset(new CImChat());

    if(m_pImChat)
        {
            m_pImChat->SetChatCallBack(&m_ChatCallBack);
        }

    MSG msg = { 0 };

    while(::GetMessage(&msg, NULL, 0, 0))
        {
            HandleThreadMessage(msg.message, msg.wParam, msg.lParam);

            ::DispatchMessage(&msg);
        }


    return S_OK;
}

DWORD CChatWindowMsgHandle::GetThreadId() const
{
    return m_ThreadId;
}

void CChatWindowMsgHandle::CBOnNewMessage(TIMMessageHandle* handles, uint32_t msg_num, void* data)
{
    m_imtx.lock();
    std::lock_guard<std::mutex> lck(m_imtx, std::adopt_lock);

    for(int i = 0; i < msg_num; i++)
        {
            // for (int j = 0; j < GetElemCount(handles[i]); j++)
            {
                TIMMessageHandle tempHandle = CloneTIMMessage(handles[i]);
                m_RecvMsgHandleList.push_back(tempHandle);
                PostThreadMessage(m_ThreadId, USER_IM_MSG, USER_IM_MSG, 0);
            }
        }
}

void CChatWindowMsgHandle::CBConnOnConnected(void * data)
{

}

void CChatWindowMsgHandle::CBConnOnDisconnected(void *data)
{

}

void CChatWindowMsgHandle::CBKickOffLine(void *data)
{

}

void CChatWindowMsgHandle::LoginOnSuccess(void *data)
{
    m_bLoginSuccess = true;
    RECEIVE_MSG msg;
    msg.windowType = ALL;
    msg.msgType = NAME_TYPE;
    msg.msgUser = m_CurrentAgentName;
    string content;
    msg.toString(content);

    if(m_WindowCallBack)
        {
            m_WindowCallBack(content);
        }
}

void CChatWindowMsgHandle::LoginOnError(int code, const char* desc, void* data)
{

}

void CChatWindowMsgHandle::LogoutOnSuccess(void *data)
{

}

void CChatWindowMsgHandle::LogoutOnError(int code, const char* desc, void* data)
{

}

void CChatWindowMsgHandle::GetFriendListCallbackOnSuccess(void** handles, uint32_t num, void* data)
{

}

void CChatWindowMsgHandle::GetFriendListCallbackOnError(int code, const char* desc, void* data)
{

}

void CChatWindowMsgHandle::SendTxtMsgOnSuccess(void* data)
{

}

void CChatWindowMsgHandle::SendTxtMsgError(int code, const char* desc, void *data)
{

}

void CChatWindowMsgHandle::SendPicMsgOnSuccess(void* data)
{

}

void CChatWindowMsgHandle::SendPicMsgError(int code, const char* desc, void *data)
{

}

void CChatWindowMsgHandle::RecvPicMsgOnSucess(void *data)
{

}

void CChatWindowMsgHandle::RecvPicMsgError(int code, const char* desc, void* data)
{

}

void CChatWindowMsgHandle::CBGetMsgOnSuccess(TIMMessageHandle* handle_array, int size, void* data)
{

}

void CChatWindowMsgHandle::CBGetMsgOnError(int code, const char* desc, void* data)
{

}

void CChatWindowMsgHandle::CBOnSuccess(void *data)
{

}

void CChatWindowMsgHandle::CBOnError(int code, const char* desc, void* data)
{

}

void CChatWindowMsgHandle::CBGetSelfProfileCallbackOnSuccess(TIMSelfProfileHandle* handles, uint32_t num, void* data)
{
    if(num == 1)
        {
            m_TIMSelfProfileHandle = CloneSelfProfileHandle(handles[0]);
            PostThreadMessage(m_ThreadId, USER_IM_PROFILE, USER_IM_PROFILE, 0);
        }

}

void CChatWindowMsgHandle::CBGetSelfProfileCallbackOnError(int code, const char* desc, void* data)
{

}

void CChatWindowMsgHandle::CBGetLocalMsgOnSuccess(TIMMessageHandle* handle_array, int size, void* data)
{
    m_imtx.lock();
    std::lock_guard<std::mutex> lck(m_imtx, std::adopt_lock);

    for(int i = 0; i < size; i++)
        {
            {
                TIMMessageHandle tempHandle = CloneTIMMessage(handle_array[i]);
                m_Map_Name_TIMmsg[AnsiToUnicode(m_LocalMsgUserName)] = tempHandle;
                m_RecvMsgHandleList.push_back(tempHandle);
                PostThreadMessage(m_ThreadId, USER_IM_GETLOCALMSG, USER_IM_GETLOCALMSG, 0);
            }
        }

}

void CChatWindowMsgHandle::CBGetLocalMsgOnError(int code, const char* desc, void* data)
{
    int i = 0;
}


void CChatWindowMsgHandle::SendMessageToIM(int type, tstring name, tstring content)
{
    if(!m_pImChat && !m_bLoginSuccess)
        return;

    switch(type)
        {
            case TXT_TYPE:
                {
                    TIMMessageHandle handle =  m_pImChat->DoSendTxtMessage(UnicodeToUtf8(name).c_str(), UnicodeToUtf8(content));

                    if(m_Map_Name_TIMmsg.find(name) == m_Map_Name_TIMmsg.end())
                        {
                            m_Map_Name_TIMmsg[name] = handle;
                        }
                    else
                        {
                            DestroyTIMMessage(handle);
                        }
                };

                break;
            case  PIC_TYPE:
                {
                    SendPicMessage(name, content);

                }
                break;

            case  FACE_TYPE:
                {
                    SendFaceMessage(name, content);
                }
                break;

            case  LOCALMSG_TYPE:
                {
                    if(m_Map_Name_TIMmsg.find(name) == m_Map_Name_TIMmsg.end())
                        {
                            GetLocalStoreMsgs(name, 15, NULL);
                        }
                    else
                        {
                            GetLocalStoreMsgs(name, 15, m_Map_Name_TIMmsg[name]);
                        }
                }
                break;

            default:
                break;
        }
}

void CChatWindowMsgHandle::SetWindowCallBackFuncion(const WindowCallBack pWindowCallBack)
{
    m_WindowCallBack = pWindowCallBack;
}

void CChatWindowMsgHandle::AddQTBMessage(MESSAGE_ENTITY msg)
{

    {
        m_metx.lock();
        std::lock_guard<std::mutex> lck(m_metx, std::adopt_lock);
        m_MessageEntityList.push_back(msg);
    }
    PostThreadMessage(m_ThreadId, USER_QTB_MSG, USER_QTB_MSG, 0);
}

void CChatWindowMsgHandle::HandleThreadMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    switch(wParam)
        {
            case  USER_QTB_MSG:
                {
                    HandldQTBMsg();

                } break;

            case  USER_IM_MSG:
                {
                    HandldRecvMsg();
                }
                break;

            case  USER_IM_PROFILE:
                {
                    GetSelfProfile();
                }
                break;

            case  USER_IM_GETLOCALMSG:
                {
                    HandleLocalMsg();
                }
                break;

            default:
                break;
        }


}

void CChatWindowMsgHandle::GetSelfProfile()
{
    if(m_TIMSelfProfileHandle && m_pImChat)
        {
            string name = m_pImChat->GetSelfNickName(m_TIMSelfProfileHandle);

            if(name.empty())
                {
                    m_pImChat->SetSelfNickName("测试员");
                }
        }
}

void CChatWindowMsgHandle::CBGetFriendProfileCallbackOnSuccess(TIMFriendProfileHandle* handles, uint32_t num, void* data)
{

}

void CChatWindowMsgHandle::CBGetFriendProfileCallbackOnError(int code, const char* desc, void* data)
{

}

void CChatWindowMsgHandle::SendFaceMessage(tstring name, tstring txt)
{
    if(m_pImChat && !name.empty() && txt.size() > 2)
        {
            tstring index = GetBetweenString(txt.data() + 2, _T("[\""), _T("\"]"));

            if(!IsDigit(index.c_str()))
                {
                    return;
                }

            m_pImChat->DoSendFaceMessage(UnicodeToAnsi(name).c_str(), StringToNumber(index));
        }
}

void CChatWindowMsgHandle::RecvFaceMessage(const TIMMessageHandle handle)
{
    if(handle)
        {
            if(m_WindowCallBack)
                {
                    RECEIVE_MSG msg;
                    msg.windowType = WORKMATE;
                    msg.msgType = FACE_TYPE;
                    msg.msgUser = GetItemUser(handle).c_str();
                    size_t num = GetElemCount(handle);

                    for(size_t i = 0; i < num; i++)
                        {
                            int index = GetFaceElemIndex(GetElem(handle, i));
                            msg.msgContent.push_back(UnicodeToAnsi(NumberToString(index)));
                        }

                    string content;
                    msg.toString(content);
                    m_WindowCallBack(content);
                }
        }
}

void CChatWindowMsgHandle::HandldQTBMsg()
{
    MESSAGE_ENTITY msg;
    {
        m_metx.lock();
        std::lock_guard<std::mutex> lck(m_metx, std::adopt_lock);
        msg = m_MessageEntityList.front();
        m_MessageEntityList.pop_front();
    }

    if(msg.msgtype == USER_LOGIN)
        {
            if(m_bLoginSuccess)
                {
                    return;
                }

            LoginInfo info;
            info.unString(msg.msgContent);

            TIMUserInfo tim_user { 0 };
            tim_user.account_type = new char[info.account_type.size() + 1];
            tim_user.app_id_at_3rd = new char[info.app_id_at_3rd.size() + 1];

            strcpy(tim_user.account_type, info.account_type.c_str());
            strcpy(tim_user.app_id_at_3rd, info.app_id_at_3rd.c_str());

            if(m_pImChat)
                {
                    string content = OpenURL(CreateLoginInfoURL(info.identifier.c_str()).c_str());
                    string  managerId = GetManagerIdFromJson(content);

                    if(managerId.empty())
                        {
                            return;
                        }

                    string user = managerId + "_" + info.identifier ;

                    tim_user.identifier = new char[user.size() + 1];
                    strcpy(tim_user.identifier, user.c_str());

                    content = OpenURL(CreateLoginURL(user.c_str()).c_str()); //线程可能卡死，想到好方法再改吧，不纠结了

                    string sig = GetSigFromJson(content);

                    if(sig.empty())
                        {
                            return;
                        }

                    m_CurrentAgentName = info.identifier;
                    m_pImChat->Login(info.sdk_app_id, &tim_user,
                                     sig.c_str());
                }

            delete tim_user.account_type;
            delete tim_user.app_id_at_3rd;
            delete tim_user.identifier;

        }
    else if(msg.msgtype == USER_WINDOWSHOWTYPE)
        {
            if(m_WindowCallBack)
                {
                    RECEIVE_MSG _msg;
                    _msg.windowType = NOTIFY;
                    _msg.msgContent.push_back(msg.msgContent);
                    string str;
                    _msg.toString(str);
                    m_WindowCallBack(str);
                }
        }
    else if(msg.msgtype == USER_WORKMATEINFO)
        {
            if(m_WindowCallBack)
                {
                    m_WindowCallBack(msg.msgContent);
                }
        }
}

void CChatWindowMsgHandle::HandleLocalMsg()
{
    while(m_RecvMsgHandleList.size() > 0)
        {
            TIMMessageHandle tempHandle = m_RecvMsgHandleList.front();
            {
                m_imtx.lock();
                std::lock_guard<std::mutex> lck(m_imtx, std::adopt_lock);
                m_RecvMsgHandleList.pop_front();
            }

            for(int j = 0; j < GetElemCount(tempHandle); j++)
                {
                    auto type = GetElemType(GetElem(tempHandle, j));

                    switch(type)
                        {
                            case kElemText:
                                {
                                    RecvTxtMessage(tempHandle, true);
                                    break;
                                }

                            case kElemImage:
                                {
                                    RecvPicMessage(tempHandle, true);
                                    break;
                                }

                            default:
                                break;
                        }
                }

            DestroyElem(tempHandle);
        }
}


void CChatWindowMsgHandle::GetLocalStoreMsgs(tstring name, int count, TIMMessageHandle last_msg)
{
    if(m_pImChat)
        {
            {
                m_LocalMsgMtx.lock();
                std::lock_guard<std::mutex> lck(m_LocalMsgMtx, std::adopt_lock);
                m_LocalMsgUserName = UnicodeToAnsi(name);
            }

            m_pImChat->DoGetLocalStoreMsgs(name, count, last_msg);
        }
}




