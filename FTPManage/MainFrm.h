// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__B474A406_9BE7_4F4B_8081_606E6A4A16CB__INCLUDED_)
#define AFX_MAINFRM_H__B474A406_9BE7_4F4B_8081_606E6A4A16CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxinet.h>
#include "TastList.h"
#include "FTPView.h"
#include "LocalView.h"


typedef BOOL (__stdcall funMakeSure)( PCSTR DirPath );


#define ID_CONNECTBAR 111
#define ID_TOOLBAR 112

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	void DeleteItemFormData(CListCtrl *pCtrl, DWORD nData);
	void UpLoadFile(CMainFrame *pDlg, LPCTSTR lpDir, LPCTSTR csRelativePath,
		            DWORD nFlag, BOOL bIsFile,LPCTSTR lpServer,LPCTSTR lpUser,LPCTSTR lpPassword,int nPort);
	void DownLoadFile(CMainFrame * pDlg,LPCTSTR lpDir ,LPCTSTR csRelativePath, DWORD nFlag, 
		               BOOL bIsFile,LPCTSTR lpServer,LPCTSTR lpUser,LPCTSTR lpPassword,int nPort,LPCTSTR lpSaveDir);

	CInternetSession Session;
	CFtpConnection * m_pFtp;
	BOOL  m_bLoginSucc;	//是否登录成功

	CTastListView *m_pTastView;
	CLocalView    *m_pLocalView;
	CFTPView      *m_pFtpView;

	funMakeSure * MakeSureDirectoryPathExists;	//定义函数指针

	CString m_DownloadDir;
	CString m_DownloadFile;
	int     m_DownloadFlag;
	HANDLE  *m_phThreads;
	HANDLE hMutex;
	DWORD	 m_dwStop;	//需要终止的任务

	CString m_csServer,m_csUser,m_csPassword;
	int     m_nPort;
	CString m_csDownDir;	//下载文件的存储目录
	BOOL    m_bTurnOff;		//任务完成后是否关机



// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void TurnOff();
	void OnSetToolBar();
	void SetDownLoad();
	void OnDownload();
	void OnUpload();
	void LoginFTP();
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
public:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CDialogBar  m_ConnectBar;
	CDialogBar  m_ToolBar;
// Generated message map functions
protected:
	CSplitterWnd m_wndSplitter,m_ChildSplitter;

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLinkFtp();
	afx_msg void OnLoginbar();
	afx_msg void OnUpdateLoginbar(CCmdUI* pCmdUI);
	afx_msg void OnTurnoff();
	afx_msg void OnUpdateToolbarinfo(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__B474A406_9BE7_4F4B_8081_606E6A4A16CB__INCLUDED_)
