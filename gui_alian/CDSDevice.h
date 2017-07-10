//
// CDSDevice.h
//

#ifndef __H_CDSDevice__
#define __H_CDSDevice__

#include <afxtempl.h>
#include "GlobalDefs.h"

class CDSDevice
{
private:
	Device_Type    mType;
	CString        mFriendlyName;
	CString        mDisplayName;

public:
	CDSDevice();
	~CDSDevice();

	CDSDevice& operator = (const CDSDevice&);

	void SetDevideType(Device_Type inType);
	Device_Type GetDeviceType(void);
	BOOL IsDVDevice(void);

	void SetDeviceFriendlyName(const char * inName);
	CString GetDeviceFriendlyName(void);

	void SetDeviceDisplayName(const char * inName);
	CString GetDeviceDisplayName(void);
};

typedef CList<CDSDevice, CDSDevice&>  DEVICE_LIST;

#endif // __H_CDSDevice__