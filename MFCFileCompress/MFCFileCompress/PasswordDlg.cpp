// PasswordDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCFileCompress.h"
#include "PasswordDlg.h"
#include "afxdialogex.h"

// CPasswordDlg �Ի���

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


// CPasswordDlg ��Ϣ�������


HBRUSH CPasswordDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CPasswordDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	//��������
	CEdit *m_Edit = (CEdit *)GetDlgItem(IDC_EDIT1);
	CFont* ptf = m_Edit->GetFont(); // �õ�ԭ��������    
	LOGFONT lf;
	ptf->GetLogFont(&lf);
	lf.lfHeight = 30; // �ı�����߶�     
					  //strcpy (lf.lfFaceName, "����"); // �ı���������     
	m_font.CreateFontIndirect(&lf);
	m_Edit->SetFont(&m_font, FALSE);
	m_Edit->SetFont(&m_font);

	//Ϊ��ť��ͼ
	m_buttonsure.LoadBitmaps(IDB_BITMAP_BS1, IDB_BITMAP_BS2);
	m_buttoncancel.LoadBitmaps(IDB_BITMAP_BC1, IDB_BITMAP_BC2);

	//���뱳��ͼƬ
	CRect   rect;
	GetClientRect(&rect);    //��ȡ�Ի��򳤿�      
	CDC   dcBmp;             //���岢����һ���ڴ��豸����
	dcBmp.CreateCompatibleDC(&dc);             //����������DC
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP2);    //������Դ��ͼƬ
	BITMAP   m_bitmap;                         //ͼƬ����               
	bmpBackground.GetBitmap(&m_bitmap);       //��ͼƬ����λͼ��
											  //��λͼѡ����ʱ�ڴ��豸����
	CBitmap  *pbmpOld = dcBmp.SelectObject(&bmpBackground);
	//���ú�����ʾͼƬStretchBlt��ʾ��״�ɱ�
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);

}


void CPasswordDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
