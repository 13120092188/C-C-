// MontgomeryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Montgomery.h"
#include "MontgomeryDlg.h"
#include "mon.h"
#include "type.h"
#include "common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMontgomeryDlg dialog

CMontgomeryDlg::CMontgomeryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMontgomeryDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMontgomeryDlg)
	m_strA = _T("");
	m_strB = _T("");
	m_strM = _T("");
	m_strR = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMontgomeryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMontgomeryDlg)
	DDX_Text(pDX, IDC_EDIT1, m_strA);
	DDX_Text(pDX, IDC_EDIT2, m_strB);
	DDX_Text(pDX, IDC_EDIT3, m_strM);
	DDX_Text(pDX, IDC_EDIT4, m_strR);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMontgomeryDlg, CDialog)
	//{{AFX_MSG_MAP(CMontgomeryDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON9, OnInint)
	ON_BN_CLICKED(IDC_BUTTON1, OnAdd)
	ON_BN_CLICKED(IDC_BUTTON2, OnSub)
	ON_BN_CLICKED(IDC_BUTTON3, OnMul)
	ON_BN_CLICKED(IDC_BUTTON4, OnDiv)
	ON_BN_CLICKED(IDC_BUTTON5, OnMod)
	ON_BN_CLICKED(IDC_BUTTON6, OnModMul)
	ON_BN_CLICKED(IDC_BUTTON7, OnModExp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMontgomeryDlg message handlers

BOOL CMontgomeryDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMontgomeryDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMontgomeryDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMontgomeryDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMontgomeryDlg::OnInint() 
{
	// TODO: Add your control notification handler code here

	m_strA = "";
	m_strB = "";
	m_strM = "";
	m_strR = "";

	UpdateData(FALSE);
}

void CMontgomeryDlg::OnAdd() 
{
	// TODO: Add your control notification handler code here
	/************************************************************************/
	U32	pwA[BNLEN] = {0};
	U32 pwB[BNLEN] = {0};
	U32 pwR[BNLEN] = {0};
	S32 i = 0;
	S32 j = 0;
	S32 wordlen = 0;
	/************************************************************************/

	UpdateData(TRUE);
	m_strR = "";

	if (input(m_strA, pwA) == 1 && input(m_strB, pwB) == 1)
	{
		i = BN_GetWordLen(pwA);
		j = BN_GetWordLen(pwB);
		wordlen = i > j ? i : j;
		wordlen = BN_Add(pwA, pwB, pwR, wordlen);
		output(m_strR, pwR, wordlen);

	}
	else
	{
		m_strR = "输入有错误";
	}

	UpdateData(FALSE);

}

void CMontgomeryDlg::OnSub() 
{
	// TODO: Add your control notification handler code here
	/************************************************************************/
	U32	pwA[BNLEN] = {0};
	U32 pwB[BNLEN] = {0};
	U32 pwR[BNLEN] = {0};
	S32 i = 0;
	S32 j = 0;
	S32 wordlen = 0;
	/************************************************************************/
	UpdateData(TRUE);
    m_strR = "";

	if (input(m_strA, pwA) == 1 && input(m_strB, pwB) == 1)
	{
		i = BN_GetWordLen(pwA);
		j = BN_GetWordLen(pwB);
		wordlen = i > j ? i : j;

		if (BN_JE(pwA, pwB, wordlen) == 1 || BN_JE(pwA, pwB, wordlen) == 0)
		{
			BN_Sub(pwA, pwB, pwR, wordlen);
		}
		else
		{
			BN_Sub(pwB, pwA, pwR, wordlen);
			m_strR = "-";
		}

		output(m_strR, pwR, wordlen);
	
	}
	else
	{
		m_strR = "输入有错误";
	}
	
	UpdateData(FALSE);


	
}

void CMontgomeryDlg::OnMul() 
{
	// TODO: Add your control notification handler code here
	/************************************************************************/
	U32	pwA[BNLEN]     = {0};
	U32 pwB[BNLEN]     = {0};
	U32 pwR[2 * BNLEN] = {0};
	S32 i = 0;
	S32 j = 0;
	S32 wordlen = 0;
	/************************************************************************/
	UpdateData(TRUE);
	m_strR = "";

	if (input(m_strA, pwA) == 1 && input(m_strB, pwB) == 1)
	{
		i = BN_GetWordLen(pwA);
		j = BN_GetWordLen(pwB);
		wordlen = i > j ? i : j;

		BN_Mul(pwA, pwB, pwR, wordlen);
		wordlen = BN_GetWordLen(pwR, i + j);

		output(m_strR, pwR, wordlen);

	}
	else
	{
		m_strR = "输入有错误";
	}
	
	UpdateData(FALSE);
	


}

void CMontgomeryDlg::OnDiv() 
{
	// TODO: Add your control notification handler code here
	/************************************************************************/
	U32	pwA[2 * BNLEN] = {0};
	U32 pwB[BNLEN]     = {0};
	U32 pwR[BNLEN]     = {0};
	U32 pwT[BNLEN]     = {0};
	S32 i = 0;
//	S32 j = 0;
//	S32 wordlen = 0;
	/************************************************************************/
	UpdateData(TRUE);
	m_strR = "";

	if (input(m_strA, pwA) == 1 && input(m_strB, pwB) == 1)
	{
		BN_Div(pwA, pwB, pwR, pwT);
		i = BN_GetWordLen(pwR);

		output(m_strR, pwR, i);

	}
	else
	{
		m_strR = "输入有错误";
	}
	
	UpdateData(FALSE);
	
}

void CMontgomeryDlg::OnMod() 
{
	// TODO: Add your control notification handler code here
	/************************************************************************/
	U32	pwA[2 * BNLEN] = {0};
	U32 pwB[BNLEN]     = {0};
	U32 pwR[BNLEN]     = {0};
	U32 pwT[BNLEN]     = {0};
	S32 i = 0;
	/************************************************************************/
	UpdateData(TRUE);
	m_strR = "";

	if (input(m_strA, pwA) == 1 && input(m_strM, pwB) == 1)
	{
		BN_Div(pwA, pwB, pwT, pwR);
		i = BN_GetWordLen(pwR);
		
		output(m_strR, pwR, i);
		
	}
	else
	{
		m_strR = "输入有错误";
	}
	
	UpdateData(FALSE);
	
}

void CMontgomeryDlg::OnModMul() 
{
	// TODO: Add your control notification handler code here
	/************************************************************************/
	U32	pwA[2 * BNLEN] = {0};
	U32 pwB[BNLEN]     = {0};
	U32 pwR[BNLEN]     = {0};
	U32 pwT[BNLEN]     = {0};
	S32 i = 0;
	S32 j = 0;
	S32 wordlen = 0;
	/************************************************************************/
	UpdateData(TRUE);
	m_strR = "";

	if (input(m_strA, pwT) == 1 && input(m_strB, pwR) == 1 && input(m_strM, pwB) == 1)
	{
		i = BN_GetWordLen(pwT);
		j = BN_GetWordLen(pwR);
		wordlen = i > j ? i : j;
		BN_Mul(pwT, pwR, pwA, wordlen);

		memset(pwT, 0, sizeof(pwT));
		memset(pwR, 0, sizeof(pwR));
		
		BN_Div(pwA, pwB, pwT, pwR);

		wordlen = BN_GetWordLen(pwR);
		output(m_strR, pwR, wordlen);
		
	}
	else
	{
		m_strR = "输入有错误";
	}
	
	UpdateData(FALSE);
	
}

//这个函数不合格   太长了  
void CMontgomeryDlg::OnModExp() 
{
	// TODO: Add your control notification handler code here
	/************************************************************************/
	U32	pwA[BNLEN] = {0};
	U32 pwB[BNLEN]     = {0};
	U32 pwR[BNLEN]     = {0};
	U32 pwM[BNLEN]     = {0};
	/************************************************************************/
	UpdateData(TRUE);
	m_strR = "";

	if (input(m_strA, pwA) == 1 && input(m_strB, pwB) == 1 && input(m_strM, pwM) == 1)
	{
		if (BN_GetWordLen(pwM) == 0)
		{
			m_strR = "模不可以为0";
		}
		else if (BN_GetWordLen(pwB) == 0)
		{
			m_strR = "1";
		}
		else if ((pwM[0] & 0x1) == 1)
		{
			MonExp_odd(pwA, pwB, pwM, pwR);
		}
		else
		{
		//	m_strR = 

 		}

		output(m_strR, pwR, BNLEN);
	}
	else
	{
		m_strR = "输入有错误";
	}
	
	UpdateData(FALSE);
	
	
}
