//
// CMsgReceiver.h
//

#ifndef __H_CMsgReceiver__
#define __H_CMsgReceiver__

#include "CMsgStation.h"

class CMsgReceiver
{
protected:
	CObjectList		mStations;

public:
	CMsgReceiver(void);
	virtual ~CMsgReceiver(void);

	void AddMsgStation(CMsgStation * inStation);
	void RemoveMsgStation(CMsgStation * inStation);

	virtual bool ReceiveMessage(MessageT inMessage, void * ioParam, 
		void * ioParam2);
	virtual bool Respond(NotifyT inNotification, CMsgStation * inStation,
		long inParam1, long inParam2);

};

#endif // __H_CMsgReceiver__