// FTPManageView.h : interface of the CFTPManageView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FTPMANAGEVIEW_H__54FEDD08_7C57_46D9_975F_BDFD7D728452__INCLUDED_)
#define AFX_FTPMANAGEVIEW_H__54FEDD08_7C57_46D9_975F_BDFD7D728452__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFTPManageView : public CView
{
protected: // create from serialization only
	CFTPManageView();
	DECLARE_DYNCREATE(CFTPManageView)

// Attributes
public:
	CFTPManageDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFTPManageView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFTPManageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFTPManageView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FTPManageView.cpp
inline CFTPManageDoc* CFTPManageView::GetDocument()
   { return (CFTPManageDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FTPMANAGEVIEW_H__54FEDD08_7C57_46D9_975F_BDFD7D728452__INCLUDED_)
