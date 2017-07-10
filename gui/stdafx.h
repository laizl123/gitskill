// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息

// Windows 头文件:
#include <windows.h>
#include <wininet.h>
// TODO: 在此处引用程序需要的其他头文件

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 在此处引用程序需要的其他头文件
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
#include <vld.h>//如果找不这个头文件，去下载：http://vld.codeplex.com/
#endif
