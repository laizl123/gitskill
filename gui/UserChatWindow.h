#pragma once
#include "ui/BaseWindow.h"
class CUserChatWindow : public CBaseWindow
{
    public:
        CUserChatWindow();
        ~CUserChatWindow();
    protected:
        virtual tString GetSkinFile();
};

