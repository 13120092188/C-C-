#pragma once

#include "resource.h"		
#include "afxwin.h"
// CPasswordDlg �Ի���

class CPasswordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPasswordDlg)

public:
	CPasswordDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPasswordDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString strPassword;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	CFont m_font;
	// ȷ����
	CBitmapButton m_buttonsure;
	// ȡ��
	CBitmapButton m_buttoncancel;
	afx_msg void OnEnChangeEdit1();
};
