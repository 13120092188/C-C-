#if !defined(AFX_TASTLIST_H__5ED52FC3_7259_48AE_A84F_E2295049F72C__INCLUDED_)
#define AFX_TASTLIST_H__5ED52FC3_7259_48AE_A84F_E2295049F72C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TastList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTastListView form view

#ifndef __AFXEXT_H__
#include <afxext.h> 
#endif
 
class CTastListView : public CFormView
{
protected:
	CTastListView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTastListView)

// Form Data
public:
	//{{AFX_DATA(CTastListView)
	enum { IDD = IDD_TASTLISTVIEW_FORM };
	CButton	m_Continue;
	CButton	m_Delete;
	CButton	m_Stop;
	CListCtrl	m_TastList;

	//}}AFX_DATA

// Attributes
public:

	BOOL m_bSubClass;	//是否子类化窗口	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTastListView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTastListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CTastListView)
	afx_msg void OnBtContinue();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBtStop();
	afx_msg void OnBtDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TASTLIST_H__5ED52FC3_7259_48AE_A84F_E2295049F72C__INCLUDED_)
