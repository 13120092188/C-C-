// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "FTPManage.h"

#include "MainFrm.h"
//#include "LinkServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

struct ThreadParam
{
	CMainFrame* pDlg;			//当前对话框
	int			nItem;			//线程对应列表中的任务
	char		m_DownFile[MAX_PATH];	//下载文件
	char		m_RelativeFile[MAX_PATH];//下载到本地的路径
	int			nDownFlag;		//下载标记
	HANDLE		m_hThread;		//线程句柄
};


extern DWORD __stdcall DownloadThreadProc( LPVOID lpParameter);
extern DWORD __stdcall DownloadThreadProc( LPVOID lpParameter);

//上传文件的线程函数
DWORD __stdcall UploadThreadProc( LPVOID lpParameter)
{

	ThreadParam *Param = (ThreadParam *)lpParameter;
	CMainFrame * pDlg = Param->pDlg;
	int nItem = Param->nItem;

	char downfile[MAX_PATH] = {0};
	strcpy(downfile,Param->m_DownFile);
	char relfile[MAX_PATH] = {0};
	strcpy(relfile,Param->m_RelativeFile);

	pDlg->m_pTastView->m_TastList.SetItemText(nItem,4,"正在上传");

	if (Param->nDownFlag ==0)	//当前选择的是文件
	{	
		pDlg->UpLoadFile(pDlg,downfile,relfile,(DWORD)Param->m_hThread,true,pDlg->m_csServer,
			             pDlg->m_csUser,pDlg->m_csPassword,pDlg->m_nPort);
	}
	else if(Param->nDownFlag ==1)
	{
		pDlg->UpLoadFile(pDlg,downfile,relfile,(DWORD)Param->m_hThread,false,pDlg->m_csServer,
			             pDlg->m_csUser,pDlg->m_csPassword,pDlg->m_nPort);
	}

	if (pDlg->m_dwStop == (DWORD)Param->m_hThread)	//终止线程后设置初始标记
	{
		pDlg->m_dwStop = 0;
	}

	pDlg->m_pTastView->m_TastList.SetItemText(nItem,3,"完成");
	pDlg->m_pTastView->m_TastList.SetItemText(nItem,4,"上传完成");
	pDlg->DeleteItemFormData(&pDlg->m_pTastView->m_TastList,(DWORD)Param->m_hThread);

	delete Param;
	int nCount = pDlg->m_pTastView->m_TastList.GetItemCount();
	if (pDlg->m_bTurnOff && nCount==0)
	{
		pDlg->TurnOff();//关机操作
	}
	return 0;
}


//下载文件的线程函数
DWORD __stdcall DownloadThreadProc( LPVOID lpParameter)
{

	ThreadParam *Param = (ThreadParam *)lpParameter;
	CMainFrame * pDlg = Param->pDlg;
	int nItem = Param->nItem;

	char downfile[MAX_PATH] = {0};
	strcpy(downfile,Param->m_DownFile);
	char relfile[MAX_PATH] = {0};
	strcpy(relfile,Param->m_RelativeFile);

	pDlg->m_pTastView->m_TastList.SetItemText(nItem,4,"正在下载");

	if (Param->nDownFlag ==0)	//当前选择的是文件
	{	
		pDlg->DownLoadFile(pDlg,downfile,relfile,(DWORD)Param->m_hThread,true,pDlg->m_csServer,
			             pDlg->m_csUser,pDlg->m_csPassword,pDlg->m_nPort,pDlg->m_csDownDir);
	}
	else if(Param->nDownFlag ==1)
	{
		pDlg->DownLoadFile(pDlg,downfile,relfile,(DWORD)Param->m_hThread,false,pDlg->m_csServer,
			             pDlg->m_csUser,pDlg->m_csPassword,pDlg->m_nPort,pDlg->m_csDownDir);
	}


	pDlg->m_pTastView->m_TastList.SetItemText(nItem,3,"完成");
	pDlg->m_pTastView->m_TastList.SetItemText(nItem,4,"下载完成");

	if (pDlg->m_dwStop == (DWORD)Param->m_hThread)	//终止线程后设置初始标记
	{
		pDlg->m_dwStop = 0;
	}

	pDlg->DeleteItemFormData(&pDlg->m_pTastView->m_TastList,(DWORD)Param->m_hThread);

	int nCount = pDlg->m_pTastView->m_TastList.GetItemCount();
	delete Param;
	if (pDlg->m_bTurnOff && nCount == 0 )
	{
		pDlg->TurnOff();	//关机操作
	}
	return 0;
}



IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_LINKFTP, OnLinkFtp)
	ON_COMMAND(ID_CONNECTBAR, OnLoginbar)
	ON_COMMAND(ID_TURNOFF, OnTurnoff)
	ON_COMMAND(ID_UPLOAD, OnUpload)
	ON_UPDATE_COMMAND_UI(ID_TOOLBARINFO, OnUpdateToolbarinfo)
	//}}AFX_MSG_MAP
	ON_COMMAND(IDC_LOGIN_FTP, LoginFTP)
	ON_COMMAND(IDC_BT_UPLOAD,OnUpload)
	ON_COMMAND(IDC_BT_DOWNLOAD,OnDownload)
	ON_COMMAND(IDC_SETDIR,SetDownLoad)
	ON_COMMAND(ID_TOOLBARINFO,OnSetToolBar)
	ON_COMMAND(ID_DOWNLOAD, OnDownload)
	
	ON_UPDATE_COMMAND_UI(ID_CONNECTBAR, OnUpdateLoginbar)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_bLoginSucc = FALSE;
	m_pTastView = NULL;
	m_pFtpView = NULL;
	m_pLocalView = NULL;
	m_phThreads = NULL;
	m_dwStop = 0;
	m_csServer = m_csPassword = m_csUser = "";
	m_nPort = 0;
	m_bTurnOff = FALSE;
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;  
	}

	if (!m_ConnectBar.Create(this, IDD_CONNECTFTPDLG, CBRS_TOP | 
		CBRS_TOOLTIPS | CBRS_FLYBY|CBRS_SIZE_DYNAMIC, ID_CONNECTBAR))
	{
		TRACE0("Failed to create Dialog bar\n");
		return -1;      		
	}
	m_ConnectBar.EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
		EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_ConnectBar);

	m_ConnectBar.SetDlgItemText(IDC_FTPSERVER,"192.168.1.23");
	m_ConnectBar.SetDlgItemText(IDC_FTPPORT,"21");

	hMutex = CreateMutex(NULL,false,"mutex1");

	HMODULE hMod = LoadLibrary("Dbghelp.dll");
	MakeSureDirectoryPathExists = (funMakeSure *)GetProcAddress(hMod,"MakeSureDirectoryPathExists");

	if (!m_ToolBar.Create(this,IDD_TOOLBAR,CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY|CBRS_SIZE_DYNAMIC,
			ID_TOOLBARINFO))
	{
		TRACE0("Failed to create Dialog bar\n");
		return -1;      			
	}
	m_ToolBar.EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_ToolBar);

	m_ToolBar.SetDlgItemText(IDC_SAVEDIR,"c:");

	SetIcon(LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_MAIN)),TRUE);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnLinkFtp() 
{

//	CLinkServer linkSvr;
//	linkSvr.DoModal();
	
}

