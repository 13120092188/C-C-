// FTPManage.h : main header file for the FTPMANAGE application
//

#if !defined(AFX_FTPMANAGE_H__846BF784_1745_45B7_AFAB_B2A5DC5F665A__INCLUDED_)
#define AFX_FTPMANAGE_H__846BF784_1745_45B7_AFAB_B2A5DC5F665A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFTPManageApp:
// See FTPManage.cpp for the implementation of this class
//



class CFTPManageApp : public CWinApp
{
public:
	CFTPManageApp();
	HIMAGELIST hImage;
	CImageList m_ImageList;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFTPManageApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFTPManageApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FTPMANAGE_H__846BF784_1745_45B7_AFAB_B2A5DC5F665A__INCLUDED_)
