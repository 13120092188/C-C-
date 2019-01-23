// LinkServer.cpp : implementation file
//

#include "stdafx.h"
#include "FTPManage.h"
#include "LinkServer.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
 
/////////////////////////////////////////////////////////////////////////////
// CLinkServer dialog

	

CLinkServer::CLinkServer(CWnd* pParent /*=NULL*/)
	: CDialog(CLinkServer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLinkServer)
	//}}AFX_DATA_INIT
	m_phThreads = NULL;
	m_dwStop = 0;
}


void CLinkServer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLinkServer)
	DDX_Control(pDX, IDC_TASKLIST, m_TastList);
	DDX_Control(pDX, IDC_REMOTEFILES, m_RemoteFiles);
	DDX_Control(pDX, IDC_LOCALFILES, m_LocalFiles);
	DDX_Control(pDX, IDC_FRAME, m_Frame);
	DDX_Control(pDX, IDC_FTPPORT, m_Port);
	DDX_Control(pDX, IDC_USER, m_User);
	DDX_Control(pDX, IDC_PASSWORD, m_Password);
	DDX_Control(pDX, IDC_FTPSERVER, m_FtpServer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLinkServer, CDialog)
	//{{AFX_MSG_MAP(CLinkServer)
	ON_BN_CLICKED(IDC_LOGIN_FTP, OnLoginFtp)
	ON_BN_CLICKED(IDC_UPLOAD, OnUpload)
	ON_BN_CLICKED(IDC_DOWNLOAD, OnDownload)
	ON_BN_CLICKED(IDC_BT_STOP, OnBtStop)
	ON_BN_CLICKED(IDC_BT_DELETE, OnBtDelete)
	ON_BN_CLICKED(IDC_BT_CONTINUE, OnBtContinue)
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(111,DiskItemChange)


END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLinkServer message handlers

void CLinkServer::OnOK() 
{

}

void CLinkServer::OnLoginFtp() 
{
	CString csServer,csPassword,csUser,csPort;
	m_FtpServer.GetWindowText(csServer);
	m_Password.GetWindowText(csPassword);
	m_User.GetWindowText(csUser);
	m_Port.GetWindowText(csPort);
	if ( !csServer.IsEmpty() && !csPassword.IsEmpty() &&
		 !csUser.IsEmpty() && !csPort.IsEmpty())
	{

			//CFtpConnection* pTemp = NULL;
			m_pFtp =  Session.GetFtpConnection(csServer,csUser,csPassword,atoi(csPort));
		//	m_pFtp =  Session.GetFtpConnection("192.168.1.23","sk","songkun",21);
			m_RemoteFiles.m_FtpServer = csServer;
			m_RemoteFiles.m_Port = csPort;
			m_RemoteFiles.m_User = csUser;
			m_RemoteFiles.m_Password = csPassword;
			CString csCurDir;
			m_pFtp->GetCurrentDirectory(csCurDir);
	
			m_RemoteFiles.m_BaseDir = csCurDir;
			m_RemoteFiles.DisplayPath("");
		//	m_pFtp->Close();
		//	Session.Close();
			delete m_pFtp;	
	}
}

