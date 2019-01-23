// LocalView.cpp : implementation file
//

#include "stdafx.h"
#include "ftpmanage.h"
#include "LocalView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLocalView

IMPLEMENT_DYNCREATE(CLocalView, CFormView)

CLocalView::CLocalView()
	: CFormView(CLocalView::IDD)
{
	//{{AFX_DATA_INIT(CLocalView)
	//}}AFX_DATA_INIT
	m_bSubClass = FALSE;
	m_bDrag = FALSE;
}

CLocalView::~CLocalView()
{
}

void CLocalView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLocalView)
	DDX_Control(pDX, IDC_FRAME, m_Frame);
	DDX_Control(pDX, IDC_LOCALFILES, m_LocalFiles);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLocalView, CFormView)
	//{{AFX_MSG_MAP(CLocalView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BACK, OnBack)
	ON_NOTIFY(LVN_BEGINDRAG, IDC_LOCALFILES, OnBegindragLocalfiles)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
		ON_CBN_SELCHANGE(112,DiskItemChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLocalView diagnostics

#ifdef _DEBUG
void CLocalView::AssertValid() const
{
	CFormView::AssertValid();
}

void CLocalView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLocalView message handlers

void CLocalView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	CRect ComBoxRC;
	m_Frame.GetWindowRect(ComBoxRC);
	m_Frame.ScreenToClient(ComBoxRC);
	m_Frame.MapWindowPoints(this,ComBoxRC);
	ComBoxRC.bottom = ComBoxRC.top+100;
	m_DiskList.Create(WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST|CBS_SORT,ComBoxRC,this,112);

	m_LocalFiles.SetExtendedStyle(LVS_EX_TWOCLICKACTIVATE|LVS_EX_FULLROWSELECT );
	m_LocalFiles.SetColumns(_T("文件名,150;文件大小,80;文件日期,150"));
	m_bSubClass = TRUE;
	
	GetSysFileImage();
	GetSysDisk();

	SIZE szWidth,szHeight;
	szWidth.cx = szWidth.cy = 0;
	szHeight.cx = szHeight.cy = 0;
	SetScrollSizes(MM_TEXT,szWidth,szHeight); 
}

void CLocalView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	if (m_bSubClass==TRUE)
	{
		CRect rc;
		GetClientRect(rc);
		rc.DeflateRect(0,40,0,0);
		m_LocalFiles.MoveWindow(rc);
	}		
}

void CLocalView::GetSysFileImage()
{
	CFTPManageApp *pApp = (CFTPManageApp*)AfxGetApp();
	m_DiskList.SetImageList(&pApp->m_ImageList);
	m_LocalFiles.SetImageList(&pApp->m_ImageList,LVSIL_SMALL);
}

void CLocalView::GetSysDisk()
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

void CLocalView::DiskItemChange()
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

void CLocalView::OnBack() 
{
	m_LocalFiles.SendMessage(WM_KEYDOWN,VK_BACK,0);
}

void CLocalView::OnBegindragLocalfiles(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
  	
	*pResult = 0;
	int nItem=pNMListView->iItem;
	POINT pt=pNMListView->ptAction;
	m_pDragList = m_LocalFiles.CreateDragImage(nItem,&pt);

	m_pDragList->BeginDrag(0,CPoint(0,0));
	m_pDragList->DragEnter(NULL,pt);
	SetCapture();
	m_bDrag = TRUE;
	*pResult = 0;
}

void CLocalView::OnMouseMove(UINT nFlags, CPoint point) 
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

void CLocalView::OnLButtonUp(UINT nFlags, CPoint point) 
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
		pDlg->m_pFtpView->m_RemoteFiles.GetWindowRect(&rect);
		ClientToScreen(&point);
		if(rect.PtInRect(point))
		{
			pDlg->OnUpload();
		}
	}	
	CFormView::OnLButtonUp(nFlags, point);
}