void CMainFrame::LoginFTP()
{
	CString csServer,csPassword,csUser,csPort;
	m_ConnectBar.GetDlgItemText(IDC_FTPSERVER,csServer);
	m_ConnectBar.GetDlgItemText(IDC_FTPPORT,csPort);
	m_ConnectBar.GetDlgItemText(IDC_PASSWORD,csPassword);
	m_ConnectBar.GetDlgItemText(IDC_USER,csUser);
	if ( !csServer.IsEmpty() && !csPassword.IsEmpty() &&
		 !csUser.IsEmpty() && !csPort.IsEmpty())
	{
		try
		{
			m_pFtp =  Session.GetFtpConnection(csServer,csUser,csPassword,atoi(csPort));
			m_bLoginSucc = TRUE;
			CString csCurDir;
			m_pFtp->GetCurrentDirectory(csCurDir);
			if (m_pFtpView != NULL)
			{
				m_pFtpView->m_RemoteFiles.m_FtpServer = csServer;
				m_pFtpView->m_RemoteFiles.m_Port = csPort;
				m_pFtpView->m_RemoteFiles.m_User = csUser;
				m_pFtpView->m_RemoteFiles.m_Password = csPassword;	
				
				m_csServer = csServer;
				m_csPassword = csPassword;
				m_csUser = csUser;
				m_nPort = atoi(csPort);

				m_pFtpView->m_RemoteFiles.m_BaseDir = csCurDir;
				m_pFtpView->m_RemoteFiles.DisplayPath("");
			}	
		}
		catch(CInternetException &e)
		{
			m_bLoginSucc = FALSE;
			delete m_pFtp;	
		}
		delete m_pFtp;	
	}
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{

	if (!m_wndSplitter.CreateStatic(this, 2, 1))
	{
		TRACE0("Failed to create splitter bar ");
		return FALSE;    
	}
	if (!m_ChildSplitter.CreateStatic(&m_wndSplitter, 1, 2,WS_CHILD|WS_VISIBLE,m_wndSplitter.IdFromRowCol(0,0)))
	{
		TRACE0("Failed to create splitter bar ");
		return FALSE;   
	}
	m_ChildSplitter.CreateView(0,0,RUNTIME_CLASS(CLocalView),CSize(200,180),pContext);
	m_ChildSplitter.CreateView(0,1,RUNTIME_CLASS(CFTPView),CSize(180,180),pContext);
	m_wndSplitter.CreateView(1,0,RUNTIME_CLASS(CTastListView),CSize(0,10),pContext);

	//设置第一行的高度
	m_wndSplitter.SetRowInfo(0,400,50);

	//设置第一行各列的宽度
	m_ChildSplitter.SetColumnInfo(0,400,50);
	m_ChildSplitter.SetColumnInfo(1,400,50);

	m_pTastView = (CTastListView*)m_wndSplitter.GetPane(1,0);
	m_pFtpView = (CFTPView*)m_ChildSplitter.GetPane(0,1);
	m_pLocalView = (CLocalView*)m_ChildSplitter.GetPane(0,0);

	return TRUE;
}

void CMainFrame::OnUpload()
{
	if (m_bLoginSucc && m_pLocalView != NULL)
	{
		POSITION pos = m_pLocalView->m_LocalFiles.GetFirstSelectedItemPosition();
		int nSelCount = m_pLocalView->m_LocalFiles.GetSelectedCount();

		while (pos != NULL)
		{
			int nItem = m_pLocalView->m_LocalFiles.GetNextSelectedItem(pos);

			LVITEM item;
			item.mask = LVIF_TEXT;
			item.cchTextMax = MAX_PATH;
			char text[MAX_PATH] = {0};
			item.pszText = text;
			item.iItem = nItem ;
			item.iSubItem = 0;
			m_pLocalView->m_LocalFiles.GetItem(&item);

			int nCount = m_pTastView->m_TastList.GetItemCount();
			int nCurItem;
			nCurItem = m_pTastView->m_TastList.InsertItem(nCount,"");
			
			m_pTastView->m_TastList.SetItemData(nCurItem,nCurItem);

			m_pTastView->m_TastList.SetItemText(nCurItem,0,text);
			m_pTastView->m_TastList.SetItemText(nCurItem,1,"上传");
			m_pTastView->m_TastList.SetItemText(nCurItem,2,m_csServer);
			m_pTastView->m_TastList.SetItemText(nCurItem,3,"正在上传");

			ThreadParam * Param = new ThreadParam();
			Param->pDlg = this;
			Param->nItem = nCurItem;
			Param->nDownFlag = m_pLocalView->m_LocalFiles.GetItemData(nItem );

			memset(Param->m_DownFile,0,MAX_PATH);
			memset(Param->m_RelativeFile,0,MAX_PATH);

			strcpy(Param->m_DownFile, m_pLocalView->m_LocalFiles.m_CurDir);
			strcat(Param->m_DownFile,text);

			CString csRelative  = m_pFtpView->m_RemoteFiles.m_BaseDir;

			if (csRelative.Right(1) != "/" && csRelative.GetLength()>1)
				csRelative += "/";

			csRelative +=  m_pFtpView->m_RemoteFiles.m_CurDir;

			if (csRelative.Right(1) != "/" && csRelative.GetLength()>1)
				csRelative += "/";

			csRelative += text;

			strcpy(Param->m_RelativeFile,csRelative);

			HANDLE hHandle = CreateThread(NULL,0,UploadThreadProc,(void*)Param,0,NULL);
			m_pTastView->m_TastList.SetItemData(nCurItem,(DWORD)hHandle);
			Param->m_hThread = hHandle;
		}
	}
}

void CMainFrame::DeleteItemFormData(CListCtrl *pCtrl, DWORD nData)
{
	WaitForSingleObject(hMutex,INFINITE);	//进行线程同步限制
	DWORD nItemData;
	for (int i=0; i< pCtrl->GetItemCount(); i++)
	{
		nItemData = pCtrl->GetItemData(i);
		if (nItemData==nData)
		{
			pCtrl->DeleteItem(i);
			break;
		}
	}
	ReleaseMutex(hMutex);
}


void CMainFrame::UpLoadFile(CMainFrame *pDlg, LPCTSTR lpDir, LPCTSTR csRelativePath, DWORD nFlag, 
							BOOL bIsFile,LPCTSTR lpServer,LPCTSTR lpUser,LPCTSTR lpPassword,int nPort)
{
	CFtpConnection* pTemp = NULL;
	pTemp =  Session.GetFtpConnection(lpServer,lpUser,lpPassword,nPort);

	CFileFind Find;
	CString  filename;

	if (m_dwStop == nFlag)	//表示当前任务被挂起
	{
		pTemp->Close();
		delete pTemp;
		Find.Close();
		return;
	}

	CString csFindDir = lpDir;
	if (bIsFile == FALSE)
	{
		if (csFindDir.Right(1) != "\\")
			csFindDir += "\\";
		int nFindPos = csFindDir.Find("*.*");
		if (nFindPos <0)
			csFindDir += "*.*";
	}

	BOOL ret = Find.FindFile(csFindDir);
	if (ret)
	{
		while (Find.FindNextFile())
		{
			filename = Find.GetFileName();
			if (Find.IsDirectory() && !Find.IsDots())
			{
				char csdir[MAX_PATH] = {0};
				char csRetPath[MAX_PATH] = {0};
				strcpy(csdir,lpDir);
				strcat(csdir,"\\");
				strcat(csdir,filename);
				strcpy(csRetPath,csRelativePath);
				strcat(csRetPath,"/");
				strcat(csRetPath,filename);
				UpLoadFile(pDlg,csdir,csRetPath,nFlag,false,lpServer,lpUser,lpPassword,nPort);

			}
			else if (!Find.IsDirectory())
			{		
				//获取FTP服务器当前目录
				filename = Find.GetFileName();
				//

				CString csDir = csRelativePath;
				if (csDir.Left(1) != "/")
					csDir = "/" + csDir;
				csDir += "/";	
				//利用循环来创建多级FTP目录
				
				CString csTmpDir = "";//csDir;
				int nFind = 0;
				int nPos = 0;
				while (nPos != -1)
				{
					nPos = csDir.Find('/',nFind);
					if (nPos == -1)
						csTmpDir = csDir;
					else
						csTmpDir = csDir.Left(nPos);
					pTemp->CreateDirectory(csTmpDir);
					nFind =nPos+1;
				}
	
				csDir += filename;
				//创建文件

				CInternetFile* pFile = pTemp->OpenFile(csDir ,GENERIC_WRITE,
													   INTERNET_FLAG_TRANSFER_BINARY|INTERNET_FLAG_RELOAD);
				if (pFile!=NULL)
				{
					DWORD dwLen = Find.GetLength();	//获取文件长度
					DWORD dwReadNum = 0;
					CFile file;
					file.Open(Find.GetFilePath(),CFile::modeRead);
					void *pBuffer =  NULL;
					HGLOBAL hHeap = GlobalAlloc(GMEM_FIXED|GMEM_ZEROINIT,8192);
					pBuffer = GlobalLock(hHeap);
					while (dwReadNum < dwLen)
					{
						if (m_dwStop == nFlag)	//表示当前任务被挂起
						{
							pTemp->Close();
							delete pTemp;
							pFile->Close();
							file.Close();
							Find.Close();
							delete pFile;
							GlobalUnlock(hHeap);
							GlobalFree(hHeap);
							return;
						}	

						UINT nFact = file.Read(pBuffer,8192);
						if (nFact > 0)
						{
							pFile->Write(pBuffer,nFact);
						}
						dwReadNum += nFact;
					}

					GlobalUnlock(hHeap);
					GlobalFree(hHeap);
					pFile->Close();
					delete pFile;
					file.Close();

				}
			}
		}
		if (Find.IsDirectory() && !Find.IsDots())	//是目录
		{

			filename = Find.GetFileName();
			char csdir[MAX_PATH] = {0};
			char csRetPath[MAX_PATH] = {0};
			strcpy(csdir,lpDir);
			strcat(csdir,"\\");
			strcat(csdir,filename);

			strcpy(csRetPath,csRelativePath);
			strcat(csRetPath,"/");
			strcat(csRetPath,filename);
			UpLoadFile(pDlg,csdir,csRetPath,nFlag,false,lpServer,lpUser,lpPassword,nPort);	
		}
		else if (!Find.IsDirectory())					//是文件
		{
			CString csUrl;
			if(bIsFile==FALSE)
			{
				csUrl = csRelativePath;
				if (csUrl.Left(1) != "/")
					csUrl = "/" + csUrl;
				csUrl += "/";
				csUrl += Find.GetFileName();
			}
			else
			{
				csUrl = csRelativePath;
				if (csUrl.Left(1) != "/")
					csUrl = "/" + csUrl;

			}
			filename = Find.GetFileName();


			CString csGetDir;
			int nFind = csUrl.ReverseFind('/');
			csGetDir = csUrl.Left(nFind);
			CString csTmpDir = "";
			nFind = 0;
			int nPos = 0;
			while (nPos != -1)
			{
				nPos = csGetDir.Find('/',nFind);
				if (nPos == -1)
					csTmpDir = csGetDir;
				else
					csTmpDir = csGetDir.Left(nPos);
			
				pTemp->CreateDirectory(csTmpDir);
				nFind =nPos+1;
			}


			CInternetFile* pFile = pTemp->OpenFile(csUrl ,GENERIC_WRITE ,
												   INTERNET_FLAG_TRANSFER_BINARY|INTERNET_FLAG_RELOAD);
			if (pFile!=NULL)
			{
				DWORD dwLen = Find.GetLength();	//获取文件长度
				DWORD dwReadNum = 0;
				CFile file;
				//创建文件
				CString csFileName = Find.GetFilePath();
				file.Open(csFileName,CFile::modeRead);

				void *pBuffer = NULL;//new BYTE[8192];
				HGLOBAL hHeap = GlobalAlloc(GMEM_FIXED|GMEM_ZEROINIT,8192);
				pBuffer = GlobalLock(hHeap);

				int nNum = 1;
				while (dwReadNum < dwLen)
				{
					if (m_dwStop == nFlag)	//表示当前任务被挂起
					{
						pTemp->Close();
						delete pTemp;
						pFile->Close();
						file.Close();
						Find.Close();
						delete pFile;
						GlobalUnlock(hHeap);
						GlobalFree(hHeap);
						return;
					}
				
					UINT nFact = file.Read(pBuffer,8192);
					if (nFact >0)
					{
						pFile->Write(pBuffer,nFact);
					}
					dwReadNum += nFact;
				}
				GlobalUnlock(hHeap);
				GlobalFree(hHeap);
				pFile->Close();
				delete pFile;
				file.Close();
			}
		}
	}
	Find.Close();
	delete pTemp;
}
/**************************************参数说明*******************************************
pDlg:			表示主窗口，在这里没有实际意义
lpDir:			表示当前下载的文件或目录
csRelativePath:	表示文件存储到本地的相对路径,与lpSaveDir参数构成完整的路径
nFlag:			表示结束标记，如果用户取消了下载任务，立即退出DownLoadFile函数
bIsFile:		表示当前的文件名是否是一个完整文件名，在首次调用DownLoadFile函数时bIsFile为TRUE
				例如，当下载的FTP目录为Data，如果Data目录下的zone.txt文件是最后一个查找的文件
				则查找该文件时获得的文件名是"Data/zone.txt"，该文件名是一个完整的文件名，
				不需要在添加父目录了

lpServer:		表示FTP服务器地址
lpUser:			表示登录用户名
lpPassword:		表示登录密码
nPort:			表示端口号
lpSaveDir:		表示下载文件在本地的根存储路径
***********************************************************************************************/

void CMainFrame::DownLoadFile(CMainFrame * pDlg,LPCTSTR lpDir ,LPCTSTR csRelativePath, DWORD nFlag, 
		               BOOL bIsFile,LPCTSTR lpServer,LPCTSTR lpUser,LPCTSTR lpPassword,int nPort,LPCTSTR lpSaveDir)
{
	CFtpConnection* pTemp = NULL;
	pTemp =  Session.GetFtpConnection(lpServer,lpUser,lpPassword,nPort);
	CFtpFileFind Find(pTemp);
	CString  filename;

	if (m_dwStop == nFlag)	//表示当前任务被挂起
	{
		pTemp->Close();
		delete pTemp;
		Find.Close();
		return;
	}

	BOOL ret ;
	if (strlen(lpDir)==0)
		ret = Find.FindFile(NULL,INTERNET_FLAG_EXISTING_CONNECT);
	else
		ret = Find.FindFile(lpDir,INTERNET_FLAG_EXISTING_CONNECT);
	if (ret)
	{
		while (Find.FindNextFile())
		{
			filename = Find.GetFileName();
			if (Find.IsDirectory())
			{

				char csdir[MAX_PATH] = {0};

				char csRetPath[MAX_PATH] = {0};
				strcpy(csdir,lpDir);

				strcat(csdir,"/");
				strcat(csdir,filename);

				strcpy(csRetPath,csRelativePath);
				strcat(csRetPath,"/");

				strcat(csRetPath,filename);


				DownLoadFile(pDlg,csdir,csRetPath,nFlag,false,lpServer,lpUser,lpPassword,nPort,lpSaveDir);
			}
			else 
			{
				char csUrl[MAX_PATH] = {0};

				strcpy(csUrl,lpDir);
				strcat(csUrl,"/");
				strcat(csUrl,Find.GetFileName());

			
				filename = Find.GetFileName();
			
				CInternetFile* pFile = pTemp->OpenFile(csUrl ,GENERIC_READ,
													   INTERNET_FLAG_TRANSFER_BINARY|INTERNET_FLAG_RELOAD);
				if (pFile!=NULL)
				{
					DWORD dwLen = Find.GetLength();	//获取文件长度
					DWORD dwReadNum = 0;
					CFile file;

					CString csDir = csRelativePath;

					csDir.Replace('/','\\');
					csDir = lpSaveDir + csDir +"\\";
					//先创建目录
					pDlg->MakeSureDirectoryPathExists(csDir);
					//创建文件
					csDir += filename;
					file.Open(csDir,CFile::modeCreate|CFile::modeWrite);
					void *pBuffer =  NULL;//new BYTE[8192];
					HGLOBAL hHeap = GlobalAlloc(GMEM_FIXED|GMEM_ZEROINIT,8192);
					pBuffer = GlobalLock(hHeap);

					int nNum = 1;
					while (dwReadNum < dwLen)
					{
						if (m_dwStop == nFlag)	//表示当前任务被挂起
						{
							pTemp->Close();
							delete pTemp;
							pFile->Close();
							file.Close();
							Find.Close();
							delete pFile;
							GlobalUnlock(hHeap);
							GlobalFree(hHeap);

							return;
						}

						nNum ++;

						UINT nFact = pFile->Read(pBuffer,8192);
						if (nFact > 0)
						{
							file.Write(pBuffer,nFact);
						}
						dwReadNum += nFact;
					}

					GlobalUnlock(hHeap);
					GlobalFree(hHeap);
					pFile->Close();
					delete pFile;
					file.Close();

				}
			}
		}
		if (Find.IsDirectory())
		{
			filename = Find.GetFileName();
			char csdir[MAX_PATH] = {0};
			char csRetPath[MAX_PATH] = {0};
			strcpy(csdir,lpDir);
			strcat(csdir,"/");
			strcat(csdir,filename);

			strcpy(csRetPath,csRelativePath);
			strcat(csRetPath,"/");

			strcat(csRetPath,filename);
			DownLoadFile(pDlg,csdir,csRetPath,nFlag,false,lpServer,lpUser,lpPassword,nPort,lpSaveDir);	
		}
		else
		{
			char csUrl[MAX_PATH] = {0};

			if(bIsFile==FALSE)
			{
				strcpy(csUrl,lpDir);
				strcat(csUrl,"/");
				strcat(csUrl,Find.GetFileName());
			}

			else
			{
				strcpy(csUrl,lpDir);
			}

			filename = Find.GetFileName();

			CInternetFile* pFile = pTemp->OpenFile(csUrl ,GENERIC_READ,
												   INTERNET_FLAG_TRANSFER_BINARY|INTERNET_FLAG_RELOAD);
			if (pFile!=NULL)
			{
				DWORD dwLen = Find.GetLength();	//获取文件长度
				DWORD dwReadNum = 0;
				CFile file;
				CString csDir;
				
				if (bIsFile==FALSE)
				{
					csDir = csRelativePath;
					csDir += "/";
					csDir += Find.GetFileName();
					csDir.Replace('/','\\');
					csDir = lpSaveDir + csDir;
					//先创建目录
					CString csPath;
					int nPos = csDir.ReverseFind('\\');
					csPath = csDir.Left(nPos+1);
					
					pDlg->MakeSureDirectoryPathExists(csPath);
				}
				else
				{
					csDir = lpSaveDir;
					csDir += "\\";
					csDir += csRelativePath;
				}
				//创建文件
				file.Open(csDir,CFile::modeCreate|CFile::modeWrite);
				void *pBuffer = NULL;
				HGLOBAL hHeap = GlobalAlloc(GMEM_FIXED|GMEM_ZEROINIT,8192);
				pBuffer = GlobalLock(hHeap);

				int nNum = 1;
				while (dwReadNum < dwLen)
				{
					if (m_dwStop == nFlag)	//表示当前任务被挂起
					{
						pTemp->Close();
						delete pTemp;
						pFile->Close();
						file.Close();
						Find.Close();
						delete pFile;
						GlobalUnlock(hHeap);
						GlobalFree(hHeap);

						return;
					}
				
					UINT nFact = pFile->Read(pBuffer,8192);
					if (nFact >0)
					{
						file.Write(pBuffer,nFact);
					}
					dwReadNum += nFact;
				}
				GlobalUnlock(hHeap);
				GlobalFree(hHeap);

				pFile->Close();
				delete pFile;
				file.Close();
			}
		}
	}
	Find.Close();
	delete pTemp;
}

void CMainFrame::OnDownload()
{
	if (m_bLoginSucc && m_pLocalView != NULL)
	{
		m_ToolBar.GetDlgItemText(IDC_SAVEDIR,m_csDownDir);

		POSITION pos = m_pFtpView->m_RemoteFiles.GetFirstSelectedItemPosition();
		int nSelCount = m_pFtpView->m_RemoteFiles.GetSelectedCount();

		while (pos != NULL)
		{
			int nItem = m_pFtpView->m_RemoteFiles.GetNextSelectedItem(pos);

			LVITEM item;
			item.mask = LVIF_TEXT;
			item.cchTextMax = MAX_PATH;
			char text[MAX_PATH] = {0};
			item.pszText = text;
			item.iItem = nItem ;
			item.iSubItem = 0;
			m_pFtpView->m_RemoteFiles.GetItem(&item);

			int nCount = m_pTastView->m_TastList.GetItemCount();
			int nCurItem;
			nCurItem = m_pTastView->m_TastList.InsertItem(nCount,"");
			
			m_pTastView->m_TastList.SetItemData(nCurItem,nCurItem);

			m_pTastView->m_TastList.SetItemText(nCurItem,0,text);
			m_pTastView->m_TastList.SetItemText(nCurItem,1,"下载");
			m_pTastView->m_TastList.SetItemText(nCurItem,2,m_csServer);
			m_pTastView->m_TastList.SetItemText(nCurItem,3,"正在下载");

			ThreadParam * Param = new ThreadParam();
			Param->pDlg = this;
			Param->nItem = nCurItem;
			Param->nDownFlag =m_pFtpView->m_RemoteFiles.GetItemData(nItem );

			memset(Param->m_DownFile,0,MAX_PATH);
			memset(Param->m_RelativeFile,0,MAX_PATH);

			strcpy(Param->m_DownFile, m_pFtpView->m_RemoteFiles.m_CurDir);
			strcat(Param->m_DownFile,text);
			strcpy(Param->m_RelativeFile,text);

			HANDLE hHandle = CreateThread(NULL,0,DownloadThreadProc,(void*)Param,0,NULL);
			m_pTastView->m_TastList.SetItemData(nCurItem,(DWORD)hHandle);
			Param->m_hThread = hHandle;
		}
	}
}

void CMainFrame::SetDownLoad()
{
	BROWSEINFO BrowInfo;
	char csFolder[MAX_PATH] = {0};
	memset(&BrowInfo,0,sizeof(BROWSEINFO));
	BrowInfo.hwndOwner = m_hWnd;
	BrowInfo.pszDisplayName = csFolder;
	BrowInfo.lpszTitle = "请选择文件";
	BrowInfo.ulFlags = BIF_EDITBOX;
	ITEMIDLIST *pitem = SHBrowseForFolder(&BrowInfo);
	if (pitem)
	{
		SHGetPathFromIDList(pitem,csFolder);
		m_csDownDir = csFolder;
		m_ToolBar.SetDlgItemText(IDC_SAVEDIR,m_csDownDir);		
	}
}

void CMainFrame::OnLoginbar() 
{
	CMenu * pMenu = GetMenu();
	CMenu * pSub = pMenu->GetSubMenu(0);
	if (pSub != NULL)
	{
		int nState = pSub->GetMenuState(ID_CONNECTBAR,MF_BYCOMMAND);
		if (nState == MF_CHECKED)
		{
			pSub->CheckMenuItem(ID_CONNECTBAR,MF_BYCOMMAND|MF_UNCHECKED);
			CControlBar* pBar = GetControlBar(ID_CONNECTBAR);
			if (pBar != NULL)
			{
				ShowControlBar(pBar, (pBar->GetStyle() & WS_VISIBLE) == 0, FALSE);
			}
			RecalcLayout();
		}
		else if (nState == MF_UNCHECKED)
		{
			pSub->CheckMenuItem(ID_CONNECTBAR,MF_BYCOMMAND|MF_CHECKED);
			CControlBar* pBar = GetControlBar(ID_CONNECTBAR);
			if (pBar != NULL)
			{
				ShowControlBar(pBar, (pBar->GetStyle() & WS_VISIBLE) == 0, FALSE);
			}
			RecalcLayout();
		}
	}
}

void CMainFrame::OnUpdateLoginbar(CCmdUI* pCmdUI) 
{
	CControlBar* pBar = GetControlBar(pCmdUI->m_nID);
	if (pBar != NULL)
	{
		pCmdUI->SetCheck((pBar->GetStyle() & WS_VISIBLE) != 0);
		return;
	}
	pCmdUI->ContinueRouting();
}

void CMainFrame::OnSetToolBar()
{
	CMenu * pMenu = GetMenu();
	CMenu * pSub = pMenu->GetSubMenu(0);
	if (pSub != NULL)
	{
		int nState = pSub->GetMenuState(ID_TOOLBARINFO,MF_BYCOMMAND);
		if (nState == MF_CHECKED)
		{
			pSub->CheckMenuItem(ID_TOOLBARINFO,MF_BYCOMMAND|MF_UNCHECKED);
			CControlBar* pBar = GetControlBar(ID_TOOLBARINFO);
			if (pBar != NULL)
			{
				ShowControlBar(pBar, (pBar->GetStyle() & WS_VISIBLE) == 0, FALSE);
			}
			RecalcLayout();
		}
		else if (nState == MF_UNCHECKED)
		{
			pSub->CheckMenuItem(ID_TOOLBARINFO,MF_BYCOMMAND|MF_CHECKED);
			CControlBar* pBar = GetControlBar(ID_TOOLBARINFO);
			if (pBar != NULL)
			{
				ShowControlBar(pBar, (pBar->GetStyle() & WS_VISIBLE) == 0, FALSE);
			}
			RecalcLayout();
		}
	}
}


void CMainFrame::OnTurnoff() 
{
	CMenu * pMenu = GetMenu();
	CMenu * pSub = pMenu->GetSubMenu(1);
	if (pSub != NULL)
	{
		int nState = pSub->GetMenuState(ID_TURNOFF,MF_BYCOMMAND);
		if (nState == MF_CHECKED)
		{
			pSub->CheckMenuItem(ID_TURNOFF,MF_BYCOMMAND|MF_UNCHECKED);
			m_bTurnOff = FALSE;

		}
		else if (nState == MF_UNCHECKED)
		{
			pSub->CheckMenuItem(ID_TURNOFF,MF_BYCOMMAND|MF_CHECKED);
			m_bTurnOff = TRUE;
		}
	}	
}

void CMainFrame::TurnOff()
{
	//更改权限
	HANDLE hToken;
	OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,&hToken);
	
	TOKEN_PRIVILEGES Privilege;

	LookupPrivilegeValue(NULL,"Seshutdownprivilege",&Privilege.Privileges[0].Luid );

	Privilege.PrivilegeCount = 1;
	Privilege.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	DWORD dwLen;
	AdjustTokenPrivileges(hToken,false,&Privilege,sizeof(TOKEN_PRIVILEGES),NULL,&dwLen);
	ExitWindowsEx(EWX_SHUTDOWN | EWX_POWEROFF,0);
}

void CMainFrame::OnUpdateToolbarinfo(CCmdUI* pCmdUI) 
{
	CControlBar* pBar = GetControlBar(pCmdUI->m_nID);
	if (pBar != NULL)
	{
		pCmdUI->SetCheck((pBar->GetStyle() & WS_VISIBLE) != 0);
		return;
	}
	pCmdUI->ContinueRouting();	
}



