// MontgomeryDlg.h : header file
//

#if !defined(AFX_MONTGOMERYDLG_H__7A9D64E8_E400_4475_9BD7_802B86FEFA2A__INCLUDED_)
#define AFX_MONTGOMERYDLG_H__7A9D64E8_E400_4475_9BD7_802B86FEFA2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMontgomeryDlg dialog

class CMontgomeryDlg : public CDialog
{
// Construction
public:
	CMontgomeryDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMontgomeryDlg)
	enum { IDD = IDD_MONTGOMERY_DIALOG };
	CString	m_strA;
	CString	m_strB;
	CString	m_strM;
	CString	m_strR;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMontgomeryDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMontgomeryDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnInint();
	afx_msg void OnAdd();
	afx_msg void OnSub();
	afx_msg void OnMul();
	afx_msg void OnDiv();
	afx_msg void OnMod();
	afx_msg void OnModMul();
	afx_msg void OnModExp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONTGOMERYDLG_H__7A9D64E8_E400_4475_9BD7_802B86FEFA2A__INCLUDED_)
