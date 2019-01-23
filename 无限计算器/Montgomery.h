// Montgomery.h : main header file for the MONTGOMERY application
//

#if !defined(AFX_MONTGOMERY_H__F6E78961_BB08_4CB3_B7B6_B541E8CC3740__INCLUDED_)
#define AFX_MONTGOMERY_H__F6E78961_BB08_4CB3_B7B6_B541E8CC3740__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMontgomeryApp:
// See Montgomery.cpp for the implementation of this class
//

class CMontgomeryApp : public CWinApp
{
public:
	CMontgomeryApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMontgomeryApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMontgomeryApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONTGOMERY_H__F6E78961_BB08_4CB3_B7B6_B541E8CC3740__INCLUDED_)
