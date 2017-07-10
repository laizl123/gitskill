#pragma once
#include "IMlibs/c_includes/tim_c.h"
#include "IMlibs/c_includes/tim_friend_c.h"

struct ChatCallBack
{
    ChatCallBack()
    {
        pCBOnNewMessage   = NULL;
        pCBConnOnConnected = NULL;
        pCBConnOnDisconnected = NULL;
        pCBKickOffline = NULL;
        pCBLoginOnSuccess = NULL;
        pCBLoginOnError = NULL;
        pCBLogoutOnSuccess = NULL;
        pCBLogoutOnError = NULL;
        pCBGetFriendListCallbackOnSuccess = NULL;
        pCBGetFriendListCallbackOnError = NULL;
        pCBSendTxtMsgOnSuccess = NULL;
        pCBSendTxtMsgError = NULL;
        pCBSendPicMsgOnSuccess = NULL;
        pCBSendPicMsgError = NULL;
        pCBRecvPicMsgOnSucess = NULL;
        pCBRecvPicMsgError = NULL;
        pCBGetMsgOnSuccess = NULL;
        pCBGetMsgOnError = NULL;
        pCBOnSuccess = NULL;
        pCBOnError = NULL;
        pCBGetSelfProfileCallbackOnSuccess = NULL;
        pCBGetSelfProfileCallbackOnError = NULL;
        pCBGetFriendProfileCallbackOnSuccess = NULL;
        pCBGetFriendProfileCallbackOnError = NULL;
        pCBGetLocalMsgOnSuccess  = NULL;
        pCBGetLocalMsgOnError    = NULL;
    }

    void SetCBFunction(ChatCallBack *pCallBack)
    {
        if(pCallBack != NULL)
            {
                pCBOnNewMessage = pCallBack->pCBOnNewMessage;
                pCBConnOnConnected = pCallBack->pCBConnOnConnected;
                pCBConnOnDisconnected = pCallBack->pCBConnOnDisconnected;
                pCBKickOffline = pCallBack->pCBKickOffline;
                pCBLoginOnSuccess = pCallBack->pCBLoginOnSuccess;
                pCBLoginOnError = pCallBack->pCBLoginOnError;
                pCBLogoutOnSuccess = pCallBack->pCBLogoutOnSuccess;
                pCBLogoutOnError = pCallBack->pCBLoginOnError;
                pCBGetFriendListCallbackOnSuccess = pCallBack->pCBGetFriendListCallbackOnSuccess;
                pCBGetFriendListCallbackOnError = pCallBack->pCBGetFriendListCallbackOnError;
                pCBSendTxtMsgOnSuccess = pCallBack->pCBSendTxtMsgOnSuccess;
                pCBSendTxtMsgError = pCallBack->pCBSendTxtMsgError;
                pCBSendPicMsgOnSuccess = pCallBack->pCBSendPicMsgOnSuccess;
                pCBSendPicMsgError = pCallBack->pCBSendPicMsgError;
                pCBRecvPicMsgOnSucess = pCallBack->pCBRecvPicMsgOnSucess;
                pCBRecvPicMsgError = pCallBack->pCBRecvPicMsgError;
                pCBGetMsgOnSuccess = pCallBack->pCBGetMsgOnSuccess;
                pCBGetMsgOnError = pCallBack->pCBGetMsgOnError;
                pCBOnSuccess = pCallBack->pCBOnSuccess;
                pCBOnError = pCallBack->pCBOnError;
                pCBGetSelfProfileCallbackOnSuccess = pCallBack->pCBGetSelfProfileCallbackOnSuccess;
                pCBGetSelfProfileCallbackOnError = pCallBack->pCBGetSelfProfileCallbackOnError;
                pCBGetFriendProfileCallbackOnSuccess = pCallBack->pCBGetFriendProfileCallbackOnSuccess;
                pCBGetFriendProfileCallbackOnError = pCallBack->pCBGetFriendListCallbackOnError;
                pCBGetLocalMsgOnSuccess = pCallBack->pCBGetLocalMsgOnSuccess;
                pCBGetLocalMsgOnError   = pCallBack->pCBGetLocalMsgOnError;
            }

    }

    CBOnNewMessage pCBOnNewMessage;
    CBConnOnConnected pCBConnOnConnected;
    CBConnOnDisconnected pCBConnOnDisconnected;
    CBKickOffline        pCBKickOffline;
    CBOnSuccess        pCBLoginOnSuccess;
    CBOnError          pCBLoginOnError;
    CBOnSuccess        pCBLogoutOnSuccess;
    CBOnError          pCBLogoutOnError;
    CBGetFriendListCallbackOnSuccess pCBGetFriendListCallbackOnSuccess;
    CBGetFriendListCallbackOnError   pCBGetFriendListCallbackOnError;
    CBOnSuccess      pCBSendTxtMsgOnSuccess;
    CBOnError        pCBSendTxtMsgError;
    CBOnSuccess      pCBSendPicMsgOnSuccess;
    CBOnError        pCBSendPicMsgError;
    CBOnSuccess      pCBRecvPicMsgOnSucess;
    CBOnError        pCBRecvPicMsgError;
    CBGetMsgOnSuccess pCBGetMsgOnSuccess;
    CBGetMsgOnError   pCBGetMsgOnError;
    CBOnSuccess       pCBOnSuccess;
    CBOnError        pCBOnError;
    CBGetSelfProfileCallbackOnSuccess pCBGetSelfProfileCallbackOnSuccess;
    CBGetSelfProfileCallbackOnError   pCBGetSelfProfileCallbackOnError;
    CBGetFriendProfileCallbackOnSuccess pCBGetFriendProfileCallbackOnSuccess;
    CBGetFriendProfileCallbackOnError   pCBGetFriendProfileCallbackOnError;
    CBGetMsgOnSuccess pCBGetLocalMsgOnSuccess;
    CBGetMsgOnError   pCBGetLocalMsgOnError;
};

