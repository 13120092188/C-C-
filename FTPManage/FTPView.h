#if !defined(AFX_FTPVIEW_H__E6181803_D1C2_491B_8430_6F82C8A9606A__INCLUDED_)
#define AFX_FTPVIEW_H__E6181803_D1C2_491B_8430_6F82C8A9606A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FTPView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFTPView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "SortListCtrl.h"

class CFTPView : public CFormView
{
protected:
	CFTPView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFTPView)
	BOOL m_bSubClass;	//是否子类化窗口
	BOOL  m_bDrag;
	CImageList *m_pDragList;
// Form Data
public:
	//{{AFX_DATA(CFTPView)
	enum { IDD = IDD_FTPVIEW_FORM };
	CSortListCtrl	m_RemoteFiles;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	void GetSysFileImage();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFTPView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFTPView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CFTPView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBack();
	afx_msg void OnBegindragRemotefiles(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FTPVIEW_H__E6181803_D1C2_491B_8430_6F82C8A9606A__INCLUDED_)
