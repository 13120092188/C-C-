#if !defined(AFX_LOCALVIEW_H__D304DAE0_3454_4959_8536_E0460AE727F9__INCLUDED_)
#define AFX_LOCALVIEW_H__D304DAE0_3454_4959_8536_E0460AE727F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LocalView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLocalView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "SortListCtrl.h"

class CLocalView : public CFormView
{
protected:
	CLocalView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CLocalView)
	CComboBoxEx m_DiskList;
	BOOL  m_bDrag;
	CImageList *m_pDragList;
// Form Data
public:
	//{{AFX_DATA(CLocalView)
	enum { IDD = IDD_LOCALVIEW_FORM };
	CStatic	m_Frame;
	CSortListCtrl	m_LocalFiles;
	//}}AFX_DATA

// Attributes
public:
	BOOL m_bSubClass;	//是否子类化窗口	
// Operations
public:
	void DiskItemChange();
	void GetSysDisk();
	void GetSysFileImage();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocalView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLocalView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CLocalView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBack();
	afx_msg void OnBegindragLocalfiles(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOCALVIEW_H__D304DAE0_3454_4959_8536_E0460AE727F9__INCLUDED_)
