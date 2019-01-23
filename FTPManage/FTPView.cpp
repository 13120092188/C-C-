// FTPView.cpp : implementation file
//

#include "stdafx.h"
#include "ftpmanage.h"
#include "FTPView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFTPView

IMPLEMENT_DYNCREATE(CFTPView, CFormView)

CFTPView::CFTPView()
	: CFormView(CFTPView::IDD)
{
	//{{AFX_DATA_INIT(CFTPView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bSubClass = FALSE;
	m_bDrag = FALSE;
}

CFTPView::~CFTPView()
{
}

void CFTPView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFTPView)
	DDX_Control(pDX, IDC_REMOTEFILES, m_RemoteFiles);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFTPView, CFormView)
	//{{AFX_MSG_MAP(CFTPView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BACK, OnBack)
	ON_NOTIFY(LVN_BEGINDRAG, IDC_REMOTEFILES, OnBegindragRemotefiles)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFTPView diagnostics

#ifdef _DEBUG
void CFTPView::AssertValid() const
{
	CFormView::AssertValid();
}

void CFTPView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFTPView message handlers

void CFTPView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	if (m_bSubClass==TRUE)
	{
		CRect rc;
		GetClientRect(rc);
		rc.DeflateRect(0,40,0,0);
		m_RemoteFiles.MoveWindow(rc);
	}		
}

void CFTPView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	m_RemoteFiles.SetExtendedStyle(LVS_EX_TWOCLICKACTIVATE|LVS_EX_FULLROWSELECT );
	m_RemoteFiles.SetColumns(_T("文件名,150;文件大小,80;文件日期,150"));
	m_bSubClass = TRUE;
	GetSysFileImage();

	m_RemoteFiles.m_nListType = 1;	//显示FTP服务器信息

	SIZE szWidth,szHeight;
	szWidth.cx = szWidth.cy = 0;
	szHeight.cx = szHeight.cy = 0;
	SetScrollSizes(MM_TEXT,szWidth,szHeight);
	SendMessage(WM_SIZE,0,0);
}

void CFTPView::GetSysFileImage()
{
	CFTPManageApp *pApp = (CFTPManageApp*)AfxGetApp();
	m_RemoteFiles.SetImageList(&pApp->m_ImageList,LVSIL_SMALL);
}

void CFTPView::OnBack() 
{
	m_RemoteFiles.SendMessage(WM_KEYDOWN,VK_BACK,0);	
}

void CFTPView::OnBegindragRemotefiles(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	*pResult = 0;
	int nItem=pNMListView->iItem;
	POINT pt=pNMListView->ptAction;
	m_pDragList = m_RemoteFiles.CreateDragImage(nItem,&pt);

	m_pDragList->BeginDrag(0,CPoint(0,0));
	m_pDragList->DragEnter(NULL,pt);
	SetCapture();
	m_bDrag = TRUE;	
	*pResult = 0;
}

void CFTPView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_bDrag)
	{
		CRect rect;
		GetWindowRect(&rect);
		ClientToScreen(&point);
		m_pDragList->DragMove(point);		
	}	
	CFormView::OnMouseMove(nFlags, point);
}

void CFTPView::OnLButtonUp(UINT nFlags, CPoint point) 
{
    if(m_bDrag)
	{
		m_bDrag = FALSE;
		CImageList::DragLeave(NULL);
		CImageList::EndDrag();
		ReleaseCapture();
		delete m_pDragList;
		m_pDragList=NULL;
		CRect rect;
		CMainFrame * pDlg = (CMainFrame*)AfxGetMainWnd();
		pDlg->m_pLocalView->m_LocalFiles.GetWindowRect(&rect);
		ClientToScreen(&point);
		if(rect.PtInRect(point))
		{
			pDlg->OnDownload();
		}
	}	
	CFormView::OnLButtonUp(nFlags, point);
}

void CFTPView::OnDraw(CDC* pDC) 
{
	::SetWindowText(AfxGetMainWnd()->m_hWnd,"FTP管理工具");	
}
