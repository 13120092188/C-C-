
// MFCFileCompressDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CMFCFileCompressDlg �Ի���
class CMFCFileCompressDlg : public CDialogEx
{
// ����
public:
	CMFCFileCompressDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCFILECOMPRESS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CString strFilePath;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CEdit m_EditCtrl_FilePath;
	afx_msg void OnBnClickedButton4();
	// ѡ���ļ�// ѡ���ļ�
	CBitmapButton m_buttoncf;
	// ��ͨѹ��
	CBitmapButton m_buttoncc;
	// ����ѹ��
	CBitmapButton m_buttonec;
	// ��ѹ
	CBitmapButton m_buttonuc;
	//����
	CFont m_font;
	// ��ʾѹ����
	CEdit m_EditCtrl_Ratio;
};
