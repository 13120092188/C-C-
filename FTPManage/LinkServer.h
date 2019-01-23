#if !defined(AFX_LINKSERVER_H__18B481EE_4BD1_4B6F_A4E3_55D05B95539A__INCLUDED_)
#define AFX_LINKSERVER_H__18B481EE_4BD1_4B6F_A4E3_55D05B95539A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LinkServer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLinkServer dialog
#include <afxinet.h>
#include "SortListCtrl.h"

typedef BOOL (__stdcall funMakeSure)(   PCSTR DirPath   );

class CLinkServer : public CDialog
{
// Construction
public:
	void UpLoadFile(CLinkServer * pDlg,LPCTSTR lpDir , LPCTSTR  csRelativePath, DWORD nFlag, BOOL	bIsFile = FALSE);
	void DeleteItemFormData(CListCtrl* pCtrl, DWORD nData);
	void DownLoadFile(CLinkServer * pDlg,LPCTSTR lpDir , LPCTSTR  csRelativePath, DWORD nFlag, BOOL	bIsFile = FALSE);	//lpDir是否是文件
	void DiskItemChange();
	void OnCancel();
	void GetSysDisk();
	void GetSysFileImage();
	CLinkServer(CWnd* pParent = NULL);   // standard constructor


	CComboBoxEx m_DiskList;
	CImageList  m_DiskImages,m_FileImages;
	CInternetSession Session;
	CFtpConnection * m_pFtp;
	funMakeSure * MakeSureDirectoryPathExists;	//定义函数指针

	CString m_DownloadDir;
	CString m_DownloadFile;
	int     m_DownloadFlag;
	HANDLE  *m_phThreads;
	HANDLE hMutex;
	DWORD	 m_dwStop;	//需要终止的任务
	CPtrList m_Threads;
// Dialog Data
	//{{AFX_DATA(CLinkServer)
	enum { IDD = IDD_LINKSERVER_DIALOG };
	CListCtrl	m_TastList;
	CSortListCtrl	m_RemoteFiles;
	CSortListCtrl	m_LocalFiles;
	CStatic	m_Frame;
	CButton	m_Anonymity;
	CEdit	m_Port;
	CEdit	m_User;
	CEdit	m_Password;
	CEdit	m_FtpServer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLinkServer)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLinkServer)
	virtual void OnOK();
	afx_msg void OnLoginFtp();
	virtual BOOL OnInitDialog();
	afx_msg void OnUpload();
	afx_msg void OnDownload();
	afx_msg void OnBtStop();
	afx_msg void OnBtDelete();
	afx_msg void OnBtContinue();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINKSERVER_H__18B481EE_4BD1_4B6F_A4E3_55D05B95539A__INCLUDED_)
