// BmpResoure.cpp: implementation of the CBmpResource class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "BmpResource.h"

CBitmap CBmpResource::m_bmpIEAddpage;
//  LAMP
CBitmap CBmpResource::m_bmpLampWait;
CBitmap CBmpResource::m_bmpLampPark;
CBitmap CBmpResource::m_bmpLampTalk;
CBitmap CBmpResource::m_bmpLampHold;
CBitmap CBmpResource::m_bmpLampOutdial;
CBitmap CBmpResource::m_bmpLampProcess;
CBitmap CBmpResource::m_bmpLampIncomingcall;
CBitmap CBmpResource::m_bmpLampIncomingcallWink;
// add by lh.wang date:2012.12.25
CBitmap CBmpResource::m_bmpLampConference;
// end add

// NET
CBitmap CBmpResource::m_bmpNetVerybad;
CBitmap CBmpResource::m_bmpNetGood;
CBitmap CBmpResource::m_bmpNetBusy;
CBitmap CBmpResource::m_bmpNetBad;
// title
CBitmap CBmpResource::m_bmpTitleFillBG;
CBitmap CBmpResource::m_bmpToolbarFillBG;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBmpResource::CBmpResource()
{

}

CBmpResource::~CBmpResource()
{

}

// 读取位图
void CBmpResource::LoadBitmapResource()
{
	m_bmpIEAddpage.LoadBitmap(IDB_BMP_IEADDPAGE);
	//  LAMP
	m_bmpLampWait.LoadBitmap(IDB_BMP_LAMP_WAIT);
	m_bmpLampPark.LoadBitmap(IDB_BMP_LAMP_PARK);
	m_bmpLampTalk.LoadBitmap(IDB_BMP_LAMP_TALK);
	m_bmpLampHold.LoadBitmap(IDB_BMP_LAMP_HOLD);
	m_bmpLampOutdial.LoadBitmap(IDB_BMP_LAMP_OUTDIAL);
	m_bmpLampProcess.LoadBitmap(IDB_BMP_LAMP_PROCESS);
	m_bmpLampIncomingcall.LoadBitmap(IDB_BMP_LAMP_INCOMINGCALL);
	m_bmpLampIncomingcallWink.LoadBitmap(IDB_BMP_LAMP_INCOMINGCALL_WINK);
	// add by lh.wang date:2012.12.25
	m_bmpLampConference.LoadBitmap(IDB_BMP_LAMP_CONFERENCE);
	// end add 
	// NET
	m_bmpNetVerybad.LoadBitmap(IDB_BMP_NET_VERYBAD);
	m_bmpNetGood.LoadBitmap(IDB_BMP_NET_GOOD);
	m_bmpNetBusy.LoadBitmap(IDB_BMP_NET_BUSY);
	m_bmpNetBad.LoadBitmap(IDB_BMP_NET_BAD);
	// title
	m_bmpTitleFillBG.LoadBitmap(IDB_BMP_TITLE_FILL_BG);
	m_bmpToolbarFillBG.LoadBitmap(IDB_BMP_TOOLBAR_FILL_BG);
}

// 释放位图
void CBmpResource::ReleaseBitmapResource()
{
	m_bmpIEAddpage.DeleteObject();
	//  LAMP
	m_bmpLampWait.DeleteObject();
	m_bmpLampPark.DeleteObject();
	m_bmpLampTalk.DeleteObject();
	m_bmpLampHold.DeleteObject();
	m_bmpLampOutdial.DeleteObject();
	m_bmpLampProcess.DeleteObject();
	m_bmpLampIncomingcall.DeleteObject();
	m_bmpLampIncomingcallWink.DeleteObject();
	// add by lh.wang date:2012.12.25
	m_bmpLampConference.DeleteObject();
	// end add 
	// NET
	m_bmpNetVerybad.DeleteObject();
	m_bmpNetGood.DeleteObject();
	m_bmpNetBusy.DeleteObject();
	m_bmpNetBad.DeleteObject();
	// title
	m_bmpTitleFillBG.DeleteObject();
	m_bmpToolbarFillBG.DeleteObject();
}
