//
// CDSDevice.cpp
//

/*-----------------------------------------------------*\
			HQ Tech, Make Technology Easy!       
 More information, please go to http://hqtech.nease.net.
/*-----------------------------------------------------*/

#include "stdafx.h"
#include "CDSDevice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////
CDSDevice::CDSDevice()
{
	mType         = DT_Unknown;
	mFriendlyName = "";
	mDisplayName  = "";
}

CDSDevice::~CDSDevice()
{
}

CDSDevice& CDSDevice::operator = (const CDSDevice& inDevice)
{
	mType         = inDevice.mType;
	mFriendlyName = inDevice.mFriendlyName;
	mDisplayName  = inDevice.mDisplayName;
	return *this;
}

void CDSDevice::SetDevideType(Device_Type inType)
{
	mType = inType;
}

Device_Type CDSDevice::GetDeviceType(void)
{
	return mType;
}

BOOL CDSDevice::IsDVDevice(void)
{
	return (mType == DT_DV);
}

void CDSDevice::SetDeviceFriendlyName(const char * inName)
{
	mFriendlyName = inName;
}

CString CDSDevice::GetDeviceFriendlyName(void)
{
	return mFriendlyName;
}

void CDSDevice::SetDeviceDisplayName(const char * inName)
{
	mDisplayName = inName;
}

CString CDSDevice::GetDeviceDisplayName(void)
{
	return mDisplayName;
}