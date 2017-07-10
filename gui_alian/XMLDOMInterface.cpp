#include "stdafx.h"
#include "XMLDOMInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

namespace ibXML{

short wstrcmp(BSTR str1,BSTR str2)
{
	static DWORD i;
	static short res;
	for(i=0;str1[i]==str2[i]&&str1[i]!=0&&str2[i]!=0;i++);
	return str1[i]-str2[i];
}

CXMLDOMInterface::CXMLDOMInterface()
{
	m_pdoc= NULL;

	HRESULT hr;//=::CoInitialize(NULL);
	hr=CoCreateInstance(CLSID_DOMDocument,NULL,
		CLSCTX_ALL,IID_IXMLDOMDocument,(void**)&m_pdoc);

	if(FAILED(hr))
	{
		m_pdoc=NULL;
		m_bInitialized=false;
		return;
	}
	m_bInitialized=true;
}

CXMLDOMInterface::~CXMLDOMInterface()
{
	if(!Use_Enable()) {
		return;
	}
	
	if(m_pdoc) {
		m_pdoc->Release();
		m_pdoc= NULL;
	}
}

BOOL CXMLDOMInterface::OpenXMLFile(LPCTSTR lpName, IXMLDOMElement** pRoot)
{
	if(!Use_Enable()) return false;
	m_OpenMutex.Lock();
	HRESULT hr;
	VARIANT_BOOL btmp;
	hr=m_pdoc->load(_variant_t(lpName),&btmp);
	if(FAILED(hr)||btmp==VARIANT_FALSE)
	{
//		AfxMessageBox("XMLError:Open XML document failed!",MB_OK|MB_ICONSTOP);
		m_OpenMutex.Unlock();return false;
	}
	hr=m_pdoc->get_documentElement(pRoot);
	if(FAILED(hr))
	{
//		AfxMessageBox("XMLError:Get root element failed!",MB_OK|MB_ICONSTOP);
		m_OpenMutex.Unlock();return false;
	}
	m_OpenMutex.Unlock();
	return true;
}

//BOOL CXMLDOMInterface::LoadXMLString(LPCTSTR lpXML, IXMLDOMElement** pRoot)
//{
//	if(!Use_Enable()) return false;
//	m_OpenMutex.Lock();
//	DWORD len=strlen(lpXML);
//	BSTR wstr=CString(lpXML).AllocSysString();
//	if(wstr==NULL) {m_OpenMutex.Unlock();return false;}
//	VARIANT_BOOL btmp;
//	HRESULT hr;
//	hr=m_pdoc->loadXML(wstr,&btmp);
//	SysFreeString(wstr);
//	if(FAILED(hr)||btmp==VARIANT_FALSE) 
//	{
////		AfxMessageBox("XMLError:Load XML String failed!",MB_OK|MB_ICONSTOP);
//		m_OpenMutex.Unlock();return false;
//	}
//	hr=m_pdoc->get_documentElement(pRoot);
//	if(FAILED(hr))
//	{
////		AfxMessageBox("XMLError:Get root element failed!",MB_OK|MB_ICONSTOP);
//		m_OpenMutex.Unlock();return false;
//	}
//	m_OpenMutex.Unlock();
//	return true;
//}

BOOL CXMLDOMInterface::GetChildNode(IXMLDOMNode *pNode, IXMLDOMNode **lplpNode, LPCTSTR lpName, long index)
{
	if(pNode==NULL) 
		return false;

	IXMLDOMNodeList* ilst;
	HRESULT hr;
	if(lpName)
	{
		BSTR wstr=CString(lpName).AllocSysString();		
		hr=pNode->selectNodes(wstr,&ilst);
		SysFreeString(wstr);

		if(FAILED(hr)||ilst==NULL) 
			return false;

		hr=ilst->get_item(index,lplpNode);
		ilst->Release();

		if(FAILED(hr)||*lplpNode==NULL)
			return false;
	}
	else
	{
		hr=pNode->get_childNodes(&ilst);
		if(FAILED(hr)) return false;

		ilst->get_item(index,lplpNode);
		ilst->Release();

		if(FAILED(hr)) return false;
	}
	return true;
}

BOOL CXMLDOMInterface::GetChildrenNodes(IXMLDOMNode *pNode, IXMLDOMNodeList **lplpLst, LPCTSTR lpName)
{
	if(pNode==NULL) return false;

	HRESULT hr;
	if(lpName)
	{
		BSTR wstr=CString(lpName).AllocSysString();
		hr=pNode->selectNodes(wstr,lplpLst);
		SysFreeString(wstr);
		if(FAILED(hr))
			return false;
	}
	else
	{
		hr=pNode->get_childNodes(lplpLst);
        if(FAILED(hr)) 
			return false;
	}
	return true;
}

long CXMLDOMInterface::GetChildrenCount(IXMLDOMNode* pNode, LPCTSTR lpName)
{
	if(pNode==NULL) return 0;
	IXMLDOMNodeList* ilst;
	HRESULT hr;
	if(lpName)
	{
		BSTR wstr=CString(lpName).AllocSysString();
		hr=pNode->selectNodes(wstr,&ilst);
		SysFreeString(wstr);
		if(FAILED(hr)) return 0;
	}
	else
	{
		hr=pNode->get_childNodes(&ilst);
		if(FAILED(hr)) return 0;
	}

	long len;
	hr=ilst->get_length(&len);
	ilst->Release();

	return ((FAILED(hr))?0:len);
}

BOOL CXMLDOMInterface::GetNodeAttribute(IXMLDOMNode *pNode, LPCSTR lpName, CString &val)
{
	if(pNode==NULL) {val.Empty();return false;}
	IXMLDOMNamedNodeMap* innm;
	HRESULT hr;
	hr=pNode->get_attributes(&innm);
	if(FAILED(hr) || innm== NULL) 
	{
		val.Empty();
		return false;
	}

	IXMLDOMNode* iNode;
	BSTR wstr=CString(lpName).AllocSysString();
	hr=innm->getNamedItem(wstr,&iNode);
	SysFreeString(wstr);
	if(FAILED(hr)||iNode==NULL) {innm->Release();val.Empty();return false;}
	hr=iNode->get_text(&wstr);
	iNode->Release();innm->Release();
	if(FAILED(hr)) {val.Empty();return false;}
	val=CString(wstr);
	SysFreeString(wstr);
	return true;
}

BOOL CXMLDOMInterface::GetNodeAttribute(IXMLDOMNode *pNode, long index, CString &val)
{
	if(pNode==NULL) {val.Empty();return false;}
	IXMLDOMNamedNodeMap* innm;
	HRESULT hr;
	hr=pNode->get_attributes(&innm);
	if(FAILED(hr)) {val.Empty();return false;}
	IXMLDOMNode* iNode;
	hr=innm->get_item(index,&iNode);
	if(FAILED(hr)||iNode==NULL) {innm->Release();val.Empty();return false;}

	BSTR wstr;

	hr=iNode->get_text(&wstr);
	iNode->Release();innm->Release();
	if(FAILED(hr)) return false;
	val=CString(wstr);
	SysFreeString(wstr);
	return true;
}

BOOL CXMLDOMInterface::GetNodeAttribute(IXMLDOMNode *pNode, long index, CString& Name, CString &val)
{
	if(pNode==NULL) {Name.Empty();val.Empty();return false;}
	IXMLDOMNamedNodeMap* innm;
	HRESULT hr;
	hr=pNode->get_attributes(&innm);
	if(FAILED(hr)||innm==NULL) {Name.Empty();val.Empty();return false;}
	IXMLDOMNode* iNode;
	hr=innm->get_item(index,&iNode);
	if(FAILED(hr)||iNode==NULL) {innm->Release();Name.Empty();val.Empty();return false;}

	BSTR wstr;

	hr=iNode->get_nodeName(&wstr);
	if(FAILED(hr)) {iNode->Release();innm->Release();Name.Empty();val.Empty();return false;}
	Name=CString(wstr);
	SysFreeString(wstr);

	hr=iNode->get_text(&wstr);
	iNode->Release();innm->Release();
	if(FAILED(hr)) {Name.Empty();val.Empty();return false;}
	val=CString(wstr);
	SysFreeString(wstr);
	return true;
}

long CXMLDOMInterface::GetNodeAttributesCount(IXMLDOMNode *pNode)
{
	if(pNode==NULL) return 0;
	HRESULT hr;
	long len;
	IXMLDOMNamedNodeMap* pMap;
	hr=pNode->get_attributes(&pMap);
	if(FAILED(hr)) return 0;
	hr=pMap->get_length(&len);
	pMap->Release();
	if(FAILED(hr)) return 0;
	return len;
}

BOOL CXMLDOMInterface::GetNodeName(IXMLDOMNode* pNode, CString &val)
{
	if(pNode==NULL) {val.Empty();return false;}
	BSTR wstr;
	HRESULT hr;
	hr=pNode->get_nodeName(&wstr);
	if(FAILED(hr)) {val.Empty();return false;}
	val=CString(wstr);
	SysFreeString(wstr);
	return true;
}

BOOL CXMLDOMInterface::GetNodeText(IXMLDOMNode *pNode, CString& val)
{
	if(pNode==NULL) {val.Empty();return false;}
	BSTR wstr;
	HRESULT hr;
	hr=pNode->get_text(&wstr);
	if(FAILED(hr)) {val.Empty();return false;}
	val=CString(wstr);
	SysFreeString(wstr);
	return true;
}

void CXMLDOMInterface::Find_Initialize(LPCTSTR lpNodeName)
{
	//by lyj 20040810
	m_rst.pList = NULL;
	//by lyj 20040810
	m_FindMutex.Lock();m_cond.nCount=0;
	m_cond.tagname=CString(lpNodeName).AllocSysString();
}

void CXMLDOMInterface::Find_AddFilter(LPCTSTR lpAttName, LPCTSTR lpVal)
{
	m_cond.pHead[m_cond.nCount].strAttName=CString(lpAttName).AllocSysString();
	m_cond.pHead[m_cond.nCount].strAttValue=CString(lpVal).AllocSysString();
	m_cond.nCount++;
}

BOOL CXMLDOMInterface::FindFirst(IXMLDOMElement *pele, IXMLDOMNode **lplpNode)
{
	if(pele==NULL) return false;
	IXMLDOMNodeList* pns=NULL;
	IXMLDOMNode* pn;
	IXMLDOMNode* pni;
	IXMLDOMNamedNodeMap* pnnm;
	VARIANT var;
	HRESULT hr;
	hr=pele->getElementsByTagName(m_cond.tagname,&pns);
	if(FAILED(hr)||pns==NULL) return false;
	BOOL isadd;
	LONG len,i,j;
	hr=pns->get_length(&len);
	if(FAILED(hr)||len==0) 
		{pns->Release();return false;}
	m_rst.nIndex=NULL;
	m_rst.nCount=0;
	m_rst.pList=pns;
	for(i=0;i<len;i++)
	{
		hr=pns->get_item(i,&pn);
		if(FAILED(hr)) continue;
		hr=pn->get_attributes(&pnnm);
		//by lyj 20040810
		if(FAILED(hr)) 
		{
			pn->Release();
			continue;
		}
		//by lyj 20040810
		isadd=true;
		for(j=0;j<m_cond.nCount;j++)
		{//check for attribute
			hr=pnnm->getNamedItem(m_cond.pHead[j].strAttName,&pni);
			
			if(FAILED(hr)||pni==NULL) 
			{isadd=false;goto QUIT;}
			hr=pni->get_nodeValue(&var);
			//by lyj 20040810
			if(FAILED(hr)||pni==NULL)
			{
				isadd=false;
				pni->Release();
				goto QUIT;
			}
			pni->Release();
			//by lyj 20040810
			if(wstrcmp(var.bstrVal,m_cond.pHead[j].strAttValue)!=0) isadd=false;
		}//check for attribute
QUIT:
		//by lyj 20040810
		pn->Release();
		//by lyj 20040810
		pnnm->Release();
		if(!isadd) continue;
		m_rst.index[m_rst.nCount++]=i;
		//by lyj 20040810
		if(m_rst.nCount>=100) 
		{
			pns->Release();
			m_rst.pList = NULL;
			return false;
		}
		//by lyj 20040810
	}

	if(m_rst.nCount<=0) return false;
	hr=m_rst.pList->get_item(m_rst.index[0],lplpNode);
	return (SUCCEEDED(hr)&&(*lplpNode!=NULL));
}

BOOL CXMLDOMInterface::FindNext(IXMLDOMNode **lplpNode)
{
	m_rst.nIndex++;
	HRESULT hr;
	//by lyj 20040810
	if(m_rst.pList != NULL)
		hr=m_rst.pList->get_item(m_rst.nIndex,lplpNode);
	//by lyj 20040810
	return (SUCCEEDED(hr)&&(*lplpNode!=NULL));
}

void CXMLDOMInterface::Find_Finished()
{
	m_FindMutex.Unlock();
	if(m_rst.pList != NULL)
		m_rst.pList->Release();
	SysFreeString(m_cond.tagname);
	for(int i=0;i<m_cond.nCount;i++)
	{
		SysFreeString(m_cond.pHead[i].strAttName);
		SysFreeString(m_cond.pHead[i].strAttValue);
	}
}

void CXMLDOMInterface::TransToXML(LPCTSTR lpsrc, CString &val)
{
/*	val=lpsrc;
	val.Replace(_T("&"),	_T("&amp;")	);
	val.Replace(_T("\""),	_T("&quot;"));
	val.Replace(_T("<"),	_T("&lt;")	);
	val.Replace(_T(">"),	_T("&gt;")	);
	val.Replace(_T("\'"),	_T("&apos;"));
*/
//	基于效率的考虑，采用以下方式；虽然串在不长的情况下影响不大，
//  当串很长，且在极端情况(全部由上述字符组成)下，效率的改变是可观的；
	val = TransToXML( CString(lpsrc) );
}
CString CXMLDOMInterface::TransToXML(const CString  lpsrc)
{
	typedef struct _REPLACE{
		TCHAR src;
		TCHAR *des;
		int desLength;
	}REPLACE;
	static REPLACE RepArray[]={
		{_T('&'),	_T("&amp;"),	5},
		{_T('<'),	_T("&lt;"),		4},
		{_T('>'),	_T("&gt;"),		4},
		{_T('\''),	_T("&apos;"),	6},
		{_T('\"'),	_T("&quot;"),	6},
		{0,0,0}
	};
	TCHAR *tmp = const_cast<TCHAR *>((LPCTSTR)lpsrc);
	int oldlen = lpsrc.GetLength(); //_tcslen(lpsrc);
	int newlen = 0;
	for(; *tmp != NULL; tmp ++){
		for(int i = 0 ; RepArray[i].src != 0 && *tmp != RepArray[i].src ; i++)	// *tmp need be replaced?
			;
		if(RepArray[i].src != 0 )	newlen += RepArray[i].desLength;
	}
	if(newlen == 0) 
		return lpsrc;

	newlen += oldlen;
	TCHAR *result = new TCHAR[newlen + 1];
	TCHAR *des = result;
	tmp = const_cast<TCHAR *>((LPCTSTR)lpsrc);
	for(; *tmp; tmp++){
		for(int i = 0 ; RepArray[i].src != 0 && *tmp != RepArray[i].src ; i++)
			;
		if(RepArray[i].src != 0){												// *tmp need be replaced;
			_tcscpy(des,RepArray[i].des);
			des += RepArray[i].desLength;
		}else{																	// *tmp is common char ;
			*des = *tmp;
			des++;
		}
	}
	*des = _T('\0');
	CString retStr(result);
	delete []result;
	return retStr;
}

BOOL CXMLDOMInterface::LoadXMLString(LPCTSTR lpXML, IXMLDOMElement** lplpRoot,int judge)
{	
	HRESULT hr= S_OK;

	if (!m_pdoc)
	{
		hr=CoCreateInstance(CLSID_DOMDocument,NULL,
			CLSCTX_INPROC_SERVER,IID_IXMLDOMDocument,(void**)&m_pdoc);
		if(FAILED(hr)||m_pdoc==NULL)
		{
			m_pdoc= NULL;
			return false;
		}
	}

	DWORD len=strlen(lpXML);
	VARIANT_BOOL btmp;
	BSTR wstr=CString(lpXML).AllocSysString();
	if(wstr==NULL) {m_pdoc->Release();return false;}
	hr=m_pdoc->loadXML(wstr,&btmp);
	SysFreeString(wstr);
	if(FAILED(hr)||btmp==VARIANT_FALSE) 
	{
		return false;
	}

	hr=m_pdoc->get_documentElement(lplpRoot);

	if(FAILED(hr)||*lplpRoot==NULL)
	{
		return false;
	}

	return true;
}

BOOL CXMLDOMInterface::SetNodeText(IXMLDOMNode *pNode, CString val)
{
	BSTR bval=val.AllocSysString();
	HRESULT hr=pNode->put_text(bval); 
	::SysFreeString(bval); 
	return SUCCEEDED(hr);
}

BOOL CXMLDOMInterface::SaveToString(CString &Val)
{
	BSTR temp;
	HRESULT hr=m_pdoc->get_xml(&temp);
	Val=CString(temp);
	::SysFreeString(temp);
	return(SUCCEEDED(hr));
}

int CXMLDOMInterface::CloneNode(IXMLDOMNode *pNode1,IXMLDOMNode **pNode2)
{
	HRESULT hr=pNode1->cloneNode(-1,pNode2);
	
	return SUCCEEDED(hr);
}

int CXMLDOMInterface::AppendChild(IXMLDOMNode *MainNode,IXMLDOMNode *&pNode2)
{
	IXMLDOMNode *pNode1=NULL;
	HRESULT hr=MainNode->appendChild(pNode2,&pNode1);
	pNode2->Release();
	pNode2=pNode1;
	return SUCCEEDED(hr);
}

int CXMLDOMInterface::RemoveChild(IXMLDOMNode *MainNode,IXMLDOMNode * &pNode1)
{
	IXMLDOMNode *pNode2=NULL;
	HRESULT hr=MainNode->removeChild(pNode1,&pNode2);
    pNode1->Release();
	pNode1=pNode2;
	return SUCCEEDED(hr);
}

int CXMLDOMInterface::SetNodeAttribute(IXMLDOMNode *pNode, CString Name, CString val)
{
	if(pNode==NULL) {return false;}
	IXMLDOMNamedNodeMap* innm;
	HRESULT hr;
	hr=pNode->get_attributes(&innm);
	if(FAILED(hr)) {return false;}
	IXMLDOMNode* iNode;
	BSTR wstr=Name.AllocSysString();
	hr=innm->getNamedItem(wstr,&iNode);
	SysFreeString(wstr);
	if(FAILED(hr)||iNode==NULL) {innm->Release();val.Empty();return false;}
	wstr=val.AllocSysString(); 
	hr=iNode->put_text(wstr);
	SysFreeString(wstr);
	iNode->Release();innm->Release();
	return SUCCEEDED(hr);

}

//把一个布尔型值保存到XML字符串中
void CXMLDOMInterface::BoolPropertyToXMLString(CString &strVal,LPCSTR szPropertyName, BOOL bProperty)
{
	CString strTemp;
	strTemp=(bProperty)?"TRUE":"FALSE";
	strVal+=CString(" ")+szPropertyName+"=\""+strTemp+"\"";

	return;
}

//把一个布尔型值保存到XML字符串中
void CXMLDOMInterface::StringPropertyToXMLString(CString &strVal,LPCSTR szPropertyName, LPCSTR szProperty)
{
	strVal+=CString(" ")+szPropertyName+"=\""+
		TranslateToXMLString(szProperty)+"\"";
	return;
}


//把一个整型值保存到XML字符串中
void CXMLDOMInterface::IntPropertyToXMLString(CString &strVal,LPCSTR szPropertyName, int nProperty)
{
	CString strTemp;
	strTemp.Format("%d", nProperty );
	strVal+=CString(" ")+szPropertyName+"=\""+strTemp+"\"";
	return;
}

CString CXMLDOMInterface::TranslateToXMLString(const CString &val)
{
	CString strRet= val;

	strRet.Replace("&","&amp;");
	strRet.Replace("\"","&quot;");//&quot;
	strRet.Replace("<","&lt;");
	strRet.Replace(">","&gt;");
	strRet.Replace("'","&apos;");

	return strRet;
}

CString CXMLDOMInterface::ChangeFormatToHtml(const CString &val)
{
	CString strRet= val;

	strRet.Replace(" ","&nbsp;");
	strRet.Replace("\r\n","<br>");
	strRet.Replace("\r","<br>");
	strRet.Replace("\n","<br>");
	strRet.Replace("\t","&nbsp;&nbsp;&nbsp;");

	return strRet;
}

CString CXMLDOMInterface::ChangeHtmltoFormat(const CString &val)
{
	CString strRet= val;

	strRet.Replace("&nbsp;"," ");
	strRet.Replace("<br>","\r\n");

	return strRet;
}

}