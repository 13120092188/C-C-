
// MFCFileCompressDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCFileCompress.h"
#include "MFCFileCompressDlg.h"
#include "afxdialogex.h"
#include "FileCompress.h"
#include "PasswordDlg.h"
#include "resource.h"
#include <thread>  

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMFCFileCompressDlg 对话框



CMFCFileCompressDlg::CMFCFileCompressDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCFILECOMPRESS_DIALOG, pParent)
	, strFilePath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCFileCompressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, strFilePath);
	DDX_Control(pDX, IDC_EDIT1, m_EditCtrl_FilePath);
	//  DDX_Control(pDX, IDC_BUTTON1, m_buttoncc);
	DDX_Control(pDX, IDC_BUTTON1, m_buttoncf);
	DDX_Control(pDX, IDC_BUTTON2, m_buttoncc);
	DDX_Control(pDX, IDC_BUTTON4, m_buttonec);
	DDX_Control(pDX, IDC_BUTTON3, m_buttonuc);
	DDX_Control(pDX, IDC_EDIT2, m_EditCtrl_Ratio);
}

BEGIN_MESSAGE_MAP(CMFCFileCompressDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CMFCFileCompressDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCFileCompressDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCFileCompressDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCFileCompressDlg::OnBnClickedButton2)
	ON_WM_CTLCOLOR()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCFileCompressDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CMFCFileCompressDlg 消息处理程序

BOOL CMFCFileCompressDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//设置字体
	CEdit *m_Edit = (CEdit *)GetDlgItem(IDC_EDIT1);
	CFont* ptf = m_Edit->GetFont(); // 得到原来的字体    
	LOGFONT lf;
	ptf->GetLogFont(&lf);
	lf.lfHeight = 20; // 改变字体高度     
					  //strcpy (lf.lfFaceName, "隶书"); // 改变字体名称     
	m_font.CreateFontIndirect(&lf);
	m_Edit->SetFont(&m_font, FALSE);
	m_Edit->SetFont(&m_font);

	//为按钮贴图
	m_buttoncc.LoadBitmaps(IDB_BITMAP_BCC1, IDB_BITMAP_BCC2);
	m_buttonec.LoadBitmaps(IDB_BITMAP_BEC1, IDB_BITMAP_BEC2);
	m_buttonuc.LoadBitmaps(IDB_BITMAP_BUC1, IDB_BITMAP_BUC2);
	m_buttoncf.LoadBitmaps(IDB_BITMAP_BCF1, IDB_BITMAP_BCF2);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCFileCompressDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCFileCompressDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		
		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//注释该语句：防止重复调用重画函数
		//CDialog::OnPaint(); 
		//添加代码对话框背景贴图
		CPaintDC   dc(this);
		CRect   rect;
		GetClientRect(&rect);    //获取对话框长宽      
		CDC   dcBmp;             //定义并创建一个内存设备环境
		dcBmp.CreateCompatibleDC(&dc);             //创建兼容性DC
		CBitmap   bmpBackground;
		bmpBackground.LoadBitmap(IDB_BITMAP1);    //载入资源中图片
		BITMAP   m_bitmap;                         //图片变量               
		bmpBackground.GetBitmap(&m_bitmap);       //将图片载入位图中
												  //将位图选入临时内存设备环境
		CBitmap  *pbmpOld = dcBmp.SelectObject(&bmpBackground);
		//调用函数显示图片StretchBlt显示形状可变
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCFileCompressDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCFileCompressDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCFileCompressDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: Add your control notification handler code here   
	// 设置过滤器   
	TCHAR szFilter[] = _T("所有文件(*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	//CString strFilePath;

	// 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT1, strFilePath);
	}
}


void CMFCFileCompressDlg::OnBnClickedButton2()//普通压缩按钮
{
	// TODO: 在此添加控件通知处理程序代码
	FileCompress cps;
	USES_CONVERSION;
	std::string file(W2A(strFilePath));

	size_t i = 0;
	if (file.find("\\") == file.npos)
		AfxMessageBox(_T("请选择您将要压缩的文件！"));
	else {
		while ((i = file.find("\\", i)) != file.npos) {
			file = file.replace(file.find("\\", i), 1, "\\\\"); //将所有单'\'换成双'\'
			i += 4;
		}
		//std::thread task01(&FileCompress::thread0, cps, file.c_str());
		//task01.join();
		cps.Compress(file.c_str());
		m_EditCtrl_Ratio.SetWindowTextW(cps.GetWz_ratio());
	}
}

void CMFCFileCompressDlg::OnBnClickedButton3()//解压按钮
{
	// TODO: 在此添加控件通知处理程序代码
	FileCompress cps;
	USES_CONVERSION;
	std::string file(W2A(strFilePath));

	size_t i = 0;
	if (file.find("\\") == file.npos)
		AfxMessageBox(_T("请选择您将要解压的文件！"));
	else {
		while ((i = file.find("\\", i)) != file.npos) {
				file = file.replace(file.find("\\", i), 1, "\\\\"); //将所有单'\'换成双'\'
				i += 4;
			}

		//std::thread task01(&FileCompress::thread1, cps, file.c_str());
		//task01.join();
		cps.UnCompress(file.c_str());
	}
	
}


void CMFCFileCompressDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	
		FileCompress cps;
		USES_CONVERSION;
		std::string file(W2A(strFilePath));

		size_t i = 0;
		if (file.find("\\") == file.npos)
			AfxMessageBox(_T("请选择您将要压缩的文件！"));
		else {
			INT_PTR nRes;             // 用于保存DoModal函数的返回值   
			CPasswordDlg passwordDlg;           // 构造对话框类CPasswordDlg的实例   
			nRes = passwordDlg.DoModal();  // 弹出对话框 
			USES_CONVERSION;
			std::string password(W2A(passwordDlg.strPassword));
			if (IDCANCEL != nRes) {
				cps.SetPassword(password);

				while ((i = file.find("\\", i)) != file.npos) {
					file = file.replace(file.find("\\", i), 1, "\\\\"); //将所有单'\'换成双'\'
					i += 4;
				}
				//std::thread task01(&FileCompress::thread0, cps, file.c_str());
				//task01.join();
				cps.Compress(file.c_str());
				m_EditCtrl_Ratio.SetWindowTextW(cps.GetWz_ratio());
			}
		}
	
}

HBRUSH CMFCFileCompressDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CMFCFileCompressDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	wchar_t filepath[MAX_PATH] = { 0 };
	if (DragQueryFile(hDropInfo, 0, filepath, MAX_PATH)>0)
	{
		m_EditCtrl_FilePath.SetWindowTextW(filepath);
		strFilePath = filepath;
	}
	CDialogEx::OnDropFiles(hDropInfo);
	USES_CONVERSION;
	std::string Suffix(W2A(strFilePath));
	Suffix = Suffix.substr(Suffix.find(".") + 1, 2);
	if (0 == Suffix.compare("xy"))
		CMFCFileCompressDlg::OnBnClickedButton3();
}




void CAboutDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
