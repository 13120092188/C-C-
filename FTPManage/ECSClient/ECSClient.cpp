// ECSClient.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ECSClient.h"
#include "ECSClientDlg.h"
#include "Login.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CECSClientApp

BEGIN_MESSAGE_MAP(CECSClientApp, CWinApp)
	//{{AFX_MSG_MAP(CECSClientApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!

	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CECSClientApp construction

CECSClientApp::CECSClientApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CECSClientApp object

CECSClientApp theApp;
HANDLE hMutex;
/////////////////////////////////////////////////////////////////////////////
// CECSClientApp initialization

BOOL CECSClientApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	char chFullName[MAX_PATH] = {0};
	//��ȡӦ�ó������ƣ�����·��
	GetModuleFileName(NULL,chFullName,MAX_PATH);
	char *pchFind = strrchr(chFullName,'\\');
	int nPos = pchFind - chFullName +1;
	strncpy(m_chFullPath,chFullName,nPos-1);

	hMutex = CreateMutex(NULL,FALSE,"RunClient");
	if (GetLastError()==ERROR_ALREADY_EXISTS)	//��һ��ʵ���Ѿ�����
	{
		return FALSE;
	}
	//��ʼ��COM��
	CoInitialize(NULL);
	//AfxOleInit();
	//��ʼ���׽���
	WSADATA wsd;
	WSAStartup(MAKEWORD(2,2),&wsd);
	//��ʼ��RichEditCtrl
	AfxInitRichEdit();
	CECSClientDlg dlg;
	dlg.Create(IDD_ECSCLIENT_DIALOG);
	m_pMainWnd = &dlg;
	dlg.ShowWindow(SW_HIDE);

	CLogin login(&dlg);
	if (login.DoModal()==IDCANCEL)
	{
		return FALSE;
	}

	dlg.ShowWindow(SW_SHOW);

	int nResponse = dlg.RunModalLoop();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
//	
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CECSClientApp::ExitInstance() 
{
	CloseHandle(hMutex);
	CoUninitialize();	
	return CWinApp::ExitInstance();
}
