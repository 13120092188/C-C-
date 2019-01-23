// Login.cpp : implementation file
//

#include "stdafx.h"
#include "ecsclient.h"
#include "Login.h"
#include "ClientSock.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogin dialog


CLogin::CLogin(CECSClientDlg * MainDlg ,CWnd* pParent /*=NULL*/)
	: CDialog(CLogin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLogin)
	//}}AFX_DATA_INIT
	m_pMainDlg = MainDlg;
	m_bConnect = FALSE;
}


void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogin)
	DDX_Control(pDX, IDC_PASSWORD, m_PassWord);
	DDX_Control(pDX, IDC_USERID, m_UserID);
	DDX_Control(pDX, IDC_SVRPORT, m_SvrPort);
	DDX_Control(pDX, IDC_SVRIP, m_SvrIP);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogin, CDialog)
	//{{AFX_MSG_MAP(CLogin)
	ON_BN_CLICKED(IDC_BT_CANCEL, OnBtCancel)
	ON_BN_CLICKED(IDC_BT_LOGIN, OnBtLogin)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogin message handlers

void CLogin::OnOK() 
{

}

void CLogin::OnBtCancel() 
{
	CDialog::OnCancel();	
}

BOOL CLogin::OnInitDialog() 
{
	CDialog::OnInitDialog();

	char chHostName[MAX_PATH] = {0};
	gethostname(chHostName,MAX_PATH);
	hostent *phost = gethostbyname(chHostName);
	char* chIP = inet_ntoa(*(in_addr*)phost->h_addr_list[0]);
	BOOL bRet = FALSE;
	m_pMainDlg->m_ClientSock.ShutDown();
	m_pMainDlg->m_ClientSock.Close();
	create:
		bRet = m_pMainDlg->m_ClientSock.Create(3000+rand()%2000,SOCK_STREAM,chIP);
	if (bRet==FALSE)
		goto create;
	
	BOOL bEnable = TRUE;
	m_pMainDlg->m_ClientSock.SetSockOpt(SO_OOBINLINE,&bEnable ,sizeof(BOOL));

	

	SetTimer(1,500,NULL);

	//读取Ini文件，判断是否为自动登录
	CECSClientApp *pApp = (CECSClientApp *)AfxGetApp();
	char chName[MAX_PATH] = {0};
	strcpy(chName,pApp->m_chFullPath);
	strcat(chName,"\\Config\\");
	//创建目录
	CreateDirectory(chName,NULL);
	strcat(chName,"Login.ini");	
	CFileFind flFind;
	if (flFind.FindFile(chName))
	{

		//读取Ini文件
		char csIP[MAX_PATH] = {0},csPort[MAX_PATH] ={0},csUserID[MAX_PATH] = {0},csPassword[MAX_PATH] = {0};
		GetPrivateProfileString("登录信息","自动登录","",csIP,MAX_PATH,chName);
		if (strcmp(csIP,"1")==0)	//自动登录
		{
			GetPrivateProfileString("登录信息","帐户ID","",csUserID,MAX_PATH,chName);	
		//	GetPrivateProfileString("登录信息","登录口令","",csPassword,MAX_PATH,chName);
			GetPrivateProfileString("登录信息","服务器IP","",csIP,MAX_PATH,chName);
			GetPrivateProfileString("登录信息","端口号","",csPort,MAX_PATH,chName);
			m_UserID.SetWindowText(csUserID);
			m_SvrIP.SetWindowText(csIP);
			m_SvrPort.SetWindowText(csPort);

			char chPass[MAX_PATH] = {0};
			DWORD dwLen = GetPrivateProfileString("登录信息","登录口令","",(char*)chPass,MAX_PATH,chName);
			m_PassWord.SetWindowText(chPass);
			CButton *pCheckBox = (CButton *)GetDlgItem(IDC_CHK_AUTOLOGIN);
			pCheckBox->SetCheck(1);
			OnBtLogin();
		}
	}
	return TRUE;  
}

