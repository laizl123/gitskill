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

/*修改历史
1, 2003-3-14: 在几天前增加方法GetRest
2, 2003-3-14: 在赋值和构造函数增加Begin的调用, 避免忘记调用Begin时出错的隐患.
3, 2004-2-4:增加两个方法，支持内定分隔符与替换符之间的转换
	方法是：ReplaceBySplitChar() 和 RecoverSplitChar()
*/

namespace Basis{

/**根据token(切分符)切分字符串的操作类
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
		m_pStr= NULL;//delete null 是合法
		operator= (szTokenString);
	};
	CGeTokenString(const CGeTokenString& rhs){
		m_pStr= NULL;//delete null 是合法
		operator= (rhs);
	};
	CGeTokenString& operator= (LPCSTR szTokenString);
	inline CGeTokenString& operator= (const CGeTokenString& rhs){
		*this= rhs.m_pStr;
		m_Splits= rhs.m_Splits;
	};

	virtual ~CGeTokenString();

public:
	/**设置分割符
	*/
	void SetTokenSplit(TCHAR ch){
		m_Splits.clear();
		m_Splits.insert(ch);
	};
	/**设置分割符
	*/
	void SetTokenSplit(LPCSTR szTokens){
		m_Splits.clear();
		size_t nLen= strlen(szTokens);
		m_Splits.insert(szTokens,szTokens+nLen);
	};

	/**开始
	*/
	void Begin();
	
	/**下一个
	*/
	string GetNext();

	/**返回当前位置剩余的, 不包括前导的分割符.
	如: xxx,a,b；,为分割符，当前已经析取了xxx，调用此方法将返回a,b
	*/
	string GetRest();

	/**是否迭代结束
	*/
	bool IsEnd();

#ifdef _TEST
	static void test_Case();
	static void test_output(CGeTokenString& strToken);
#endif

private:
	TCHAR* m_Pos;//当前位置
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
