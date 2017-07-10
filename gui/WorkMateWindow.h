#pragma once
#include "ui/BaseWindow.h"
class CWorkMateWindow: public CBaseWindow
{
    public:
        CWorkMateWindow();
        ~CWorkMateWindow();
    protected:
        virtual tString GetSkinFile();
        virtual void Init();
    private:
};

