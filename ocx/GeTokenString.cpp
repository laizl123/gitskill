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
	nLen++; //结尾字符
	
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

//开始
void CGeTokenString::Begin()
{
	m_Pos= m_pStr;
}

//下一个
string CGeTokenString::GetNext()
{
	TCHAR* posBegin=m_Pos;

	while(!IsEnd())
	{
		if (m_Splits.find(*m_Pos) != m_Splits.end())
		{//在集合中
			break;
		}
		m_Pos++;
	}
	
	string str(posBegin,m_Pos);
	
	m_Pos++; //越过符号

	return str;
}

/**返回当前位置剩余的, 不包括前导的分割符.
如: xxx,a,b；,为分割符，当前已经析取了xxx，调用此方法将返回a,b
*/
string CGeTokenString::GetRest()
{
	TCHAR* posBegin=m_Pos;
	string str= posBegin;

	return str;
}

//是否迭代结束
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

	strToken= "a;b;c;d;e;fffff;gggg;趁镇;a,adf";
	strToken.SetTokenSplit(";,");
	test_output(strToken);

	strToken= "a;b;c;d;e;fffff;gggg;趁镇;a,adf";
	TRACE("开始提取：%s\n",strToken.m_pStr);
	strToken.SetTokenSplit(";");
	strToken.Begin();
	//test_output(strToken);
	strToken.GetNext();
	strToken.GetNext();
	string strRet= strToken.GetRest();
	TRACE("剩余部分          %s\n",strRet.c_str());
	
	CString cstrToken = "a;b；c;d;e;fff；ff;gggg;趁镇；a,adf；";
	CStringArray result;
	int count;
	CGeTokenString::Split(cstrToken,"；",result);
	count = result.GetSize();
	TRACE("子串数目：%d\n",count);
	for(int i=0;i<count;i++)
	{
		TRACE("%s\n",result.ElementAt(i));
	}

}

void CGeTokenString::test_output(CGeTokenString& strToken)
{
	TRACE("开始解析：%s\n",strToken.m_pStr);
	for(strToken.Begin(); !strToken.IsEnd(); )
	{
		CString strRet= strToken.GetNext().c_str();
		TRACE("          %s\n",strRet);
	}
}
#endif

}
//说明：有n个分割符，则分割成n+1个子串，如"a;b;"则分割成3个串"a","b"和""
//子串中可能含有该分隔符的替换符号，再分隔出子串时自动用该分隔符替换回来(自动复原)
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
