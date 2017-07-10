// WebOperation.cpp: implementation of the CWebOperation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "icservingagentclient.h"
#include "WebOperation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include <comutil.h>
#include <string>
using namespace std;

struct ItemAttribute
{
	CHAR strAttributeName[MAX_PATH];
	CHAR strAttributeValue[MAX_PATH];
};

struct TagAttribute
{
	CHAR sTagName[MAX_PATH];
	ItemAttribute* itematt;
};


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWebOperation::CWebOperation()
{

}

CWebOperation::~CWebOperation()
{

}

BOOL CWebOperation::XTools(IHTMLDocument2* pDocument2, string sUserName, string sPassword, BOOL bAutoLogin )
{
	if(!pDocument2)
		return FALSE;
	
	CComQIPtr <IHTMLElement> pElement;
	HRESULT hr = pDocument2->get_body(&pElement);
	if(FAILED(hr))
		return FALSE;
	
	CComQIPtr <IHTMLElement2> pElement2;
	pElement->QueryInterface(IID_IHTMLElement2,(void**)&pElement2);
	
	CComQIPtr <IHTMLElementCollection> pElementColl;
	CComBSTR tagName("INPUT");
	hr = pElement2->getElementsByTagName(tagName,&pElementColl);
	if(FAILED(hr))
		return FALSE;
	
	long lCollCount = 0;
	pElementColl->get_length(&lCollCount);
	//type="text" name="user"

	for(long l=0; l<lCollCount; l++)
	{
		_variant_t index = l;
		CComQIPtr<IDispatch> ppvdispOption;
		hr = pElementColl->item(index,index,&ppvdispOption);
		if(SUCCEEDED(hr))
		{
			CComQIPtr <IHTMLInputElement > pInputElem;
			hr = ppvdispOption->QueryInterface( IID_IHTMLInputElement , 
				(void **) &pInputElem);
			if(SUCCEEDED(hr))
			{				
				CComBSTR bsType, bsName;
				pInputElem->get_type(&bsType);
				pInputElem->get_name(&bsName);
				
				CString sTypeVal(bsType), sNameVal(bsName);
				sTypeVal.MakeLower();
				sNameVal.MakeLower();
				if(sTypeVal=="text" && sNameVal=="user")
				{
					pInputElem->put_value(CComBSTR(sUserName.c_str()));
				}
				else if(sTypeVal=="password" && sNameVal=="pass")
				{
					pInputElem->put_value(CComBSTR(sPassword.c_str()));
				}
			}
		}
	}
	
	return TRUE;
}
