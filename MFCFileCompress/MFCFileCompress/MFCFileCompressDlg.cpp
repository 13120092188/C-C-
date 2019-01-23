
// MFCFileCompressDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMFCFileCompressDlg �Ի���



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


// CMFCFileCompressDlg ��Ϣ�������

BOOL CMFCFileCompressDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//��������
	CEdit *m_Edit = (CEdit *)GetDlgItem(IDC_EDIT1);
	CFont* ptf = m_Edit->GetFont(); // �õ�ԭ��������    
	LOGFONT lf;
	ptf->GetLogFont(&lf);
	lf.lfHeight = 20; // �ı�����߶�     
					  //strcpy (lf.lfFaceName, "����"); // �ı���������     
	m_font.CreateFontIndirect(&lf);
	m_Edit->SetFont(&m_font, FALSE);
	m_Edit->SetFont(&m_font);

	//Ϊ��ť��ͼ
	m_buttoncc.LoadBitmaps(IDB_BITMAP_BCC1, IDB_BITMAP_BCC2);
	m_buttonec.LoadBitmaps(IDB_BITMAP_BEC1, IDB_BITMAP_BEC2);
	m_buttonuc.LoadBitmaps(IDB_BITMAP_BUC1, IDB_BITMAP_BUC2);
	m_buttoncf.LoadBitmaps(IDB_BITMAP_BCF1, IDB_BITMAP_BCF2);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCFileCompressDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		
		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//ע�͸���䣺��ֹ�ظ������ػ�����
		//CDialog::OnPaint(); 
		//��Ӵ���Ի��򱳾���ͼ
		CPaintDC   dc(this);
		CRect   rect;
		GetClientRect(&rect);    //��ȡ�Ի��򳤿�      
		CDC   dcBmp;             //���岢����һ���ڴ��豸����
		dcBmp.CreateCompatibleDC(&dc);             //����������DC
		CBitmap   bmpBackground;
		bmpBackground.LoadBitmap(IDB_BITMAP1);    //������Դ��ͼƬ
		BITMAP   m_bitmap;                         //ͼƬ����               
		bmpBackground.GetBitmap(&m_bitmap);       //��ͼƬ����λͼ��
												  //��λͼѡ����ʱ�ڴ��豸����
		CBitmap  *pbmpOld = dcBmp.SelectObject(&bmpBackground);
		//���ú�����ʾͼƬStretchBlt��ʾ��״�ɱ�
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCFileCompressDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCFileCompressDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCFileCompressDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: Add your control notification handler code here   
	// ���ù�����   
	TCHAR szFilter[] = _T("�����ļ�(*.*)|*.*||");
	// ������ļ��Ի���   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	//CString strFilePath;

	// ��ʾ���ļ��Ի���   
	if (IDOK == fileDlg.DoModal())
	{
		// ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����   
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT1, strFilePath);
	}
}


void CMFCFileCompressDlg::OnBnClickedButton2()//��ͨѹ����ť
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	FileCompress cps;
	USES_CONVERSION;
	std::string file(W2A(strFilePath));

	size_t i = 0;
	if (file.find("\\") == file.npos)
		AfxMessageBox(_T("��ѡ������Ҫѹ�����ļ���"));
	else {
		while ((i = file.find("\\", i)) != file.npos) {
			file = file.replace(file.find("\\", i), 1, "\\\\"); //�����е�'\'����˫'\'
			i += 4;
		}
		//std::thread task01(&FileCompress::thread0, cps, file.c_str());
		//task01.join();
		cps.Compress(file.c_str());
		m_EditCtrl_Ratio.SetWindowTextW(cps.GetWz_ratio());
	}
}

void CMFCFileCompressDlg::OnBnClickedButton3()//��ѹ��ť
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	FileCompress cps;
	USES_CONVERSION;
	std::string file(W2A(strFilePath));

	size_t i = 0;
	if (file.find("\\") == file.npos)
		AfxMessageBox(_T("��ѡ������Ҫ��ѹ���ļ���"));
	else {
		while ((i = file.find("\\", i)) != file.npos) {
				file = file.replace(file.find("\\", i), 1, "\\\\"); //�����е�'\'����˫'\'
				i += 4;
			}

		//std::thread task01(&FileCompress::thread1, cps, file.c_str());
		//task01.join();
		cps.UnCompress(file.c_str());
	}
	
}


void CMFCFileCompressDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
		FileCompress cps;
		USES_CONVERSION;
		std::string file(W2A(strFilePath));

		size_t i = 0;
		if (file.find("\\") == file.npos)
			AfxMessageBox(_T("��ѡ������Ҫѹ�����ļ���"));
		else {
			INT_PTR nRes;             // ���ڱ���DoModal�����ķ���ֵ   
			CPasswordDlg passwordDlg;           // ����Ի�����CPasswordDlg��ʵ��   
			nRes = passwordDlg.DoModal();  // �����Ի��� 
			USES_CONVERSION;
			std::string password(W2A(passwordDlg.strPassword));
			if (IDCANCEL != nRes) {
				cps.SetPassword(password);

				while ((i = file.find("\\", i)) != file.npos) {
					file = file.replace(file.find("\\", i), 1, "\\\\"); //�����е�'\'����˫'\'
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

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CMFCFileCompressDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