class CImChat
{
    public:
        CImChat();
        ~CImChat();
    public:

        ////////////////////////////////////////////////////////////////////////////////////////////

        /**************************************************************************
        函数名   : SetChatCallBack
        功能     : 设置回调函数
        参数	 : 登出失败的回调函数
        返回值   :  无
        备注     :
        **************************************************************************/
        void SetChatCallBack(ChatCallBack *pCallback);

        /**************************************************************************
        	函数名   : Logout
        	功能     : 如用户主动注销或需要进行用户的切换，则需要调用注销操作
        	参数	 : 1、CBOnSuccess   登出成功的回调函数
        			   2、CBOnError     登出失败的回调函数
        	返回值   :  无
        	备注     : 在需要切换帐号时，需要logout回调成功或者失败后才能再次login，否则login可能会失败。
        **************************************************************************/
        void Logout();

        /**************************************************************************
        函数名   : Login
        功能     : 用户登录腾讯后台服务器
        参数	 : 1、sdk_app_id   用于标识接入sdk的应用id
        2、tim_user     用户账号, 必须填写account_type、identifier、app_id_at_3rd
        3、user_sig      生成的sig 密钥
        4、CBOnSuccess   登录成功的回调函数
         5、CBOnError     登录失败的回调函数
        返回值   : int
        备注     : 最新版本为 180 天，也就是说是有期限的，所以开发者需要让终端定期到自己的后台服务器重新获取新的 usersig 从而避免用户出现 usersig 过期的现象。
        **************************************************************************/
        int  Login(int sdk_app_id, const TIMUserInfo *tim_user, const char* user_sig);

        ////////////////////////////////////////////////////////////////////////////////////////////
        /**************************************************************************
        	函数名   : CreateC2CConversation
        	功能     : 获取会话
        	参数	 : 1、peer   对方的identifier
        	返回值   : 无
        	备注     :  一定要记得调用DestroyC2CConversation来销毁获取到的TIMConversationHandle
        **************************************************************************/
        TIMConversationHandle CreateC2CConversation(const char * peer);

        /**************************************************************************
        	函数名   : DestroyC2CConversation
        	功能     : 销毁会话
        	参数	 : 1、handle      由CreateC2CConversation 创建得到
        	返回值   : 无
        	备注     : 一定要调用DestroyC2CConversation来销毁会话
        **************************************************************************/
        void  DestroyC2CConversation(TIMConversationHandle handle);

        /**************************************************************************
        	函数名   : DoSendTxtMessage
        	功能     : 发送文本消息
        	参数	 : 1、peer   对方的identifier
        	           2、content 传递需要发送的文本消息
        	返回值   : TIMMessageHandle
        	备注     : 无
        **************************************************************************/
        TIMMessageHandle DoSendTxtMessage(const char * peer, const string content);

        /**************************************************************************
        	函数名   : DoSendPicMessaage
        	功能     : 发送图片消息
        	参数	 : 1、peer   对方的identifier
        	           2、path  传递需要发送的图片消息
        	返回值   : 无
        	备注     :
        **************************************************************************/
        TIMMessageHandle DoSendPicMessage(const char * peer, const string path);

        /**************************************************************************
        	函数名   : DoSendFaceMessage
        	功能     : 发送表情功能
        	参数	 : 1、peer   对方的identifier
        	           2、index  传递需要发送的表情的序号
        	返回值   : 无
        	备注     :
        **************************************************************************/
        void DoSendFaceMessage(const char * peer, const int Index);

        /**************************************************************************
        函数名   : DoGetFriendList
        功能     : 获取所有好友资料
        参数	 : 无
        返回值   : 无
        备注     :
        **************************************************************************/
        void DoGetFriendList();

        /**************************************************************************
        函数名   : GetSelfProfile
        功能     : 获取自己的资料
        参数	 : 无
        返回值   : string
        备注     :
        **************************************************************************/
        void	GetSelfProfile();

        /**************************************************************************
        函数名   : GetSelfNickName
        功能     : 获取自己的昵称
        参数	 : 无
        返回值   : string
        备注     :
        **************************************************************************/
        string	GetSelfNickName(TIMSelfProfileHandle handle);

        /**************************************************************************
        函数名   : SetSelfNickName
        功能     : 设置自己的别名
        参数	 : 无
        返回值   : string
        备注     :
        **************************************************************************/
        int	SetSelfNickName(string name);

        /**************************************************************************
        函数名   : GetFriendNickName
        功能     : 获取自己的昵称
        参数	 : 无
        返回值   : string
        备注     :
        **************************************************************************/
        string	GetFriendNickName(TIMSelfProfileHandle handle);

        /**************************************************************************
        函数名   : DoGetLocalStoreMsgs();
        功能     : 获取本地历史信息
        参数	 : 无
        返回值   : void
        备注     :
        **************************************************************************/
        void	DoGetLocalStoreMsgs(tstring name, int count, TIMMessageHandle last_msg);

        ////////////////////////////////////////////////////////////////////////////////////////////
    private:
        void SetNewMsgCallBack();
        void SetConnCallBack();
        void SetKickOfflineCallBack();
    public:
        ChatCallBack  chatCallBack;
};

