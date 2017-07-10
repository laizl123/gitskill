//
// CDXFilter.cpp
//

/*-----------------------------------------------------*\
			HQ Tech, Make Technology Easy!       
 More information, please go to http://hqtech.nease.net.
/*-----------------------------------------------------*/

#include "stdafx.h"
#include "CDXFilter.h"
#include "UFilterUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////////
CDXFilter::CDXFilter(IGraphBuilder * inGraph, GUID inClsid, const char * inName)
{
	mGraph  = inGraph;	
	mClsid  = inClsid;
	mFilter = NULL;

	if (inName)
	{
		MultiByteToWideChar(CP_ACP, 0, inName, -1, mName, 256);
	}
	else
	{
		wcscpy(mName, L"");
	}
}

CDXFilter::~CDXFilter()
{
	ReleaseFilter();
}

BOOL CDXFilter::CreateFilter(CString strDiv)
{
	if (!mFilter && mGraph)
	{
		if (SUCCEEDED(CoCreateInstance(mClsid, NULL, CLSCTX_INPROC_SERVER,
			IID_IBaseFilter, (void **)&mFilter)))
		{
			if (SUCCEEDED(mGraph->AddFilter(mFilter, mName)))
			{
				return TRUE;
			}
		}
	}
	ReleaseFilter();
	return FALSE;
}

BOOL CDXFilter::Attach(IBaseFilter * inFilter, const char * inName)
{
	ReleaseFilter();
	
	if (inName)
	{
		MultiByteToWideChar(CP_ACP, 0, inName, -1, mName, 256);
	}

	if (mGraph && inFilter)
	{
		if (SUCCEEDED(mGraph->AddFilter(inFilter, mName)))
		{
			mFilter = inFilter;
			mFilter->AddRef();  // Add extra refercence count
			return TRUE;
		}
	}
	return FALSE;
}

void CDXFilter::Detach(void)
{
	if (mFilter)
	{
		mFilter->Release();
		mFilter = NULL;
	}
}

BOOL CDXFilter::QueryInterface(REFIID inIID, LPVOID * outObj)
{
	if (mFilter)
	{
		HRESULT hr = mFilter->QueryInterface(inIID, outObj);
		return SUCCEEDED(hr);
	}
	return FALSE;
}

void CDXFilter::ReleaseFilter(void)
{
	TRACE("--> ReleaseFilter开始 <--\r\n");
	if (mFilter)
	{
		if (mGraph)
		{
			TRACE("--> mGraph->RemoveFilter开始 <--\r\n");
			mGraph->RemoveFilter(mFilter);
			TRACE("--> mGraph->RemoveFilter结束 <--\r\n");
		}
		mFilter->Release();
		TRACE("--> mFilter->Release() <--\r\n");
		mFilter = NULL;
	}
	TRACE("--> ReleaseFilter结束 <--\r\n");
}

IBaseFilter * CDXFilter::GetFilter(void)
{
	return mFilter;
}

IPin * CDXFilter::GetPin(BOOL inInput, const char * inPartialName)
{
	return UFilterUtils::GetPin(mFilter, inInput, inPartialName);
}

BOOL CDXFilter::GetPinCount(int & outInputPin, int & outOutputPin)
{
	return UFilterUtils::GetPinCount(mFilter, outInputPin, outOutputPin);
}