// AudioRenderDevices.cpp: implementation of the CAudioRenderDevices class.
//
//////////////////////////////////////////////////////////////////////
// + [9/10/2007 lixg]
#include "stdafx.h"
#include <streams.h>
#include "AudioRenderDevices.h"
#include "UDsUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CAudioRenderDevices * CAudioRenderDevices::sDevices = NULL;
/////////////////////////////////////////////////////////////////////////
CAudioRenderDevices::CAudioRenderDevices()
{
	Populate();
}

CAudioRenderDevices::~CAudioRenderDevices()
{
	mList.RemoveAll();
}

CAudioRenderDevices * CAudioRenderDevices::Instance(void)
{
	if (sDevices == NULL)
	{
		sDevices = new CAudioRenderDevices();
	}
	return sDevices;
}

void CAudioRenderDevices::Release(void)
{
	if (sDevices)
	{
		delete sDevices;
		sDevices = NULL;
	}
}

void CAudioRenderDevices::Populate(void)
{
	mList.RemoveAll();
	UDsUtils::QueryAudioRenderDevices(mList);
}
