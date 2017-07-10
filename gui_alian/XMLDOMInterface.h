#ifndef _DOM_XML_INTERFACE_H_
#define _DOM_XML_INTERFACE_H_
#include <msxml.h>
#include <comdef.h>
#include <afxmt.h>
//Additional,you must link to "msxml3.lib".

namespace ibXML{

typedef struct _FindNode
{
	BSTR strAttName;
	BSTR strAttValue;
}FindNode;

typedef struct _FindCondition
{
	BSTR tagname;
	FindNode pHead[50];
	int nCount;
}FindCondition;

typedef struct _FindResult
{
	IXMLDOMNodeList *pList;
	int index[100];
	int nCount;
	int nIndex;
}FindResult;

class CXMLDOMInterface  
{
public:
	//construction/destruction functions
	//BOOL LoadXMLString(LPCTSTR lpXML,IXMLDOMElement** pRoot);//从字符串中装载XML文档
	BOOL OpenXMLFile(LPCTSTR lpName,IXMLDOMElement** pRoot);//打开XML文件
	CXMLDOMInterface();
	virtual ~CXMLDOMInterface();
	BOOL Use_Enable(){return m_bInitialized;}//判断是否初始化成功
	IXMLDOMDocument * GetXMLDOMDoc(){return m_pdoc;}//获得文档对象
	//construction/destruction functions

	//Find Function
	void Find_Finished();
	BOOL FindNext(IXMLDOMNode **lplpNode);
	BOOL FindFirst(IXMLDOMElement* pele,IXMLDOMNode** lplpNode);
	void Find_AddFilter(LPCTSTR lpAttName, LPCTSTR lpVal);
	void Find_Initialize(LPCTSTR lpNodeName);
	//Find Function

	static BOOL GetNodeText(IXMLDOMNode* pNode,CString& val);
	static BOOL GetNodeName(IXMLDOMNode* pNode,CString& val);

	//Node Attribute function
	static BOOL GetNodeAttribute(IXMLDOMNode* pNode,long index,CString& val);
	static BOOL GetNodeAttribute(IXMLDOMNode* pNode,LPCSTR lpName,CString& val);
	static BOOL GetNodeAttribute(IXMLDOMNode* pNode,long index,CString& Name,CString& val);
	static long GetNodeAttributesCount(IXMLDOMNode* pNode);
	//Node Attribute function

	//children nodes function
	static long GetChildrenCount(IXMLDOMNode* pNode, LPCTSTR lpName=NULL);
	static BOOL GetChildNode(IXMLDOMNode *pNode, IXMLDOMNode **lplpNode, LPCTSTR lpName=NULL, long index=0);
	static BOOL GetChildrenNodes(IXMLDOMNode *pNode,IXMLDOMNodeList** lplpLst,LPCTSTR lpName=NULL);
	//children nodes function

	static void	   TransToXML(LPCTSTR lpsrc, CString &val);		// 将串中的某些字符转换成 XML 格式；
	static CString TransToXML(const CString  str);

	//mengji的修改
	int SetNodeAttribute(IXMLDOMNode *pNode, CString Name, CString val);
	//construction/destruction functions
	int RemoveChild(IXMLDOMNode *MainNode,IXMLDOMNode * &pNode1);
	int AppendChild(IXMLDOMNode *MainNode,IXMLDOMNode *&pNode2);
	int CloneNode(IXMLDOMNode *pNode1,IXMLDOMNode **pNode2);
	BOOL SaveToString(CString &Val);
	BOOL SetNodeText(IXMLDOMNode *pNode,CString val);
	BOOL LoadXMLString(LPCTSTR lpXML,IXMLDOMElement** lplpRoot,int judge=0);//从字符串中装载XML文档

//陈震增加，辅助处理字符串的xml输出的函数
	///把格式转换为html
	static CString ChangeFormatToHtml(const CString &val);
	///从html还原
	static CString ChangeHtmltoFormat(const CString &val);
	///针对xml的保留字符做替换
	static CString TranslateToXMLString(const CString &val);

	//把一个布尔型值保存到XML字符串中
	static void BoolPropertyToXMLString(CString &strVal,LPCSTR szPropertyName, BOOL bProperty);
	
	//把一个布尔型值保存到XML字符串中
	static void StringPropertyToXMLString(CString &strVal,LPCSTR szPropertyName, LPCSTR szProperty);

	static inline BOOL StringToBool(const CString& strBool){
		return (strBool.Compare("TRUE"))?FALSE:TRUE;
	};

	//把一个整型值保存到XML字符串中
	static void IntPropertyToXMLString(CString &strVal,LPCSTR szPropertyName, int nProperty);
//陈震增加结束

private:
	BOOL m_bInitialized;
	IXMLDOMDocument * m_pdoc;
	FindCondition m_cond;
	FindResult m_rst;
	CMutex m_FindMutex;
	CMutex m_OpenMutex;
};

};

using namespace ibXML;

#endif