BOOL CLinkServer::OnInitDialog() 
{
	CDialog::OnInitDialog();

	hMutex = CreateMutex(NULL,false,"mutex");

	CRect ComBoxRC;
	m_Frame.GetWindowRect(ComBoxRC);
	m_Frame.ScreenToClient(ComBoxRC);
	m_Frame.MapWindowPoints(this,ComBoxRC);
	ComBoxRC.bottom = ComBoxRC.top+100;
	m_DiskList.Create(WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST|CBS_SORT,ComBoxRC,this,111);

	m_LocalFiles.SetExtendedStyle(LVS_EX_TWOCLICKACTIVATE|LVS_EX_FULLROWSELECT );
	m_LocalFiles.SetHeadings(_T("文件名,150;文件大小,150;文件日期,150"));
	
	m_RemoteFiles.SetExtendedStyle(LVS_EX_TWOCLICKACTIVATE|LVS_EX_FULLROWSELECT );
	m_RemoteFiles.SetHeadings(_T("文件名,150;文件大小,150;文件日期,150"));

	GetSysFileImage();
	GetSysDisk();

	m_LocalFiles.LoadColumnInfo();
	m_RemoteFiles.LoadColumnInfo();
	m_RemoteFiles.m_nListType = 1;	//显示FTP服务器信息

	m_TastList.SetExtendedStyle(LVS_EX_TWOCLICKACTIVATE|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	

	m_TastList.InsertColumn(0,"任务名称",LVCFMT_LEFT,120);
	m_TastList.InsertColumn(1,"任务类型",LVCFMT_LEFT,80);
	m_TastList.InsertColumn(2,"主机信息",LVCFMT_LEFT,80);
	m_TastList.InsertColumn(3,"当前进度",LVCFMT_LEFT,120);
	m_TastList.InsertColumn(4,"状态",LVCFMT_LEFT,120);

	HMODULE hMod = LoadLibrary("Dbghelp.dll");
	MakeSureDirectoryPathExists = (funMakeSure *)GetProcAddress(hMod,"MakeSureDirectoryPathExists");

	m_FtpServer.SetWindowText("192.168.1.23");
	m_Port.SetWindowText("21");
	m_Password.SetWindowText("songkun");
	m_User.SetWindowText("sk");


	return TRUE; 
}

//获取系统文件类型图像列表
void CLinkServer::GetSysFileImage()
{
	CFTPManageApp *pApp = (CFTPManageApp*)AfxGetApp();
	m_DiskList.SetImageList(&pApp->m_ImageList);
	m_LocalFiles.SetImageList(&pApp->m_ImageList,LVSIL_SMALL);
	m_RemoteFiles.SetImageList(&pApp->m_ImageList,LVSIL_SMALL);
}

//获取系统磁盘
void CLinkServer::GetSysDisk()
{
	m_DiskList.ResetContent();
	char  pchDrives[128] = {0};
	char* pchDrive;
	GetLogicalDriveStrings( sizeof(pchDrives), pchDrives ) ;

	pchDrive = pchDrives;
	int nItem = 0;
	while( *pchDrive )
	{
		COMBOBOXEXITEM     cbi;
		CString            csText;
		cbi.mask = CBEIF_IMAGE | CBEIF_INDENT | CBEIF_OVERLAY |
			 CBEIF_SELECTEDIMAGE | CBEIF_TEXT;

		SHFILEINFO shInfo;
		int nIcon;
		SHGetFileInfo( pchDrive,0,&shInfo,sizeof(shInfo),SHGFI_ICON | SHGFI_SMALLICON );
		nIcon = shInfo.iIcon;

		cbi.iItem = nItem;
		cbi.pszText = pchDrive;
		cbi.cchTextMax = strlen(pchDrive);
		cbi.iImage = nIcon;
		cbi.iSelectedImage = nIcon;
		cbi.iOverlay = 0;
		cbi.iIndent = (0 & 0x03); 
		m_DiskList.InsertItem(&cbi);
		nItem ++;
		pchDrive += strlen( pchDrive ) + 1;
	}
}



void CLinkServer::OnCancel()
{	
	m_DiskImages.DeleteImageList();
	if (m_phThreads != NULL)
	{
		delete [] m_phThreads;
	}
	CDialog::OnCancel();
}

BOOL CLinkServer::PreTranslateMessage(MSG* pMsg) 
{
//	if (pMsg->message==CBN_SELCHANGE && pMsg->hwnd== m_DiskList.m_hWnd)
//	{
	//	DiskItemChange();
//	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CLinkServer::DiskItemChange()
{
	COMBOBOXEXITEM cbi;
	memset(&cbi,0,sizeof(COMBOBOXEXITEM));

	int nCurItem = m_DiskList.GetCurSel();
	cbi.mask =  CBEIF_TEXT;
	char chName[128] = {0};
	cbi.pszText = chName;
	cbi.cchTextMax = 128;
	cbi.iItem = nCurItem;
	m_DiskList.GetItem(&cbi);
	m_LocalFiles.m_BaseDir = chName;
	m_LocalFiles.DisplayPath(chName);

}

//上传文件的线程函数
DWORD __stdcall UploadThreadProc( LPVOID lpParameter)
{

	ThreadParam *Param = (ThreadParam *)lpParameter;
	CLinkServer * pDlg = Param->pDlg;
	int nItem = Param->nItem;

//	WaitForSingleObject(pDlg->hMutex,INFINITE);

	char downfile[MAX_PATH] = {0};
	strcpy(downfile,Param->m_DownFile);
	char relfile[MAX_PATH] = {0};
	strcpy(relfile,Param->m_RelativeFile);

	pDlg->m_TastList.SetItemText(nItem,4,"正在上传");

	if (Param->nDownFlag ==0)	//当前选择的是文件
	{	
		pDlg->UpLoadFile(pDlg,downfile,relfile,(DWORD)Param->m_hThread,true);
	}
	else if(Param->nDownFlag ==1)
	{
		pDlg->UpLoadFile(pDlg,downfile,relfile,(DWORD)Param->m_hThread,false);
	}
//	ReleaseMutex(pDlg->hMutex);


	if (pDlg->m_dwStop == (DWORD)Param->m_hThread)	//终止线程后设置初始标记
	{
		pDlg->m_dwStop = 0;
	}

//	DWORD dwData = pDlg->m_TastList.GetItemData(nItem);

//	if (dwData == (DWORD)Param->m_hThread)
//	{

		pDlg->m_TastList.SetItemText(nItem,3,"完成");
		pDlg->m_TastList.SetItemText(nItem,4,"上传完成");
//	}
		pDlg->DeleteItemFormData(&pDlg->m_TastList,(DWORD)Param->m_hThread);



	delete Param;
	return 0;
}


void CLinkServer::OnUpload() 
{
	POSITION pos = m_LocalFiles.GetFirstSelectedItemPosition();
	int nSelCount = m_LocalFiles.GetSelectedCount();

	while (pos != NULL)
	{
		int nItem = m_LocalFiles.GetNextSelectedItem(pos);

		LVITEM item;
		item.mask = LVIF_TEXT;
		item.cchTextMax = MAX_PATH;
		char text[MAX_PATH] = {0};
		item.pszText = text;
		item.iItem = nItem ;
		item.iSubItem = 0;
		m_LocalFiles.GetItem(&item);

		int nCount = m_TastList.GetItemCount();
		int nCurItem;
		nCurItem = m_TastList.InsertItem(nCount,"");
		
		m_TastList.SetItemData(nCurItem,nCurItem);

		m_TastList.SetItemText(nCurItem,0,text);
		m_TastList.SetItemText(nCurItem,1,"上传");
		m_TastList.SetItemText(nCurItem,4,"正在上传");

		ThreadParam * Param = new ThreadParam();
		Param->pDlg = this;
		Param->nItem = nCurItem;
		Param->nDownFlag =m_LocalFiles.GetItemData(nItem );

		memset(Param->m_DownFile,0,MAX_PATH);
		memset(Param->m_RelativeFile,0,MAX_PATH);

		strcpy(Param->m_DownFile, m_LocalFiles.m_CurDir);
		strcat(Param->m_DownFile,text);

		CString csRelative  = m_RemoteFiles.m_BaseDir;

		if (csRelative.Right(1) != "/" && csRelative.GetLength()>1)
			csRelative += "/";

		csRelative +=  m_RemoteFiles.m_CurDir;

		if (csRelative.Right(1) != "/" && csRelative.GetLength()>1)
			csRelative += "/";

		csRelative += text;

		strcpy(Param->m_RelativeFile,csRelative);

		HANDLE hHandle = CreateThread(NULL,0,UploadThreadProc,(void*)Param,0,NULL);
		m_TastList.SetItemData(nCurItem,(DWORD)hHandle);
		Param->m_hThread = hHandle;
	}
}


 void CLinkServer::DownLoadFile(CLinkServer * pDlg,LPCTSTR lpDir ,LPCTSTR csRelativePath, DWORD nFlag, BOOL	bIsFile)
{
//	CString csServer,csPassword,csUser,csPort;
//	m_FtpServer.GetWindowText(csServer);
//	m_Password.GetWindowText(csPassword);
//	m_User.GetWindowText(csUser);
//	m_Port.GetWindowText(csPort);

	CFtpConnection* pTemp = NULL;
//	pTemp =  Session.GetFtpConnection(csServer,csUser,csPassword,atoi(csPort));
//	CInternetSession Session;
	pTemp =  Session.GetFtpConnection("192.168.1.80","111","111",21);
	CFtpFileFind Find(pTemp);
	CString  filename;

	if (m_dwStop == nFlag)	//表示当前任务被挂起
	{
		pTemp->Close();
	//	Session.Close();
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
				//CString csdir = lpDir;
				strcat(csdir,"/");
				strcat(csdir,filename);
				//csdir += filename;
				strcpy(csRetPath,csRelativePath);
				strcat(csRetPath,"/");
				//csRelativePath +="/";
				strcat(csRetPath,filename);
				//csRelativePath += filename;

				DownLoadFile(pDlg,csdir,csRetPath,nFlag,false);
			}
			else 
			{
				char csUrl[MAX_PATH] = {0};
				//CString csUrl ;
				strcpy(csUrl,lpDir);
				strcat(csUrl,"/");
				strcat(csUrl,Find.GetFileName());
				//csUrl = lpDir + "/" + Find.GetFileName();
			
				filename = Find.GetFileName();
			
				CInternetFile* pFile = pTemp->OpenFile(csUrl ,GENERIC_READ,
													   INTERNET_FLAG_TRANSFER_BINARY|INTERNET_FLAG_RELOAD);
				if (pFile!=NULL)
				{
					DWORD dwLen = Find.GetLength();	//获取文件长度
					DWORD dwReadNum = 0;
					CFile file;
					//char csDir[MAX_PATH] = {0};
					//strcpy(csDir,csRelativePath);


					CString csDir = csRelativePath;

					csDir.Replace('/','\\');
					csDir = "j:" + csDir +"\\";
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
						//	Session.Close();
							delete pTemp;
							pFile->Close();
							file.Close();
							Find.Close();
							delete pFile;
							GlobalUnlock(hHeap);
							GlobalFree(hHeap);
						//	delete [] pBuffer;
							return;
						}

						nNum ++;
					//	memset(pBuffer,0,8192);
						UINT nFact = pFile->Read(pBuffer,8192);
						if (nFact > 0)
						{
							file.Write(pBuffer,nFact);
						}
						dwReadNum += nFact;
					}
				//	delete [] pBuffer;
				//	pBuffer = NULL;
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
			//CString csdir = lpDir;
			strcat(csdir,"/");
			//csdir += "/";
			strcat(csdir,filename);
			//csdir += filename;
			strcpy(csRetPath,csRelativePath);
			strcat(csRetPath,"/");
			//csRelativePath +="/";
			strcat(csRetPath,filename);
			//csRelativePath += filename;
			DownLoadFile(pDlg,csdir,csRetPath,nFlag,false);	
		}
		else
		{
			char csUrl[MAX_PATH] = {0};
			//CString csUrl ;

			if(bIsFile==FALSE)
			{
				strcpy(csUrl,lpDir);
				strcat(csUrl,"/");
				strcat(csUrl,Find.GetFileName());
			}
				//csUrl = lpDir + "/" + Find.GetFileName();
			else
			{
				strcpy(csUrl,lpDir);
			}
			//	csUrl = lpDir;
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
					csDir = "j:" + csDir;
					//先创建目录
					CString csPath;
					int nPos = csDir.ReverseFind('\\');
					csPath = csDir.Left(nPos+1);
					
					pDlg->MakeSureDirectoryPathExists(csPath);
				}
				else
				{
					csDir = "j:\\";
					csDir += csRelativePath;
				}
				//创建文件
				file.Open(csDir,CFile::modeCreate|CFile::modeWrite);



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
					//	delete [] pBuffer;
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
			///	delete [] pBuffer;
				pFile->Close();
				delete pFile;
				file.Close();
			}
		}
	}
	Find.Close();
	delete pTemp;
