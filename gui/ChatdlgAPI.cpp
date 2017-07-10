#include "StdAfx.h"
#include "ChatdlgAPI.h"
#include "ChatThread.h"
#include <memory>
#include "unity/CommonDef.h"
using namespace std;

unique_ptr<CChatThread> pChatThread;

CWAPI int  _stdcall InitializeWindow()
{
    if(pChatThread == NULL)
        {
            pChatThread.reset(new CChatThread);

            return pChatThread->StartThread();
        }

    return S_FALSE;
}

CWAPI int _stdcall FreeInitializeWindow()
{
    if(pChatThread != NULL)
        {
            return pChatThread->StopThread();
        }

    return S_FALSE;
}

CWAPI int _stdcall ShowChatWindow(int left , int top, int right, int bottom)
{
    if(pChatThread != NULL)
        {
            SHOWWINDOWTYPE showtype;
            showtype.ShowWindowType = NOTIFY;
            showtype.ShowFormat = 1;
            showtype.Left = left;
            showtype.Top = top;
            showtype.Right = right;
            showtype.Bottom = bottom;

            string str;
            showtype.toString(str);

            MESSAGE_ENTITY msg;
            msg.msgtype = USER_WINDOWSHOWTYPE;
            msg.msgContent = str;
            pChatThread->AddQTBMessage(msg);
            return S_OK;
        }

    return S_FALSE;
}

CWAPI int _stdcall HideChatWindow()
{
    if(pChatThread != NULL)
        {
            SHOWWINDOWTYPE showtype;
            showtype.ShowWindowType = NOTIFY;
            showtype.ShowFormat = 0;

            string str;
            showtype.toString(str);

            MESSAGE_ENTITY msg;
            msg.msgtype = USER_WINDOWSHOWTYPE;
            msg.msgContent = str;
            pChatThread->AddQTBMessage(msg);
            return S_OK;
        }

    return S_FALSE;
}

CWAPI int _stdcall LoginToChatWindow(const char* identifier)
{
    if(pChatThread != NULL)
        {
            LoginInfo info;

            info.identifier    = identifier;

            string str;
            info.toString(str);

            MESSAGE_ENTITY msg;
            msg.msgtype = USER_LOGIN;
            msg.msgContent = str;
            pChatThread->AddQTBMessage(msg);

            return S_OK;
        }

    return S_FALSE;
}

CWAPI int _stdcall SetChatObject(const char* identifier)
{
    if(pChatThread != NULL && pChatThread->pSetClientName)
        {

            string strinfo(identifier);
            string user = "";
            string username = ""; //中文名字

            //解析出帐号名和中文名
            if(strinfo.find('|') != -1)
                {
                    user = strinfo.substr(0, strinfo.find('|'));
                    username = strinfo.substr(strinfo.find('|') + 1, strinfo.size() - strinfo.find('|') - 1);
                }
            else
                {
                    user = strinfo;
                    username = strinfo;
                }

            RECEIVE_MSG Info;
            Info.windowType = WORKMATE;
            Info.msgType = SHOW_TYPE;
            Info.msgUser = user;
            Info.msgUserName = username;

            string content = OpenURL(CreateLoginInfoURL(Info.msgUser.c_str()).c_str());
            string  managerId = GetManagerIdFromJson(content);

            if(managerId.empty())
                {
                    return S_FALSE;
                }

            Info.msgUser = managerId + "_" + Info.msgUser;

            string str;
            Info.toString(str);

            MESSAGE_ENTITY msg;
            msg.msgtype = USER_WORKMATEINFO;
            msg.msgContent = str;
            pChatThread->AddQTBMessage(msg);

            pChatThread->pSetClientName(AnsiToUnicode(string(identifier)));
        }

    return S_OK;
}


CWAPI int _stdcall EndChatObject(const char* identifier)
{
    if(pChatThread != NULL)
        {
            RECEIVE_MSG Info;
            Info.windowType = DELETEUSER;
            Info.msgType = HIDE_TYPE;
            Info.msgUser = identifier;

			//string content = OpenURL(CreateLoginInfoURL(Info.msgUser.c_str()).c_str());
			//string  managerId = GetManagerIdFromJson(content);

			//if ( managerId.empty() )
			//{
			//	return S_FALSE;
			//}

			//Info.msgUser = managerId + "_" + Info.msgUser;

            string str;
            Info.toString(str);

            MESSAGE_ENTITY msg;
            msg.msgtype = USER_WORKMATEINFO;
            msg.msgContent = str;
            pChatThread->AddQTBMessage(msg);

        }

    return S_OK;
}

CWAPI bool _stdcall IsChatWindowShow()
{
    return false;
}



