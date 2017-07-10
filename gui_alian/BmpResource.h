// BmpResoure.h: interface for the CBmpResoure class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BMPRESOURE_H__2EC77B0F_C112_422B_A3F0_FBDDB6B4E2D4__INCLUDED_)
#define AFX_BMPRESOURE_H__2EC77B0F_C112_422B_A3F0_FBDDB6B4E2D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBmpResource  
{
public:
	CBmpResource();
	virtual ~CBmpResource();
public:
	// 读取位图
	static void LoadBitmapResource();
	// 释放位图
	static void ReleaseBitmapResource();

public:
	static CBitmap m_bmpIEAddpage;
	//  LAMP
	static CBitmap m_bmpLampWait;
	static CBitmap m_bmpLampPark;
	static CBitmap m_bmpLampTalk;
	static CBitmap m_bmpLampHold;
	static CBitmap m_bmpLampOutdial;
	static CBitmap m_bmpLampProcess;
	static CBitmap m_bmpLampIncomingcall;
	static CBitmap m_bmpLampIncomingcallWink;
	// add by lh.wang date:2012.12.25
	static CBitmap m_bmpLampConference;
	// end add 

	// NET
	static CBitmap m_bmpNetVerybad;
	static CBitmap m_bmpNetGood;
	static CBitmap m_bmpNetBusy;
	static CBitmap m_bmpNetBad;
	// title
	static CBitmap m_bmpTitleFillBG;
	static CBitmap m_bmpToolbarFillBG;
};

#endif // !defined(AFX_BMPRESOURE_H__2EC77B0F_C112_422B_A3F0_FBDDB6B4E2D4__INCLUDED_)
