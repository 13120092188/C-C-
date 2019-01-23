// PasswordDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCFileCompress.h"
#include "PasswordDlg.h"
#include "afxdialogex.h"

// CPasswordDlg 对话框

IMPLEMENT_DYNAMIC(CPasswordDlg, CDialogEx)

CPasswordDlg::CPasswordDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, strPassword(_T(""))
{

}

CPasswordDlg::~CPasswordDlg()
{
}

void CPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, strPassword);
	DDX_Control(pDX, IDOK, m_buttonsure);
	DDX_Control(pDX, IDCANCEL, m_buttoncancel);
}


BEGIN_MESSAGE_MAP(CPasswordDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_EDIT1, &CPasswordDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CPasswordDlg 消息处理程序


HBRUSH CPasswordDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CPasswordDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	//设置字体
	CEdit *m_Edit = (CEdit *)GetDlgItem(IDC_EDIT1);
	CFont* ptf = m_Edit->GetFont(); // 得到原来的字体    
	LOGFONT lf;
	ptf->GetLogFont(&lf);
	lf.lfHeight = 30; // 改变字体高度     
					  //strcpy (lf.lfFaceName, "隶书"); // 改变字体名称     
	m_font.CreateFontIndirect(&lf);
	m_Edit->SetFont(&m_font, FALSE);
	m_Edit->SetFont(&m_font);

	//为按钮贴图
	m_buttonsure.LoadBitmaps(IDB_BITMAP_BS1, IDB_BITMAP_BS2);
	m_buttoncancel.LoadBitmaps(IDB_BITMAP_BC1, IDB_BITMAP_BC2);

	//插入背景图片
	CRect   rect;
	GetClientRect(&rect);    //获取对话框长宽      
	CDC   dcBmp;             //定义并创建一个内存设备环境
	dcBmp.CreateCompatibleDC(&dc);             //创建兼容性DC
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP2);    //载入资源中图片
	BITMAP   m_bitmap;                         //图片变量               
	bmpBackground.GetBitmap(&m_bitmap);       //将图片载入位图中
											  //将位图选入临时内存设备环境
	CBitmap  *pbmpOld = dcBmp.SelectObject(&bmpBackground);
	//调用函数显示图片StretchBlt显示形状可变
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);

}


void CPasswordDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	
	// TODO:  在此添加控件通知处理程序代码
}
