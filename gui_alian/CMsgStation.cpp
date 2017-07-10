//
// CMsgStation.cpp
// 

/*-----------------------------------------------------*\
			HQ Tech, Make Technology Easy!       
 More information, please go to http://hqtech.nease.net.
/*-----------------------------------------------------*/

#include "stdafx.h"
#include "CMsgStation.h"
#include "CMsgReceiver.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMsgStation::CMsgStation(void)
{
}

CMsgStation::~CMsgStation(void)
{
	Broadcast(msg_StationDestroyed, (void *)this);
}

void CMsgStation::AddMsgReceiver(CMsgReceiver * inReceiver)
{
	if (inReceiver)
	{
		if (mReceivers.GetIndex(inReceiver) == -1)
		{
			mReceivers.Add(inReceiver);
			inReceiver->AddMsgStation(this);
		}
	}
}

void CMsgStation::RemoveMsgReceiver(CMsgReceiver * inReceiver)
{
	if (inReceiver)
	{
		inReceiver->RemoveMsgStation(this);
		mReceivers.Remove(inReceiver);
	}
}

bool CMsgStation::Broadcast(MessageT inMessage, void * ioParam, void * ioParam2)
{
//	TRACE("CMsgStation::Broadcast\r\n");
	for (int i = mReceivers.GetSize() - 1; i >= 0; i --)
	{
		CMsgReceiver * receiver = (CMsgReceiver *)mReceivers.GetAt(i);
		if (receiver)
		{
			//TRACE("receiver->ReceiveMessage\r\n");
			receiver->ReceiveMessage(inMessage, ioParam, ioParam2);
			//TRACE("receiver->ReceiveMessageOK\r\n");
		}
	}
//	TRACE("CMsgStation::BroadcastOK\r\n");
	return true;
}

bool CMsgStation::Notify(NotifyT inNotification, long inParam1, long inParam2)
{
	SNotificationStruct   notification;
	notification.mNotification = inNotification;
	notification.mStation = this;
	notification.mParam1  = inParam1;
	notification.mParam2  = inParam2;
	TRACE("Notify\r\n");
	return Broadcast(msg_Notify, &notification);
}

