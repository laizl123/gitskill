////////////////////////////////////////////////////////////////////////////
//FileName: GeTokenString.cpp
//Write by: chenzhen 
//Time: 2002-9-13 14:43:12
///////////////////////////////////////////////////////////////////////////

// GeTokenString.cpp: implementation of the CGeTokenString class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GeTokenString.h"

#ifdef _AFXDLL
	#ifdef _DEBUG
	#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
	#define new DEBUG_NEW
	#endif
#endif

namespace Basis{

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CGeTokenString::~CGeTokenString()
{
	delete m_pStr;
}

CGeTokenString& CGeTokenString::operator= (LPCSTR szTokenString)
{
	if (m_pStr != NULL)
		delete m_pStr;

	int nLen= 0;
	if (szTokenString)
	{
		nLen= strlen(szTokenString);
	}
	nLen++; //��β�ַ�
	
	m_pStr= new TCHAR[nLen];
	if (szTokenString)
		strcpy(m_pStr,szTokenString);
	else
	{
		m_pStr[0]= NULL;
	}

	Begin();

	return *this;
}

//��ʼ
void CGeTokenString::Begin()
{
	m_Pos= m_pStr;
}

//��һ��
string CGeTokenString::GetNext()
{
	TCHAR* posBegin=m_Pos;

	while(!IsEnd())
	{
		if (m_Splits.find(*m_Pos) != m_Splits.end())
		{//�ڼ�����
			break;
		}
		m_Pos++;
	}
	
	string str(posBegin,m_Pos);
	
	m_Pos++; //Խ������

	return str;
}

/**���ص�ǰλ��ʣ���, ������ǰ���ķָ��.
��: xxx,a,b��,Ϊ�ָ������ǰ�Ѿ���ȡ��xxx�����ô˷���������a,b
*/
string CGeTokenString::GetRest()
{
	TCHAR* posBegin=m_Pos;
	string str= posBegin;

	return str;
}

//�Ƿ��������
bool CGeTokenString::IsEnd()
{
	return m_Pos>= m_pStr+ strlen(m_pStr);
}

#ifdef _TEST
void CGeTokenString::test_Case()
{
	CGeTokenString strToken;

	strToken= "";
	test_output(strToken);
	
	strToken= "afdk;asdf";
	test_output(strToken);

	strToken= "adfsasdf,adsfa";
	strToken.SetTokenSplit(',');
	test_output(strToken);
	
	strToken= "adsf;ads;adfskkkk,asdf;dkkkk";
	test_output(strToken);

	strToken= "adsf;ads;ad;;;fskkkk,asdf;dkkkk;;";
	strToken.SetTokenSplit(';');
	test_output(strToken);

	strToken= "adsf;ads;ad;;;fskkkk,asdf;;;;";
	strToken.SetTokenSplit(';');
	test_output(strToken);
	//TRACE("end");

	strToken= "a;b;c;d;e;fffff;gggg;����;a,adf";
	strToken.SetTokenSplit(";,");
	test_output(strToken);

	strToken= "a;b;c;d;e;fffff;gggg;����;a,adf";
	TRACE("��ʼ��ȡ��%s\n",strToken.m_pStr);
	strToken.SetTokenSplit(";");
	strToken.Begin();
	//test_output(strToken);
	strToken.GetNext();
	strToken.GetNext();
	string strRet= strToken.GetRest();
	TRACE("ʣ�ಿ��          %s\n",strRet.c_str());
	
	CString cstrToken = "a;b��c;d;e;fff��ff;gggg;����a,adf��";
	CStringArray result;
	int count;
	CGeTokenString::Split(cstrToken,"��",result);
	count = result.GetSize();
	TRACE("�Ӵ���Ŀ��%d\n",count);
	for(int i=0;i<count;i++)
	{
		TRACE("%s\n",result.ElementAt(i));
	}

}

void CGeTokenString::test_output(CGeTokenString& strToken)
{
	TRACE("��ʼ������%s\n",strToken.m_pStr);
	for(strToken.Begin(); !strToken.IsEnd(); )
	{
		CString strRet= strToken.GetNext().c_str();
		TRACE("          %s\n",strRet);
	}
}
#endif

}
//˵������n���ָ������ָ��n+1���Ӵ�����"a;b;"��ָ��3����"a","b"��""
//�Ӵ��п��ܺ��и÷ָ������滻���ţ��ٷָ����Ӵ�ʱ�Զ��ø÷ָ����滻����(�Զ���ԭ)
bool Basis::CGeTokenString::Split(const CString & src, CString splitChar, CStringArray& arrResult)
{
	arrResult.RemoveAll();
	if(src.IsEmpty())
	{
		return false;
	}

	if(splitChar.IsEmpty()) 
	{
		return false;
	}

	char ch,ch1;
	int length = src.GetLength();
	int spos=0,epos=0;
	CString  sSubstr;
	for(int i=0;i<length;i++)
	{
		epos = i;
		ch = src[i];
		if(splitChar[0]<0)
		{
			if(i+1<length) 
			{
				ch1 = src[i+1];
				if(ch == splitChar[0] && ch1 == splitChar[1])
				{
					sSubstr = src.Mid(spos,epos-spos);
					sSubstr = RecoverSplitChar(sSubstr,splitChar[0]);
					arrResult.Add(sSubstr);
					spos = epos + 2;
					i++;
				}
			}
		}
		else
		{
			if(ch == splitChar)
			{
				sSubstr = src.Mid(spos,epos-spos);
				sSubstr = RecoverSplitChar(sSubstr,splitChar[0]);
				arrResult.Add(sSubstr);
				spos = epos + 1;
			}
		}
	}
	if(src[epos]!=splitChar[0])
	{
		sSubstr = src.Right(length-spos);
		sSubstr = RecoverSplitChar(sSubstr,splitChar[0]);
		arrResult.Add(sSubstr);
	}
	else
	{
		arrResult.Add("");
	}
	return true;
}

CString CGeTokenString::ReplaceBySplitChar(CString sSrc, char splitChar)
{
	CString repStr;
	if(splitChar == '|')
		repStr = "##1";
	else if(splitChar == ';')
		repStr = "##2";
	else if(splitChar == ',')
		repStr = "##3";
	else if(splitChar == ':')
		repStr = "##4";
	else
		return sSrc;
	CString oldStr(splitChar);
	sSrc.Replace(oldStr,repStr);
	return sSrc;
}

CString CGeTokenString::RecoverSplitChar(CString sSrc, char splitChar)
{
	CString repStr;
	if(splitChar == '|')
		repStr = "##1";
	else if(splitChar == ';')
		repStr = "##2";
	else if(splitChar == ',')
		repStr = "##3";
	else if(splitChar == ':')
		repStr = "##4";
	else
		return sSrc;
	CString newStr(splitChar);
	sSrc.Replace(repStr,newStr);
	return sSrc;
}
