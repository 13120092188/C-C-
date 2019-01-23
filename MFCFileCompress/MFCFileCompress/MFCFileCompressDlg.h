
// MFCFileCompressDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CMFCFileCompressDlg 对话框
class CMFCFileCompressDlg : public CDialogEx
{
// 构造
public:
	CMFCFileCompressDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCFILECOMPRESS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	// 选择文件// 选择文件
	CBitmapButton m_buttoncf;
	// 普通压缩
	CBitmapButton m_buttoncc;
	// 加密压缩
	CBitmapButton m_buttonec;
	// 解压
	CBitmapButton m_buttonuc;
	//字体
	CFont m_font;
	// 显示压缩率
	CEdit m_EditCtrl_Ratio;
};