//	Session.Close();
}

//下载文件的线程函数
DWORD __stdcall DownloadThreadProc( LPVOID lpParameter)
{

	ThreadParam *Param = (ThreadParam *)lpParameter;
	CLinkServer * pDlg = Param->pDlg;
	int nItem = Param->nItem;

//	WaitForSingleObject(pDlg->hMutex,INFINITE);

	char downfile[MAX_PATH] = {0};
	strcpy(downfile,Param->m_DownFile);
	char relfile[MAX_PATH] = {0};
	strcpy(relfile,Param->m_RelativeFile);

	pDlg->m_TastList.SetItemText(nItem,4,"正在下载");

	if (Param->nDownFlag ==0)	//当前选择的是文件
	{	
		pDlg->DownLoadFile(pDlg,downfile,relfile,(DWORD)Param->m_hThread,true);
	}
	else if(Param->nDownFlag ==1)
	{
		pDlg->DownLoadFile(pDlg,downfile,relfile,(DWORD)Param->m_hThread,false);
	}
//	ReleaseMutex(pDlg->hMutex);


	pDlg->m_TastList.SetItemText(nItem,3,"完成");
	pDlg->m_TastList.SetItemText(nItem,4,"下载完成");

	if (pDlg->m_dwStop == (DWORD)Param->m_hThread)	//终止线程后设置初始标记
	{
		pDlg->m_dwStop = 0;
	}

	pDlg->DeleteItemFormData(&pDlg->m_TastList,(DWORD)Param->m_hThread);

	delete Param;
	return 0;
}








