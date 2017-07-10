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
        ������   : SetChatCallBack
        ����     : ���ûص�����
        ����	 : �ǳ�ʧ�ܵĻص�����
        ����ֵ   :  ��
        ��ע     :
        **************************************************************************/
        void SetChatCallBack(ChatCallBack *pCallback);

        /**************************************************************************
        	������   : Logout
        	����     : ���û�����ע������Ҫ�����û����л�������Ҫ����ע������
        	����	 : 1��CBOnSuccess   �ǳ��ɹ��Ļص�����
        			   2��CBOnError     �ǳ�ʧ�ܵĻص�����
        	����ֵ   :  ��
        	��ע     : ����Ҫ�л��ʺ�ʱ����Ҫlogout�ص��ɹ�����ʧ�ܺ�����ٴ�login������login���ܻ�ʧ�ܡ�
        **************************************************************************/
        void Logout();

        /**************************************************************************
        ������   : Login
        ����     : �û���¼��Ѷ��̨������
        ����	 : 1��sdk_app_id   ���ڱ�ʶ����sdk��Ӧ��id
        2��tim_user     �û��˺�, ������дaccount_type��identifier��app_id_at_3rd
        3��user_sig      ���ɵ�sig ��Կ
        4��CBOnSuccess   ��¼�ɹ��Ļص�����
         5��CBOnError     ��¼ʧ�ܵĻص�����
        ����ֵ   : int
        ��ע     : ���°汾Ϊ 180 �죬Ҳ����˵�������޵ģ����Կ�������Ҫ���ն˶��ڵ��Լ��ĺ�̨���������»�ȡ�µ� usersig �Ӷ������û����� usersig ���ڵ�����
        **************************************************************************/
        int  Login(int sdk_app_id, const TIMUserInfo *tim_user, const char* user_sig);

        ////////////////////////////////////////////////////////////////////////////////////////////
        /**************************************************************************
        	������   : CreateC2CConversation
        	����     : ��ȡ�Ự
        	����	 : 1��peer   �Է���identifier
        	����ֵ   : ��
        	��ע     :  һ��Ҫ�ǵõ���DestroyC2CConversation�����ٻ�ȡ����TIMConversationHandle
        **************************************************************************/
        TIMConversationHandle CreateC2CConversation(const char * peer);

        /**************************************************************************
        	������   : DestroyC2CConversation
        	����     : ���ٻỰ
        	����	 : 1��handle      ��CreateC2CConversation �����õ�
        	����ֵ   : ��
        	��ע     : һ��Ҫ����DestroyC2CConversation�����ٻỰ
        **************************************************************************/
        void  DestroyC2CConversation(TIMConversationHandle handle);

        /**************************************************************************
        	������   : DoSendTxtMessage
        	����     : �����ı���Ϣ
        	����	 : 1��peer   �Է���identifier
        	           2��content ������Ҫ���͵��ı���Ϣ
        	����ֵ   : TIMMessageHandle
        	��ע     : ��
        **************************************************************************/
        TIMMessageHandle DoSendTxtMessage(const char * peer, const string content);

        /**************************************************************************
        	������   : DoSendPicMessaage
        	����     : ����ͼƬ��Ϣ
        	����	 : 1��peer   �Է���identifier
        	           2��path  ������Ҫ���͵�ͼƬ��Ϣ
        	����ֵ   : ��
        	��ע     :
        **************************************************************************/
        TIMMessageHandle DoSendPicMessage(const char * peer, const string path);

        /**************************************************************************
        	������   : DoSendFaceMessage
        	����     : ���ͱ��鹦��
        	����	 : 1��peer   �Է���identifier
        	           2��index  ������Ҫ���͵ı�������
        	����ֵ   : ��
        	��ע     :
        **************************************************************************/
        void DoSendFaceMessage(const char * peer, const int Index);

        /**************************************************************************
        ������   : DoGetFriendList
        ����     : ��ȡ���к�������
        ����	 : ��
        ����ֵ   : ��
        ��ע     :
        **************************************************************************/
        void DoGetFriendList();

        /**************************************************************************
        ������   : GetSelfProfile
        ����     : ��ȡ�Լ�������
        ����	 : ��
        ����ֵ   : string
        ��ע     :
        **************************************************************************/
        void	GetSelfProfile();

        /**************************************************************************
        ������   : GetSelfNickName
        ����     : ��ȡ�Լ����ǳ�
        ����	 : ��
        ����ֵ   : string
        ��ע     :
        **************************************************************************/
        string	GetSelfNickName(TIMSelfProfileHandle handle);

        /**************************************************************************
        ������   : SetSelfNickName
        ����     : �����Լ��ı���
        ����	 : ��
        ����ֵ   : string
        ��ע     :
        **************************************************************************/
        int	SetSelfNickName(string name);

        /**************************************************************************
        ������   : GetFriendNickName
        ����     : ��ȡ�Լ����ǳ�
        ����	 : ��
        ����ֵ   : string
        ��ע     :
        **************************************************************************/
        string	GetFriendNickName(TIMSelfProfileHandle handle);

        /**************************************************************************
        ������   : DoGetLocalStoreMsgs();
        ����     : ��ȡ������ʷ��Ϣ
        ����	 : ��
        ����ֵ   : void
        ��ע     :
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

