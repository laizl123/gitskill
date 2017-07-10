//
// UDsUtils.h
//

#ifndef __H_UDsUtils__
#define __H_UDsUtils__

#include "CAVDevice.h"
#include "CDSDevice.h"	// + [9/11/2007 lixg]
class UDsUtils
{
public:
	UDsUtils() {};
	~UDsUtils() {};

	static void NukeDownstream(IGraphBuilder * inGraph, IBaseFilter * inFilter);
	static void NukeUpstream(IGraphBuilder * inGraph, IBaseFilter * inFilter);
	static BOOL ShowFilterPropertyPage(IBaseFilter * inFilter);
	//////////////////////////////////////////////////////////////////////////
	// + [9/11/2007 lixg]
	static BOOL QueryAudioCaptureDevices(DEVICE_LIST & outDevices);
	static BOOL QueryAudioRenderDevices(DEVICE_LIST & outDevices);
	static IBaseFilter * CreateAudioRenderDevice(const char * inFriendlyName);
	//////////////////////////////////////////////////////////////////////////

	static IBaseFilter * CreateCompressor(BOOL inIsVideo, const char * inName);
	static IBaseFilter * CreateHardwareFilter(GUID inCategory, 
		const char * inFriendlyName);

	static IBaseFilter * CreateCamera(CAVDevice& outDevice, CString strDiv = "");
	static IBaseFilter * CreateAudioDevice(CAVDevice& outDevice);
	static IBaseFilter * CreateAudioCapDevice( CAVDevice& outDevice, const char * inFriendlyName);	// + [9/14/2007 lixg];
private:
	static IBaseFilter * CreateAVDevice(GUID inCategory, CAVDevice& outDevice);
	static IBaseFilter * CreateAVDevice(GUID inCategory, const char * inFriendlyName,  CAVDevice& outDevice);	// + [9/14/2007 lixg];
	static Device_Type DetermineDeviceType(IBaseFilter * inFilter);
	// + [9/11/2007 lixg]
	static BOOL QueryDeviceCategory(GUID inCategory, DEVICE_LIST & outDevices);
};

#endif // __H_UDsUtils__