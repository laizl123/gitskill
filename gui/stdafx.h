// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ

// Windows ͷ�ļ�:
#include <windows.h>
#include <wininet.h>
// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include <objbase.h>
#include <vector>
#include <string>
#include <map>
#include <commctrl.h>
#include <tchar.h>
#include <shlwapi.h>
#include <list>
#include "ui\DuiLib\UIlib.h"
#include "unity\CommonDef.h"
namespace DuiLib
{
// tString is a TCHAR std::string
typedef std::basic_string<TCHAR> tString;
}
#ifndef NO_USING_DUILIB_NAMESPACE
using namespace DuiLib;
using namespace std;
#endif


#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "ui\\bin\\DuiLib_ud.lib")
#   else
#       pragma comment(lib, "ui\\bin\\DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "ui\\bin\\DuiLib_u.lib")
#   else
#       pragma comment(lib, "ui\\bin\\DuiLib.lib")
#   endif
#endif

#define USE(FEATURE) (defined USE_##FEATURE  && USE_##FEATURE)
#define ENABLE(FEATURE) (defined ENABLE_##FEATURE  && ENABLE_##FEATURE)

#define USE_ZIP_SKIN 1
#define USE_EMBEDED_RESOURCE 1

#define MESSAGE_RICHEDIT_MAX  1024


#ifdef _DEBUG
#include <vld.h>//����Ҳ����ͷ�ļ���ȥ���أ�http://vld.codeplex.com/
#endif
