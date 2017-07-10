//
// CAudioDevices.cpp
//

/*-----------------------------------------------------*\
			HQ Tech, Make Technology Easy!       
 More information, please go to http://hqtech.nease.net.
/*-----------------------------------------------------*/

#include "stdafx.h"
#include <streams.h>
#include "CAudioDevices.h"
#include "UDsUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAudioDevices * CAudioDevices::sDevices = NULL;
/////////////////////////////////////////////////////////////////////////
CAudioDevices::CAudioDevices()
{
	Populate();
}

CAudioDevices::~CAudioDevices()
{
	mList.RemoveAll();
}

CAudioDevices * CAudioDevices::Instance(void)
{
	if (sDevices == NULL)
	{
		sDevices = new CAudioDevices();
	}
	return sDevices;
}

void CAudioDevices::Release(void)
{
	if (sDevices)
	{
		delete sDevices;
		sDevices = NULL;
	}
}

void CAudioDevices::Populate(void)
{
	mList.RemoveAll();
	UDsUtils::QueryAudioCaptureDevices(mList);
}
