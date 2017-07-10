// TextResource.cpp: implementation of the CTextResource class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TextResource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTextResource::CTextResource()
: CResourceItem(RES_TYPE_TEXT)
{

}

CTextResource::~CTextResource()
{
	FreeResource();
}

void CTextResource::FreeResource()
{
	m_mapText.clear();
}

//<text id="0" name="title" > 启动包安装</text>
bool CTextResource::ReadResource(CXMLDOMInterface& Dom,IXMLDOMNode* pXMLNode)
{
	FreeResource();
	BOOL bResult = TRUE;
	IXMLDOMNode* pImageNode = pXMLNode;
	if(pImageNode)
	{
		int nChildCount = Dom.GetChildrenCount(pImageNode);
		
		for(int i=0; i<nChildCount; i++)
		{
			IXMLDOMNode* pText = NULL;
			bResult &= Dom.GetChildNode(pImageNode, &pText, NULL, i );
			if(pText)
			{
				stText text;
				CString sTemp;
				bResult &= Dom.GetNodeAttribute(pText,"id",sTemp);

				text.nIndex = atoi(sTemp);
				
				bResult &= Dom.GetNodeAttribute(pText,"name",text.sTextName);
				
				bResult &= Dom.GetNodeText(pText, text.sText);
				
				m_mapText.insert(make_pair(text.sTextName, text));				
			}
		}
	}
	
	return bResult;
}



LPCSTR CTextResource::GetText(CString sTextName)
{
	map<string, stText>::iterator it = m_mapText.find(string(sTextName));
	
	if(it == m_mapText.end())
		return "";
	
	stText text = it->second;
	
	return text.sText;
}