DWORD __stdcall ThreadProc(  LPVOID lpParam)
{
	int nNum = 0;
	CLogin *pLogin = (CLogin *)lpParam;
	CString csIP,csPort,csUserID,csPassword;
	csIP = "192.168.1.23";
	csUserID = "1001";
	csPassword = "123";
	//m_SvrIP.GetWindowText(csIP);
//	pLogin->m_SvrPort.GetWindowText(csPort);
	csPort = "456";
	BOOL bRet = pLogin->m_pMainDlg->m_ClientSock.Create(3000+rand()%2000,SOCK_STREAM,csIP);

	bRet = pLogin->m_pMainDlg->m_ClientSock.Connect(csIP,atoi(csPort));	


	while(bRet==FALSE)
	{
		nNum++;
		if (nNum<8)
		{
			bRet = pLogin->m_pMainDlg->m_ClientSock.Connect(csIP,atoi(csPort));
		}
		else
		{
			pLogin->m_bConnect = FALSE;
			return 0;
		}
	}
	pLogin->m_bConnect = TRUE;
	//SetEvent(pLogin->m_hEvent);
	return 0;
}

//登录服务器
void CLogin::OnBtLogin() 
{
	if (m_pMainDlg != NULL)
	{
		CString csIP,csPort,csUserID,csPassword;
		m_SvrIP.GetWindowText(csIP);
		m_SvrPort.GetWindowText(csPort);
		m_UserID.GetWindowText(csUserID);
		m_PassWord.GetWindowText(csPassword);

		if (!csIP.IsEmpty() && !csPort.IsEmpty() && !csUserID.IsEmpty()
			                && !csPassword.IsEmpty())
		{
			m_pMainDlg->m_bLogined = FALSE;

			BOOL bRet = FALSE;		

			bRet = m_pMainDlg->m_ClientSock.Connect(csIP,atoi(csPort));	
			int nNum = 0;
			while(bRet==FALSE)
			{
				nNum++;
				bRet = m_pMainDlg->m_ClientSock.Connect(csIP,atoi(csPort));	
				MSG msg;
				if (GetMessage(&msg,m_hWnd,0,0))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				if (nNum > 20)
				{
					MessageBox("连接服务器超时!","提示");
					return;
				}
			}

			CMessage cmLoginInfo;
			strncpy(cmLoginInfo.m_chAccount,csUserID,csUserID.GetLength());

			strncpy(cmLoginInfo.m_chPassword,csPassword,csPassword.GetLength());
			cmLoginInfo.m_nMsgType = MT_FIRSTLOG;
			m_pMainDlg->m_nLoginUser = atoi(csUserID);
			m_pMainDlg->m_Password = csPassword;
			m_pMainDlg->m_nPort = atoi(csPort);
			m_pMainDlg->m_ServerIP = csIP;
			m_pMainDlg->m_ClientSock.Send(&cmLoginInfo,sizeof(CMessage));
		}
	}
}

void CLogin::OnTimer(UINT nIDEvent) 
{
	if (m_pMainDlg != NULL && m_pMainDlg->m_bLogined==TRUE)
	{
		KillTimer(1);
		//记录登录信息
		CECSClientApp *pApp = (CECSClientApp *)AfxGetApp();
		char chName[MAX_PATH] = {0};
		strcpy(chName,pApp->m_chFullPath);
		strcat(chName,"\\Config\\");
		//创建目录
		CreateDirectory(chName,NULL);
		strcat(chName,"Login.ini");
		CString csIP,csPort,csUserID,csPassword;
		m_SvrIP.GetWindowText(csIP);
		m_SvrPort.GetWindowText(csPort);
		m_UserID.GetWindowText(csUserID);
		m_PassWord.GetWindowText(csPassword);
		int nLen = csPassword.GetLength();

		WritePrivateProfileString("登录信息","帐户ID",csUserID,chName);
		WritePrivateProfileString("登录信息","登录口令",csPassword,chName);
		WritePrivateProfileString("登录信息","服务器IP",csIP,chName);
		WritePrivateProfileString("登录信息","端口号",csPort,chName);

		CButton *pCheckBox = (CButton *)GetDlgItem(IDC_CHK_AUTOLOGIN);
		int nState = 0;
		if (pCheckBox != NULL)
		{
			nState = pCheckBox->GetCheck();
		}
		CString csAutoLogin;
		csAutoLogin.Format("%d",nState);
		WritePrivateProfileString("登录信息","自动登录",csAutoLogin,chName);

		EndDialog(IDOK);
	}
	CDialog::OnTimer(nIDEvent);
}
