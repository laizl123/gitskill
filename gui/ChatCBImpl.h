#pragma once
#include "IMlibs/c_includes/tim_msg_c.h"
#include "IMlibs/c_includes/tim_friend_c.h"
class CChatCBImpl
{
    public:
        CChatCBImpl();
        virtual ~CChatCBImpl();

        /**************************************************************************
        	������   : ChatCBOnNewMessage
        	����     : ����Ϣ֪ͨ�Ļص�����
        	����	 : 1��TIMMessageHandle   ���Ի�ȡ��Ϣ����ػỰ����ϸ��Ϣ
        	           2��msg_num            δ����Ϣ��Ŀ
        			   3��data               �û�����
        	����ֵ   : ��
        	��ע     : ��
        **************************************************************************/
        virtual void CBOnNewMessage(TIMMessageHandle* handles, uint32_t msg_num, void* data) = 0;

        virtual void CBConnOnConnected(void * data)  = 0;

        virtual void CBConnOnDisconnected(void *data) = 0;

        virtual void CBKickOffLine(void *data) = 0;

        virtual void LoginOnSuccess(void* data) = 0;

        virtual void LoginOnError(int code, const char* desc, void* data) = 0;

        virtual void LogoutOnSuccess(void* data) = 0;

        virtual void LogoutOnError(int code, const char* desc, void* data) = 0;

        virtual void GetFriendListCallbackOnSuccess(void** handles, uint32_t num, void* data) = 0;

        virtual void GetFriendListCallbackOnError(int code, const char* desc, void* data) = 0;

        virtual void SendTxtMsgOnSuccess(void* data) = 0;

        virtual void SendTxtMsgError(int code, const char* desc, void* data) = 0;

        virtual void SendPicMsgOnSuccess(void * data) = 0;

        virtual void SendPicMsgError(int code, const char* desc, void* data) = 0;

        virtual void RecvPicMsgOnSucess(void * data) = 0;

        virtual void RecvPicMsgError(int code, const char* desc, void* data) = 0;

        virtual void CBGetMsgOnSuccess(TIMMessageHandle* handle_array, int size, void* data) = 0;

        virtual void CBGetMsgOnError(int code, const char* desc, void* data) = 0;

        virtual void CBOnSuccess(void *data) = 0;

        virtual void CBOnError(int code, const char* desc, void* data) = 0;
        virtual void CBGetSelfProfileCallbackOnSuccess(TIMSelfProfileHandle* handles, uint32_t num, void* data) = 0;
        virtual void CBGetSelfProfileCallbackOnError(int code, const char* desc, void* data) = 0;

    protected:
        bool m_bLoginSuccess;
};

