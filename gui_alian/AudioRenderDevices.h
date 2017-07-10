// AudioRenderDevices.h: interface for the CAudioRenderDevices class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUDIORENDERDEVICES_H__649F32FB_CF69_491B_A23C_26E74F030603__INCLUDED_)
#define AFX_AUDIORENDERDEVICES_H__649F32FB_CF69_491B_A23C_26E74F030603__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CDSDevice.h"

// +Attention: this is a singleton [9/10/2007 lixg]
class CAudioRenderDevices  
{
public:
	DEVICE_LIST         mList;
	
public:
	static CAudioRenderDevices * Instance(void);
	static void Release(void);
	void Populate(void);

protected:
	CAudioRenderDevices();
	~CAudioRenderDevices();
	
private:
	static CAudioRenderDevices * sDevices;	
};

#endif // !defined(AFX_AUDIORENDERDEVICES_H__649F32FB_CF69_491B_A23C_26E74F030603__INCLUDED_)
