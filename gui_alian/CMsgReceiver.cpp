//
// CMsgReceiver.h
//

/*-----------------------------------------------------*\
			HQ Tech, Make Technology Easy!       
 More information, please go to http://hqtech.nease.net.
/*-----------------------------------------------------*/

#include "stdafx.h"
#include "CMsgReceiver.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMsgReceiver::CMsgReceiver(void)
{
}

CMsgReceiver::~CMsgReceiver(void)
{
	for (int i = mStations.GetSize() - 1; i >= 0; i --)
	{
		CMsgStation * station = (CMsgStation *) mStations.GetAt(i);
		if (station)
		{
			station->RemoveMsgReceiver(this);
		}
	}
}

void CMsgReceiver::AddMsgStation(CMsgStation * inStation)
{
	mStations.Add(inStation);
}

void CMsgReceiver::RemoveMsgStation(CMsgStation * inStation)
{
	mStations.Remove(inStation);
}

bool CMsgReceiver::ReceiveMessage(MessageT inMessage, void * ioParam, void * ioParam2)
{
	switch (inMessage)
	{
	case msg_Notify:
		{
			SNotificationStruct * notification = (SNotificationStruct *)ioParam;
			return Respond(notification->mNotification, notification->mStation,
				notification->mParam1, notification->mParam2);
		}

	case msg_StationDestroyed:
		RemoveMsgStation((CMsgStation *)ioParam);
		return true;
	}
	return false;
}

bool CMsgReceiver::Respond(NotifyT inNotification, CMsgStation * inStation,
						long inParam1, long inParam2)
{
	return false;
}
