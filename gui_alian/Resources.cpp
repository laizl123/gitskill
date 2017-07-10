// Resources.cpp: implementation of the CResources class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Resources.h"

#include "XMLDOMInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTextResource* CResources::m_pTextResource = NULL;
CImageResource* CResources::m_pImageResource = NULL;
CIconResource* CResources::m_pIconResource = NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CResources::CResources()
{
	
}

CResources::~CResources()
{
	FreeResources();
}

void CResources::FreeResources()
{
	if(m_pTextResource)
	{
		delete m_pTextResource;
		m_pTextResource = NULL;
	}

	if(m_pImageResource)
	{
		delete m_pImageResource;
		m_pImageResource = NULL;
	}

	if(m_pIconResource)
	{
		delete m_pIconResource;
		m_pIconResource = NULL;
	}
}

bool CResources::LoadResources(CString strXMLFile)
{
	CXMLDOMInterface Dom;
	
	if (!Dom.Use_Enable())
	{
		return false;
	}
	
	IXMLDOMElement* pRoot= NULL;
	BOOL bOpen= Dom.OpenXMLFile(strXMLFile,&pRoot);
	if(!bOpen || !pRoot)
	{
		return false;
	}

	BOOL bResult = TRUE;
	IXMLDOMNode* pImageNode = NULL;
	bResult &= Dom.GetChildNode(pRoot, &pImageNode, "ImageResource");
	if(pImageNode)
	{
		if(m_pImageResource == NULL)
		{
			m_pImageResource = new CImageResource;
			
		}
		bResult &= m_pImageResource->ReadResource(Dom, pImageNode);
	}

	IXMLDOMNode* pIconNode = NULL;
	bResult &= Dom.GetChildNode(pRoot, &pIconNode, "IconResource");
	if(pIconNode)
	{
		if(m_pIconResource == NULL)
		{
			m_pIconResource = new CIconResource;
			
		}
		bResult &= m_pIconResource->ReadResource(Dom, pIconNode);
	}

	IXMLDOMNode* pTextNode = NULL;
	bResult &= Dom.GetChildNode(pRoot, &pTextNode, "TextResource");
	if(pTextNode)
	{
		if(m_pTextResource == NULL)
		{
			m_pTextResource = new CTextResource;
			
		}
		bResult &= m_pTextResource->ReadResource(Dom, pTextNode);
	}
	
	return bResult;
}

HBITMAP CResources::GetImageResource(CString sImageName)
{
	if(m_pImageResource == NULL)
		return NULL;
	return m_pImageResource->GetBitMap(sImageName);
}

HICON CResources::GetIconResource(CString sIconName)
{
	if(m_pIconResource == NULL)
		return NULL;
	return m_pIconResource->GetIcon(sIconName);
}

CString CResources::GetTextResource(CString sTextName)
{
	if(m_pTextResource == NULL)
		return "";
	return m_pTextResource->GetText(sTextName);
}