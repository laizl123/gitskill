#pragma once

/**********************************************************************
**
**	ThemeUtil.h : include file
**
**	by Andrzej Markowski June 2004
**
**********************************************************************/

#include "TmSchema.h"

#define THM_WM_THEMECHANGED     0x031A

//##ModelId=4610706A0014
typedef struct _MY_MARGINS
{
    int cxLeftWidth;
    int cxRightWidth;
    int cyTopHeight;
    int cyBottomHeight;
} MY_MARGINS;

//##ModelId=4610706A002E
class CThemeUtil
{
public:
	//##ModelId=4610706A002F
	CThemeUtil();
	//##ModelId=4610706A0030
	virtual ~CThemeUtil();
	//##ModelId=4610706A0032
	BOOL OpenThemeData(HWND hWnd, LPCWSTR pszClassList);
	//##ModelId=4610706A0040
	void CloseThemeData();
	//##ModelId=4610706A0041
	BOOL DrawThemePart(HDC hdc, int iPartId, int iStateId, const RECT *pRect);
	//##ModelId=4610706A0046
	BOOL GetThemeColor(int iPartId, int iStateId, int iPropId, const COLORREF *pColor);
	//##ModelId=4610706A004F
	BOOL GetThemeInt(int iPartId, int iStateId, int iPropId, const int *piVal);
	//##ModelId=4610706A0054
	BOOL GetThemeMargins(int iPartId, int iStateId, int iPropId, const MY_MARGINS *pMargins);
	//##ModelId=4610706A0059
	BOOL GetThemeEnumValue(int iPartId, int iStateId, int iPropId, const int *piVal);
	//##ModelId=4610706A0060
	BOOL GetThemeFilename(int iPartId, int iStateId, int iPropId, 
							OUT LPWSTR pszThemeFileName, int cchMaxBuffChars);
	//##ModelId=4610706A0066
	BOOL GetCurrentThemeName(OUT LPWSTR pszThemeFileName, int cchMaxNameChars, 
							OUT OPTIONAL LPWSTR pszColorBuff, int cchMaxColorChars,
							OUT OPTIONAL LPWSTR pszSizeBuff, int cchMaxSizeChars);
	//##ModelId=4610706A0070
	HBITMAP LoadBitmap(LPWSTR pszBitmapName);
private:
	//##ModelId=4610706A0072
	BOOL IsWinXP(void);
	//##ModelId=4610706A0074
	void FreeLibrary();
private:
	//##ModelId=4610706A0075
	HINSTANCE m_hUxThemeDll;
	//##ModelId=4610706A007D
	HINSTANCE m_hRcDll;
	//##ModelId=4610706A007E
	UINT m_hTheme;
};