void CLinkServer::OnDownload() 
{
	POSITION pos = m_RemoteFiles.GetFirstSelectedItemPosition();
	int nSelCount = m_RemoteFiles.GetSelectedCount();

	while (pos != NULL)
	{
		int nItem = m_RemoteFiles.GetNextSelectedItem(pos);

		LVITEM item;
		item.mask = LVIF_TEXT;
		item.cchTextMax = MAX_PATH;
		char text[MAX_PATH] = {0};
		item.pszText = text;
		item.iItem = nItem ;
		item.iSubItem = 0;
		m_RemoteFiles.GetItem(&item);

		int nCount = m_TastList.GetItemCount();
		int nCurItem;
		nCurItem = m_TastList.InsertItem(nCount,"");
		
		m_TastList.SetItemData(nCurItem,nCurItem);

		m_TastList.SetItemText(nCurItem,0,text);
		m_TastList.SetItemText(nCurItem,1,"下载");
		m_TastList.SetItemText(nCurItem,4,"正在下载");

		ThreadParam * Param = new ThreadParam();
		Param->pDlg = this;
		Param->nItem = nCurItem;
		Param->nDownFlag =m_RemoteFiles.GetItemData(nItem );

		memset(Param->m_DownFile,0,MAX_PATH);
		memset(Param->m_RelativeFile,0,MAX_PATH);

		strcpy(Param->m_DownFile, m_RemoteFiles.m_CurDir);
		strcat(Param->m_DownFile,text);
		strcpy(Param->m_RelativeFile,text);

		HANDLE hHandle = CreateThread(NULL,0,DownloadThreadProc,(void*)Param,0,NULL);
		m_TastList.SetItemData(nCurItem,(DWORD)hHandle);
		Param->m_hThread = hHandle;

	}
}

