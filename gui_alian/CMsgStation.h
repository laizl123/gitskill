//
// CMsgStation.h
// 

#ifndef __H_CMsgStation__
#define __H_CMsgStation__

#include "CObjectList.h"

typedef long MessageT;
typedef long NotifyT;

class CMsgReceiver;
class CMsgStation
{
protected:
	CObjectList		mReceivers;

public:
	CMsgStation(void);
	virtual ~CMsgStation(void);	

	void AddMsgReceiver(CMsgReceiver * inReceiver);
	void RemoveMsgReceiver(CMsgReceiver * inReceiver);

	bool Broadcast(MessageT inMessage, void * ioParam = 0, void * ioParam2 = 0);
	bool Notify(NotifyT inNotification, long inParam1 = 0, long inParam2 = 0);

};

const MessageT msg_StationDestroyed = 0;
const MessageT msg_Notify           = 1;

struct SNotificationStruct
{
	NotifyT			mNotification;
	CMsgStation *	mStation;
	long			mParam1;
	long			mParam2;
};

#endif // __H_CMsgStation__