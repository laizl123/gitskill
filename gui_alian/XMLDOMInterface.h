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
	//BOOL LoadXMLString(LPCTSTR lpXML,IXMLDOMElement** pRoot);//���ַ�����װ��XML�ĵ�
	BOOL OpenXMLFile(LPCTSTR lpName,IXMLDOMElement** pRoot);//��XML�ļ�
	CXMLDOMInterface();
	virtual ~CXMLDOMInterface();
	BOOL Use_Enable(){return m_bInitialized;}//�ж��Ƿ��ʼ���ɹ�
	IXMLDOMDocument * GetXMLDOMDoc(){return m_pdoc;}//����ĵ�����
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

	static void	   TransToXML(LPCTSTR lpsrc, CString &val);		// �����е�ĳЩ�ַ�ת���� XML ��ʽ��
	static CString TransToXML(const CString  str);

	//mengji���޸�
	int SetNodeAttribute(IXMLDOMNode *pNode, CString Name, CString val);
	//construction/destruction functions
	int RemoveChild(IXMLDOMNode *MainNode,IXMLDOMNode * &pNode1);
	int AppendChild(IXMLDOMNode *MainNode,IXMLDOMNode *&pNode2);
	int CloneNode(IXMLDOMNode *pNode1,IXMLDOMNode **pNode2);
	BOOL SaveToString(CString &Val);
	BOOL SetNodeText(IXMLDOMNode *pNode,CString val);
	BOOL LoadXMLString(LPCTSTR lpXML,IXMLDOMElement** lplpRoot,int judge=0);//���ַ�����װ��XML�ĵ�

//�������ӣ����������ַ�����xml����ĺ���
	///�Ѹ�ʽת��Ϊhtml
	static CString ChangeFormatToHtml(const CString &val);
	///��html��ԭ
	static CString ChangeHtmltoFormat(const CString &val);
	///���xml�ı����ַ����滻
	static CString TranslateToXMLString(const CString &val);

	//��һ��������ֵ���浽XML�ַ�����
	static void BoolPropertyToXMLString(CString &strVal,LPCSTR szPropertyName, BOOL bProperty);
	
	//��һ��������ֵ���浽XML�ַ�����
	static void StringPropertyToXMLString(CString &strVal,LPCSTR szPropertyName, LPCSTR szProperty);

	static inline BOOL StringToBool(const CString& strBool){
		return (strBool.Compare("TRUE"))?FALSE:TRUE;
	};

	//��һ������ֵ���浽XML�ַ�����
	static void IntPropertyToXMLString(CString &strVal,LPCSTR szPropertyName, int nProperty);
//�������ӽ���

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