void CLinkServer::DeleteItemFormData(CListCtrl *pCtrl, DWORD nData)
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

void CLinkServer::OnBtStop() 
{

	int nSel = m_TastList.GetSelectionMark();
	if (nSel != -1)
	{
		DWORD nItemData = m_TastList.GetItemData(nSel);
		CString csState = m_TastList.GetItemText(nSel,4);
		if (csState != "暂停")
		{
			SuspendThread((HANDLE)nItemData);
			m_TastList.SetItemText(nSel,4,"暂停");		
		}
	}

}

void CLinkServer::OnBtDelete() 
{
	int nSel = m_TastList.GetSelectionMark();
	if (nSel != -1)
	{
		DWORD nItemData = m_TastList.GetItemData(nSel);
		m_dwStop = nItemData;
	}

}

void CLinkServer::OnBtContinue() 
{
	int nSel = m_TastList.GetSelectionMark();
	if (nSel != -1)
	{
		DWORD nItemData = m_TastList.GetItemData(nSel);
		CString csType = m_TastList.GetItemText(nSel,1);
		ResumeThread((HANDLE)nItemData);
		if (csType=="下载")
		{
			m_TastList.SetItemText(nSel,4,"正在下载");
		}
		else
		{
			m_TastList.SetItemText(nSel,4,"正在上传");	
		}
	}	
}

void CLinkServer::UpLoadFile(CLinkServer *pDlg, LPCTSTR lpDir, LPCTSTR csRelativePath, DWORD nFlag, BOOL bIsFile)
{
//	CString csServer,csPassword,csUser,csPort;
//	m_FtpServer.GetWindowText(csServer);
//	m_Password.GetWindowText(csPassword);
//	m_User.GetWindowText(csUser);
//	m_Port.GetWindowText(csPort);

	CFtpConnection* pTemp = NULL;
//	pTemp =  Session.GetFtpConnection(csServer,csUser,csPassword,atoi(csPort));
	pTemp =  Session.GetFtpConnection("192.168.1.80","111","111",21);

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
				UpLoadFile(pDlg,csdir,csRetPath,nFlag,false);

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
					if (csTmpDir == "/mssdk/samples/Multimedia/DirectPlay")
					{
						int a = 10;
					}
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
			UpLoadFile(pDlg,csdir,csRetPath,nFlag,false);	
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
