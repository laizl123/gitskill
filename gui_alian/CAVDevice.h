//
// CAVDevice.h
//

#ifndef __H_CAVDevice__
#define __H_CAVDevice__

#include "GlobalDefs.h"

class CAVDevice
{
private:
	Device_Type		mType;
	CString			mFriendlyName;
	CString			mDisplayName;

	long			mVideoResolution;
	long			mAudioConnector;

public:
	CAVDevice();
	~CAVDevice();

	CAVDevice& operator = (const CAVDevice&);

	void SetDevideType(Device_Type inType);
	Device_Type GetDeviceType(void);

	BOOL IsDVDevice(void);
	BOOL IsDeviceAvailable(void);

	void SetDeviceFriendlyName(const char * inName);
	CString GetDeviceFriendlyName(void);

	void SetDeviceDisplayName(const char * inName);
	CString GetDeviceDisplayName(void);

	void SetVideoResolution(long inResolution);
	long GetVideoResolution(void);

	void SetAudioConnector(long inConnector);
	long GetAudioConnector(void);
};

#endif // __H_CAVDevice__