//
// CAudioDevices.h
//

#ifndef __H_CAudioDevices__
#define __H_CAudioDevices__

#include "CDSDevice.h"

// Attention: this is a singleton

class CAudioDevices
{
public:
	DEVICE_LIST         mList;

public:
	static CAudioDevices * Instance(void);
	static void Release(void);
	void Populate(void);

protected:
	CAudioDevices();
	~CAudioDevices();

private:
	static CAudioDevices * sDevices;	
};

#endif // __H_CAudioDevices__