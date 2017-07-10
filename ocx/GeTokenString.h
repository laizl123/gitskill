// GeTokenString.h: interface for the CGeTokenString class.
//


#if !defined(AFX_GETOKENSTRING_H__1B27503F_B3AD_4B0C_88FD_E2760E196248__INCLUDED_)
#define AFX_GETOKENSTRING_H__1B27503F_B3AD_4B0C_88FD_E2760E196248__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <set>
#include <string>
using namespace std;

/*�޸���ʷ
1, 2003-3-14: �ڼ���ǰ���ӷ���GetRest
2, 2003-3-14: �ڸ�ֵ�͹��캯������Begin�ĵ���, �������ǵ���Beginʱ���������.
3, 2004-2-4:��������������֧���ڶ��ָ������滻��֮���ת��
	�����ǣ�ReplaceBySplitChar() �� RecoverSplitChar()
*/

namespace Basis{

/**����token(�зַ�)�з��ַ����Ĳ�����
*/
class CGeTokenString  
{
public:
	CGeTokenString(){
		SetTokenSplit(';');
		m_pStr= new TCHAR[1];
		m_pStr[0]= 0;
		m_Pos= m_pStr;
	};
	CGeTokenString(LPCSTR szTokenString){
		SetTokenSplit(';');
		m_pStr= NULL;//delete null �ǺϷ�
		operator= (szTokenString);
	};
	CGeTokenString(const CGeTokenString& rhs){
		m_pStr= NULL;//delete null �ǺϷ�
		operator= (rhs);
	};
	CGeTokenString& operator= (LPCSTR szTokenString);
	inline CGeTokenString& operator= (const CGeTokenString& rhs){
		*this= rhs.m_pStr;
		m_Splits= rhs.m_Splits;
	};

	virtual ~CGeTokenString();

public:
	/**���÷ָ��
	*/
	void SetTokenSplit(TCHAR ch){
		m_Splits.clear();
		m_Splits.insert(ch);
	};
	/**���÷ָ��
	*/
	void SetTokenSplit(LPCSTR szTokens){
		m_Splits.clear();
		size_t nLen= strlen(szTokens);
		m_Splits.insert(szTokens,szTokens+nLen);
	};

	/**��ʼ
	*/
	void Begin();
	
	/**��һ��
	*/
	string GetNext();

	/**���ص�ǰλ��ʣ���, ������ǰ���ķָ��.
	��: xxx,a,b��,Ϊ�ָ������ǰ�Ѿ���ȡ��xxx�����ô˷���������a,b
	*/
	string GetRest();

	/**�Ƿ��������
	*/
	bool IsEnd();

#ifdef _TEST
	static void test_Case();
	static void test_output(CGeTokenString& strToken);
#endif

private:
	TCHAR* m_Pos;//��ǰλ��
	LPSTR m_pStr;
	set<TCHAR> m_Splits;
public:
	static CString RecoverSplitChar(CString sSrc,char splitChar);
	static CString ReplaceBySplitChar(CString sSrc,char splitChar);
	// const CString &src,TCHAR splitChar ,CString* result, int *num
	static bool Split(const CString & src, CString splitChar, CStringArray& arrResult);
};
}

using namespace Basis;

#endif // !defined(AFX_GETOKENSTRING_H__1B27503F_B3AD_4B0C_88FD_E2760E196248__INCLUDED_)
