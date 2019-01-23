// FTPManageDoc.h : interface of the CFTPManageDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FTPMANAGEDOC_H__8861E21A_BC7D_4A81_8946_0634481F0A30__INCLUDED_)
#define AFX_FTPMANAGEDOC_H__8861E21A_BC7D_4A81_8946_0634481F0A30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFTPManageDoc : public CDocument
{
protected: // create from serialization only
	CFTPManageDoc();
	DECLARE_DYNCREATE(CFTPManageDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFTPManageDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFTPManageDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFTPManageDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FTPMANAGEDOC_H__8861E21A_BC7D_4A81_8946_0634481F0A30__INCLUDED_)
