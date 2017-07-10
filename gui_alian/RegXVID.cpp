// RegXVID.cpp: implementation of the CRegXVID class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RegXVID.h"
#include "shlwapi.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRegXVID::CRegXVID()
{

}

CRegXVID::~CRegXVID()
{

}

bool CRegXVID::DisplayXVIDStatus(bool bShow)
{
	CRegKey key;
	LONG lRes = key.Open(HKEY_CURRENT_USER, _T("Software\\GNU\\XviD"),KEY_READ|KEY_WRITE);

	if (lRes == ERROR_SUCCESS)
	{
		DWORD dValue;
		dValue = (DWORD)bShow;
		key.SetValue(dValue,"display_status");
		dValue = (DWORD)7;
		key.SetValue(dValue,"Supported_4CC");
	}
	else 
	{
		lRes = key.Create(HKEY_CURRENT_USER,_T("Software\\GNU\\XviD"));
		DWORD dValue;
		dValue = (DWORD)bShow;
		key.SetValue(dValue,"display_status");
		dValue = (DWORD)7;
		key.SetValue(dValue,"Supported_4CC");
	}
	key.Close();
	return true;
}

bool CRegXVID::XVIDRegistry()
{
	char winntPath[MAX_PATH];
	memset(winntPath, 0, MAX_PATH);
	::GetWindowsDirectory(winntPath, MAX_PATH);
	CString sWinntPath = winntPath;

/*
Windows Registry Editor Version 5.00

[HKEY_CLASSES_ROOT\CLSID\{00000001-4FEF-40D3-B3FA-E0531B897F98}]
@="XviD MPEG-4 Video DecoderAbout"

[HKEY_CLASSES_ROOT\CLSID\{00000001-4FEF-40D3-B3FA-E0531B897F98}\InprocServer32]
@="C:\\WINNT\\system32\\xvid.ax"
"ThreadingModel"="Both"

//64697678->64697678
[HKEY_CLASSES_ROOT\CLSID\{64697678-0000-0010-8000-00AA00389B71}]
@="XviD MPEG-4 Video Decoder"

[HKEY_CLASSES_ROOT\CLSID\{64697678-0000-0010-8000-00AA00389B71}\InprocServer32]
@="C:\\WINNT\\system32\\xvid.ax"
"ThreadingModel"="Both"

[HKEY_CURRENT_USER\Software\GNU\XviD]
"Supported_4CC"=dword:00000007
"display_status"=dword:00000000


[HKEY_CURRENT_USER\Software\Microsoft\ActiveMovie\devenum\{33D9A760-90C8-11D0-BD43-00A0C911CE86}\xvid]
"FriendlyName"="XviD MPEG-4 Codec"
"CLSID"="{D76E2820-1563-11CF-AC98-00AA004C0FA9}"
"FilterData"=hex:02,00,00,00,00,00,20,00,02,00,00,00,00,00,00,00,30,70,69,33,\
  00,00,00,00,00,00,00,00,01,00,00,00,00,00,00,00,00,00,00,00,30,74,79,33,00,\
  00,00,00,60,00,00,00,70,00,00,00,31,70,69,33,08,00,00,00,00,00,00,00,01,00,\
  00,00,00,00,00,00,00,00,00,00,30,74,79,33,00,00,00,00,60,00,00,00,80,00,00,\
  00,76,69,64,73,00,00,10,00,80,00,00,aa,00,38,9b,71,00,00,00,00,00,00,00,00,\
  00,00,00,00,00,00,00,00,78,76,69,64,00,00,10,00,80,00,00,aa,00,38,9b,71
"FccHandler"="xvid"
"ClassManagerFlags"=dword:00000000
*/
	CRegKey key;
	LONG lRes = key.Open(HKEY_CLASSES_ROOT, _T("CLSID\\{00000001-4FEF-40D3-B3FA-E0531B897F98}"),KEY_READ|KEY_WRITE);
//	if (lRes != ERROR_SUCCESS) 
	{
		lRes = key.Create(HKEY_CLASSES_ROOT,_T("CLSID\\{00000001-4FEF-40D3-B3FA-E0531B897F98}"));
		lRes = key.SetValue(_T("XviD MPEG-4 Video DecoderAbout"),"");
		
		lRes = key.SetKeyValue("InprocServer32",sWinntPath + "\\system32\\xvid_infobird.ax");
		lRes = key.SetKeyValue("InprocServer32",_T("Both"),"ThreadingModel");		
	}
	key.Close();

	lRes = key.Open(HKEY_CLASSES_ROOT, _T("CLSID\\{64697678-0000-0010-8000-00AA00389B71}"),KEY_READ|KEY_WRITE);
//	if (lRes != ERROR_SUCCESS) 
	{
		lRes = key.Create(HKEY_CLASSES_ROOT,_T("CLSID\\{64697678-0000-0010-8000-00AA00389B71}"));
		lRes = key.SetValue(_T("XviD MPEG-4 Video Decoder"),"");
		
		lRes = key.SetKeyValue("InprocServer32",sWinntPath + "\\system32\\xvid_infobird.ax");
		lRes = key.SetKeyValue("InprocServer32",_T("Both"),"ThreadingModel");		
	}
	key.Close();

	lRes = key.Open(HKEY_CURRENT_USER, _T("Software\\Microsoft\\ActiveMovie\\devenum\\{33D9A760-90C8-11D0-BD43-00A0C911CE86}"),KEY_READ|KEY_WRITE);
//	if (lRes != ERROR_SUCCESS) 
	{
		lRes = key.Create(HKEY_CURRENT_USER,_T("Software\\Microsoft\\ActiveMovie\\devenum\\{33D9A760-90C8-11D0-BD43-00A0C911CE86}"));
		lRes = key.SetKeyValue("xvid","XviD MPEG-4 Codec Infobird","FriendlyName");
		lRes = key.SetKeyValue("xvid",_T("{D76E2820-1563-11CF-AC98-00AA004C0FA9}"),"CLSID");		
		lRes = key.SetKeyValue("xvid",_T("xvid"),"FccHandler");		
		lRes = key.SetKeyValue("xvid",_T("{D76E2820-1563-11CF-AC98-00AA004C0FA9}"),"CLSID");	
		
		CString str = "02,00,00,00,00,00,20,00,02,00,00,00,00,00,00,00,30,70,69,33,"
			"00,00,00,00,00,00,00,00,01,00,00,00,00,00,00,00,00,00,00,00,30,74,79,33,00,"
			"00,00,00,60,00,00,00,70,00,00,00,31,70,69,33,08,00,00,00,00,00,00,00,01,00,"
			"00,00,00,00,00,00,00,00,00,00,30,74,79,33,00,00,00,00,60,00,00,00,80,00,00,"
			"00,76,69,64,73,00,00,10,00,80,00,00,aa,00,38,9b,71,00,00,00,00,00,00,00,00,"
			"00,00,00,00,00,00,00,00,78,76,69,64,00,00,10,00,80,00,00,aa,00,38,9b,71";
		
		str.Replace(",","");
		
		int iLength = str.GetLength()/2;		
		BYTE* lpData = new BYTE[iLength+1];

		BYTE* lptempData = lpData;
		lpData[iLength]=0;
		int nStart =0;
		for(int i=0,j=0; i<str.GetLength(); i++)
		{
			if(i%2 == 0 || i == 0)
				continue;

			CString strTemp = str.Mid(i-1,2);
			int temp;
			sscanf((char*)strTemp.LockBuffer(),"%2X",&temp);
			//lpData[j] = __toascii(temp);
			memcpy((char*)&lpData[j],(char*)&temp,1);
			j++;
			strTemp.UnlockBuffer();
		}
		
		HKEY hKEY;
		long ret0=::RegOpenKeyEx(HKEY_CURRENT_USER,"Software\\Microsoft\\ActiveMovie\\devenum\\{33D9A760-90C8-11D0-BD43-00A0C911CE86}\\xvid",0,KEY_ALL_ACCESS,&hKEY);
		long ret2=::RegSetValueEx(hKEY,"FilterData",NULL,REG_BINARY,lpData,iLength);
		DWORD dword = 0;
		ret2=::RegSetValueEx(hKEY,"ClassManagerFlags",NULL,REG_DWORD,(const unsigned char *)&dword,sizeof(DWORD));
		RegCloseKey(hKEY);
		delete []lptempData; 		
	}
	key.Close();
	
/*
[HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Applets\Regedit]
"View"=hex:2c,00,00,00,02,00,00,00,03,00,00,00,00,83,ff,ff,00,83,ff,ff,ff,ff,\
  ff,ff,ff,ff,ff,ff,cb,00,00,00,96,00,00,00,cb,03,00,00,af,02,00,00,2b,01,00,\
  00,78,00,00,00,78,00,00,00,20,01,00,00,01,00,00,00
"FindFlags"=dword:0000000e
"LastKey"="我的电脑\\HKEY_CURRENT_USER\\Software\\GNU\\XviD"
*/
	lRes = key.Open(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Applets\\Regedit"),KEY_READ|KEY_WRITE);
//	if (lRes != ERROR_SUCCESS) 
	{
		lRes = key.Create(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Applets\\Regedit"));
		
		lRes = key.SetKeyValue("","我的电脑\\HKEY_CURRENT_USER\\Software\\GNU\\XviD","LastKey");
		
		CString str = "2c,00,00,00,02,00,00,00,03,00,00,00,00,83,ff,ff,00,83,ff,ff,ff,ff,"
			"ff,ff,ff,ff,ff,ff,cb,00,00,00,96,00,00,00,cb,03,00,00,af,02,00,00,2b,01,00,"
			"00,78,00,00,00,78,00,00,00,20,01,00,00,01,00,00,00";
		
		str.Replace(",","");
		
		int iLength = str.GetLength()/2;		
		BYTE* lpData = new BYTE[iLength+1];	

		for(int i=0,j=0; i<str.GetLength(); i++)
		{
			if(i%2 == 0 || i == 0)
				continue;
			
			CString strTemp = str.Mid(i-1,2);
			int temp;
			sscanf((char*)strTemp.LockBuffer(),"%2X",&temp);
			//lpData[j] = __toascii(temp);
			memcpy((char*)&lpData[j],(char*)&temp,1);
			j++;
			strTemp.UnlockBuffer();
		}
		
		HKEY hKEY;
		long ret0=::RegOpenKeyEx(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Applets\\Regedit",0,KEY_ALL_ACCESS,&hKEY);
		long ret2=::RegSetValueEx(hKEY,"View",NULL,REG_BINARY,lpData,iLength);
		DWORD dword = 0x0000000e;
		ret2=::RegSetValueEx(hKEY,"FindFlags",NULL,REG_DWORD,(const unsigned char *)&dword,sizeof(DWORD));
		RegCloseKey(hKEY);
		delete []lpData; 		
	}
	key.Close();
/*
[HKEY_LOCAL_MACHINE\SOFTWARE\Classes\CLSID\{00000001-4FEF-40D3-B3FA-E0531B897F98}]
@="XviD MPEG-4 Video DecoderAbout"

[HKEY_LOCAL_MACHINE\SOFTWARE\Classes\CLSID\{00000001-4FEF-40D3-B3FA-E0531B897F98}\InprocServer32]
@="C:\\WINNT\\system32\\xvid.ax"
"ThreadingModel"="Both"
*/

	lRes = key.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Classes\\CLSID\\{00000001-4FEF-40D3-B3FA-E0531B897F98}"),KEY_READ|KEY_WRITE);
//	if (lRes != ERROR_SUCCESS) 
	{
		lRes = key.Create(HKEY_CLASSES_ROOT,_T("SOFTWARE\\Classes\\CLSID\\{00000001-4FEF-40D3-B3FA-E0531B897F98}"));
		lRes = key.SetValue(_T("XviD MPEG-4 Video DecoderAbout"),"");
		
		lRes = key.SetKeyValue("InprocServer32",sWinntPath + "\\system32\\xvid_infobird.ax");
		lRes = key.SetKeyValue("InprocServer32",_T("Both"),"ThreadingModel");		
	}
	key.Close();
/*
[HKEY_CLASSES_ROOT\CLSID\{083863F1-70DE-11d0-BD40-00A0C911CE86}\Instance\{64697678-0000-0010-8000-00AA00389B71}]
"FriendlyName"="XviD MPEG-4 Video Decoder"
"CLSID"="{64697678-0000-0010-8000-00AA00389B71}"
"FilterData"=hex:02,00,00,00,00,00,80,00,02,00,00,00,00,00,00,00,30,70,69,33,\
  00,00,00,00,00,00,00,00,07,00,00,00,00,00,00,00,00,00,00,00,30,74,79,33,00,\
  00,00,00,c0,00,00,00,d0,00,00,00,31,74,79,33,00,00,00,00,c0,00,00,00,e0,00,\
  00,00,32,74,79,33,00,00,00,00,c0,00,00,00,f0,00,00,00,33,74,79,33,00,00,00,\
  00,c0,00,00,00,00,01,00,00,34,74,79,33,00,00,00,00,c0,00,00,00,10,01,00,00,\
  35,74,79,33,00,00,00,00,c0,00,00,00,20,01,00,00,36,74,79,33,00,00,00,00,c0,\
  00,00,00,30,01,00,00,31,70,69,33,08,00,00,00,00,00,00,00,01,00,00,00,00,00,\
  00,00,00,00,00,00,30,74,79,33,00,00,00,00,c0,00,00,00,40,01,00,00,76,69,64,\
  73,00,00,10,00,80,00,00,aa,00,38,9b,71,78,76,69,64,00,00,10,00,80,00,00,aa,\
  00,38,9b,71,58,56,49,44,00,00,10,00,80,00,00,aa,00,38,9b,71,64,69,76,78,00,\
  00,10,00,80,00,00,aa,00,38,9b,71,44,49,56,58,00,00,10,00,80,00,00,aa,00,38,\
  9b,71,64,78,35,30,00,00,10,00,80,00,00,aa,00,38,9b,71,44,58,35,30,00,00,10,\
  00,80,00,00,aa,00,38,9b,71,6d,70,34,76,00,00,10,00,80,00,00,aa,00,38,9b,71,\
  00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00
  */
	lRes = key.Open(HKEY_CLASSES_ROOT, _T("CLSID\\{083863F1-70DE-11d0-BD40-00A0C911CE86}\\Instance\\{64697678-0000-0010-8000-00AA00389B71}"),KEY_READ|KEY_WRITE);
//	if (lRes != ERROR_SUCCESS) 
	{
		lRes = key.Create(HKEY_CLASSES_ROOT,_T("CLSID\\{083863F1-70DE-11d0-BD40-00A0C911CE86}\\Instance\\{64697678-0000-0010-8000-00AA00389B71}"));
		
		lRes = key.SetKeyValue("","XviD MPEG-4 Video Decoder","FriendlyName");
		lRes = key.SetKeyValue("","{64697678-0000-0010-8000-00AA00389B71}","CLSID");
		
		CString str = "02,00,00,00,ff,ff,ff,ff,02,00,00,00,00,00,00,00,30,70,69,33,"
			"00,00,00,00,00,00,00,00,07,00,00,00,00,00,00,00,00,00,00,00,30,74,79,33,00,"
			"00,00,00,c0,00,00,00,d0,00,00,00,31,74,79,33,00,00,00,00,c0,00,00,00,e0,00,"
			"00,00,32,74,79,33,00,00,00,00,c0,00,00,00,f0,00,00,00,33,74,79,33,00,00,00,"
			"00,c0,00,00,00,00,01,00,00,34,74,79,33,00,00,00,00,c0,00,00,00,10,01,00,00,"
			"35,74,79,33,00,00,00,00,c0,00,00,00,20,01,00,00,36,74,79,33,00,00,00,00,c0,"
			"00,00,00,30,01,00,00,31,70,69,33,08,00,00,00,00,00,00,00,01,00,00,00,00,00,"
			"00,00,00,00,00,00,30,74,79,33,00,00,00,00,c0,00,00,00,40,01,00,00,76,69,64,"
			"73,00,00,10,00,80,00,00,aa,00,38,9b,71,78,76,69,64,00,00,10,00,80,00,00,aa,"
			"00,38,9b,71,58,56,49,44,00,00,10,00,80,00,00,aa,00,38,9b,71,64,69,76,78,00,"
			"00,10,00,80,00,00,aa,00,38,9b,71,44,49,56,58,00,00,10,00,80,00,00,aa,00,38,"
			"9b,71,64,78,35,30,00,00,10,00,80,00,00,aa,00,38,9b,71,44,58,35,30,00,00,10,"
			"00,80,00,00,aa,00,38,9b,71,6d,70,34,76,00,00,10,00,80,00,00,aa,00,38,9b,71,"
			"00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00";
		
		str.Replace(",","");
		
		int iLength = str.GetLength()/2;		
		BYTE* lpData = new BYTE[iLength+1];	

		for(int i=0,j=0; i<str.GetLength(); i++)
		{
			if(i%2 == 0 || i == 0)
				continue;
			
			CString strTemp = str.Mid(i-1,2);
			int temp;
			sscanf((char*)strTemp.LockBuffer(),"%2X",&temp);
			//lpData[j] = __toascii(temp);
			memcpy((char*)&lpData[j],(char*)&temp,1);
			j++;
			strTemp.UnlockBuffer();
		}
		
		HKEY hKEY;
		long ret0=::RegOpenKeyEx(HKEY_CLASSES_ROOT,"CLSID\\{083863F1-70DE-11d0-BD40-00A0C911CE86}\\Instance\\{64697678-0000-0010-8000-00AA00389B71}",0,KEY_ALL_ACCESS,&hKEY);
		long ret2=::RegSetValueEx(hKEY,"FilterData",NULL,REG_BINARY,lpData,iLength);

		RegCloseKey(hKEY);
		delete []lpData; 		
	}
	key.Close();
/*
[HKEY_LOCAL_MACHINE\SOFTWARE\Classes\CLSID\{083863F1-70DE-11d0-BD40-00A0C911CE86}\Instance\{64697678-0000-0010-8000-00AA00389B71}]
"FriendlyName"="XviD MPEG-4 Video Decoder"
"CLSID"="{64697678-0000-0010-8000-00AA00389B71}"
"FilterData"=hex:02,00,00,00,00,00,80,00,02,00,00,00,00,00,00,00,30,70,69,33,\
  00,00,00,00,00,00,00,00,07,00,00,00,00,00,00,00,00,00,00,00,30,74,79,33,00,\
  00,00,00,c0,00,00,00,d0,00,00,00,31,74,79,33,00,00,00,00,c0,00,00,00,e0,00,\
  00,00,32,74,79,33,00,00,00,00,c0,00,00,00,f0,00,00,00,33,74,79,33,00,00,00,\
  00,c0,00,00,00,00,01,00,00,34,74,79,33,00,00,00,00,c0,00,00,00,10,01,00,00,\
  35,74,79,33,00,00,00,00,c0,00,00,00,20,01,00,00,36,74,79,33,00,00,00,00,c0,\
  00,00,00,30,01,00,00,31,70,69,33,08,00,00,00,00,00,00,00,01,00,00,00,00,00,\
  00,00,00,00,00,00,30,74,79,33,00,00,00,00,c0,00,00,00,40,01,00,00,76,69,64,\
  73,00,00,10,00,80,00,00,aa,00,38,9b,71,78,76,69,64,00,00,10,00,80,00,00,aa,\
  00,38,9b,71,58,56,49,44,00,00,10,00,80,00,00,aa,00,38,9b,71,64,69,76,78,00,\
  00,10,00,80,00,00,aa,00,38,9b,71,44,49,56,58,00,00,10,00,80,00,00,aa,00,38,\
  9b,71,64,78,35,30,00,00,10,00,80,00,00,aa,00,38,9b,71,44,58,35,30,00,00,10,\
  00,80,00,00,aa,00,38,9b,71,6d,70,34,76,00,00,10,00,80,00,00,aa,00,38,9b,71,\
  00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00
*/
	lRes = key.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Classes\\CLSID\\{083863F1-70DE-11d0-BD40-00A0C911CE86}\\Instance\\{64697678-0000-0010-8000-00AA00389B71}"),KEY_READ|KEY_WRITE);
//	if (lRes != ERROR_SUCCESS) 
	{
		lRes = key.Create(HKEY_LOCAL_MACHINE,_T("SOFTWARE\\Classes\\CLSID\\{083863F1-70DE-11d0-BD40-00A0C911CE86}\\Instance\\{64697678-0000-0010-8000-00AA00389B71}"));
		
		lRes = key.SetKeyValue("","XviD MPEG-4 Video Decoder","FriendlyName");
		lRes = key.SetKeyValue("","{64697678-0000-0010-8000-00AA00389B71}","CLSID");
		
		CString str = "02,00,00,00,ff,ff,ff,ff,02,00,00,00,00,00,00,00,30,70,69,33,"
			"00,00,00,00,00,00,00,00,07,00,00,00,00,00,00,00,00,00,00,00,30,74,79,33,00,"
			"00,00,00,c0,00,00,00,d0,00,00,00,31,74,79,33,00,00,00,00,c0,00,00,00,e0,00,"
			"00,00,32,74,79,33,00,00,00,00,c0,00,00,00,f0,00,00,00,33,74,79,33,00,00,00,"
			"00,c0,00,00,00,00,01,00,00,34,74,79,33,00,00,00,00,c0,00,00,00,10,01,00,00,"
			"35,74,79,33,00,00,00,00,c0,00,00,00,20,01,00,00,36,74,79,33,00,00,00,00,c0,"
			"00,00,00,30,01,00,00,31,70,69,33,08,00,00,00,00,00,00,00,01,00,00,00,00,00,"
			"00,00,00,00,00,00,30,74,79,33,00,00,00,00,c0,00,00,00,40,01,00,00,76,69,64,"
			"73,00,00,10,00,80,00,00,aa,00,38,9b,71,78,76,69,64,00,00,10,00,80,00,00,aa,"
			"00,38,9b,71,58,56,49,44,00,00,10,00,80,00,00,aa,00,38,9b,71,64,69,76,78,00,"
			"00,10,00,80,00,00,aa,00,38,9b,71,44,49,56,58,00,00,10,00,80,00,00,aa,00,38,"
			"9b,71,64,78,35,30,00,00,10,00,80,00,00,aa,00,38,9b,71,44,58,35,30,00,00,10,"
			"00,80,00,00,aa,00,38,9b,71,6d,70,34,76,00,00,10,00,80,00,00,aa,00,38,9b,71,"
			"00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00";
		
		str.Replace(",","");
		
		int iLength = str.GetLength()/2;		
		BYTE* lpData = new BYTE[iLength+1];	

		for(int i=0,j=0; i<str.GetLength(); i++)
		{
			if(i%2 == 0 || i == 0)
				continue;
			
			CString strTemp = str.Mid(i-1,2);
			int temp;
			sscanf((char*)strTemp.LockBuffer(),"%2X",&temp);
			//lpData[j] = __toascii(temp);
			memcpy((char*)&lpData[j],(char*)&temp,1);
			j++;
			strTemp.UnlockBuffer();
		}
		
		HKEY hKEY;
		long ret0=::RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Classes\\CLSID\\{083863F1-70DE-11d0-BD40-00A0C911CE86}\\Instance\\{64697678-0000-0010-8000-00AA00389B71}",0,KEY_ALL_ACCESS,&hKEY);
		long ret2=::RegSetValueEx(hKEY,"FilterData",NULL,REG_BINARY,lpData,iLength);

		RegCloseKey(hKEY);
		delete []lpData; 		
	}
	key.Close();
/*
[HKEY_LOCAL_MACHINE\SOFTWARE\Classes\CLSID\{64697678-0000-0010-8000-00AA00389B71}]
@="XviD MPEG-4 Video Decoder"

[HKEY_LOCAL_MACHINE\SOFTWARE\Classes\CLSID\{64697678-0000-0010-8000-00AA00389B71}\InprocServer32]
@="C:\\WINNT\\system32\\xvid.ax"
"ThreadingModel"="Both"

*/
	lRes = key.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Classes\\CLSID\\{64697678-0000-0010-8000-00AA00389B71}"),KEY_READ|KEY_WRITE);
//	if (lRes != ERROR_SUCCESS) 
	{
		lRes = key.Create(HKEY_LOCAL_MACHINE,_T("SOFTWARE\\Classes\\CLSID\\{64697678-0000-0010-8000-00AA00389B71}"));
		lRes = key.SetValue(_T("XviD MPEG-4 Video Decoder"),"");
		
		lRes = key.SetKeyValue("InprocServer32",sWinntPath + "\\system32\\xvid_infobird.ax");
		lRes = key.SetKeyValue("InprocServer32",_T("Both"),"ThreadingModel");		
	}
	key.Close();

/*
[HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Drivers32]
"vidc.XVID"="xvidvfw.dll"

[HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Control\MediaResources\icm\vidc.XVID]
"Description"="XviD MPEG-4 Video Codec"
"Driver"="xvidvfw.dll"
"FriendlyName"="XviD"
*/
	lRes = key.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Drivers32"),KEY_READ|KEY_WRITE);
//	if (lRes != ERROR_SUCCESS) 
	{
		lRes = key.Create(HKEY_LOCAL_MACHINE,_T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Drivers32"));
		lRes = key.SetValue(_T("xvidvfw_infobird.dll"),"vidc.XVID");
	}
	key.Close();

	lRes = key.Open(HKEY_LOCAL_MACHINE, _T("SYSTEM\\ControlSet001\\Control\\MediaResources\\icm\\vidc.XVID"),KEY_READ|KEY_WRITE);
//	if (lRes != ERROR_SUCCESS) 
	{
		lRes = key.Create(HKEY_LOCAL_MACHINE,_T("SYSTEM\\ControlSet001\\Control\\MediaResources\\icm\\vidc.XVID"));
		lRes = key.SetValue(_T("XviD MPEG-4 Video Codec"),"Description");
		lRes = key.SetValue(_T("xvidvfw_infobird.dll"),"Driver");
		lRes = key.SetValue(_T("XviD"),"FriendlyName");
	}
	key.Close();

/*
[HKEY_LOCAL_MACHINE\SYSTEM\ControlSet002\Control\MediaResources\icm\vidc.XVID]
"Description"="XviD MPEG-4 Video Codec"
"Driver"="xvidvfw.dll"
"FriendlyName"="XviD"

[HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\MediaResources\icm\vidc.XVID]
"Description"="XviD MPEG-4 Video Codec"
"Driver"="xvidvfw.dll"
"FriendlyName"="XviD"
*/
	lRes = key.Open(HKEY_LOCAL_MACHINE, _T("SYSTEM\\ControlSet002\\Control\\MediaResources\\icm\\vidc.XVID"),KEY_READ|KEY_WRITE);
//	if (lRes != ERROR_SUCCESS) 
	{
		lRes = key.Create(HKEY_LOCAL_MACHINE,_T("SYSTEM\\ControlSet002\\Control\\MediaResources\\icm\\vidc.XVID"));
		lRes = key.SetValue(_T("XviD MPEG-4 Video Codec"),"Description");
		lRes = key.SetValue(_T("xvidvfw_infobird.dll"),"Driver");
		lRes = key.SetValue(_T("XviD"),"FriendlyName");
	}
	key.Close();

	lRes = key.Open(HKEY_LOCAL_MACHINE, _T("SYSTEM\\CurrentControlSet\\Control\\MediaResources\\icm\\vidc.XVID"),KEY_READ|KEY_WRITE);
//	if (lRes != ERROR_SUCCESS) 
	{
		lRes = key.Create(HKEY_LOCAL_MACHINE,_T("SYSTEM\\CurrentControlSet\\Control\\MediaResources\\icm\\vidc.XVID"));
		lRes = key.SetValue(_T("XviD MPEG-4 Video Codec"),"Description");
		lRes = key.SetValue(_T("xvidvfw_infobird.dll"),"Driver");
		lRes = key.SetValue(_T("XviD"),"FriendlyName");
	}
	key.Close();

	return true;
}

