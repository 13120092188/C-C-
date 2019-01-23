// TastList.cpp : implementation file
//

#include "stdafx.h"
#include "ftpmanage.h"
#include "TastList.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CTastListView, CFormView)

CTastListView::CTastListView()
	: CFormView(CTastListView::IDD)
{
	//{{AFX_DATA_INIT(CTastListView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bSubClass = FALSE;
}

CTastListView::~CTastListView()
{

}

void CTastListView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTastListView)
	DDX_Control(pDX, IDC_BT_CONTINUE, m_Continue);
	DDX_Control(pDX, IDC_BT_DELETE, m_Delete);
	DDX_Control(pDX, IDC_BT_STOP, m_Stop);
	DDX_Control(pDX, IDC_TASKLIST, m_TastList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTastListView, CFormView)
	//{{AFX_MSG_MAP(CTastListView)
	ON_BN_CLICKED(IDC_BT_CONTINUE, OnBtContinue)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BT_STOP, OnBtStop)
	ON_BN_CLICKED(IDC_BT_DELETE, OnBtDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTastListView diagnostics

#ifdef _DEBUG
void CTastListView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTastListView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTastListView message handlers

void CTastListView::OnBtContinue() 
{
	int nSel = m_TastList.GetSelectionMark();
	if (nSel != -1)
	{
		DWORD nItemData = m_TastList.GetItemData(nSel);
		CString csType = m_TastList.GetItemText(nSel,1);
		ResumeThread((HANDLE)nItemData);
		if (csType=="下载")
		{
			m_TastList.SetItemText(nSel,3,"正在下载");
		}
		else
		{
			m_TastList.SetItemText(nSel,3,"正在上传");	
		}
	}	
}

int CTastListView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;	
	return 0;
}

void CTastListView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	m_TastList.SetExtendedStyle(LVS_EX_TWOCLICKACTIVATE|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	m_TastList.InsertColumn(0,"任务名称",LVCFMT_LEFT,120);
	m_TastList.InsertColumn(1,"任务类型",LVCFMT_LEFT,80);
	m_TastList.InsertColumn(2,"主机信息",LVCFMT_LEFT,80);
	m_TastList.InsertColumn(3,"状态",LVCFMT_LEFT,120);	
	
	CRect rc;
	GetClientRect(rc);
	rc.DeflateRect(0,0,100,0);
	m_TastList.MoveWindow(rc);

	CRect btnRC;	//按钮显示区域
	btnRC.left = rc.right + 10;
	btnRC.right = btnRC.left + 80;
	btnRC.top = rc.top + 20;
	btnRC.bottom = btnRC.top + 20;
	btnRC.OffsetRect(0,30);

	m_Continue.MoveWindow(btnRC);
		btnRC.OffsetRect(0,30);
	m_Stop.MoveWindow(btnRC);
		btnRC.OffsetRect(0,30);
	m_Delete.MoveWindow(btnRC);
	m_bSubClass = TRUE;

	SIZE szWidth,szHeight;
	szWidth.cx = szWidth.cy = 0;
	szHeight.cx = szHeight.cy = 0;
	SetScrollSizes(MM_TEXT,szWidth,szHeight);
}

void CTastListView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	if (m_bSubClass==TRUE)
	{
		CRect rc;
		GetClientRect(rc);
		rc.DeflateRect(0,0,100,0);
		m_TastList.MoveWindow(rc);

		CRect btnRC;	//按钮显示区域
		btnRC.left = rc.right + 10;
		btnRC.right = btnRC.left + 80;
		btnRC.top = rc.top + 20;
		btnRC.bottom = btnRC.top + 20;

		btnRC.OffsetRect(0,10);
		m_Stop.MoveWindow(btnRC);

		btnRC.OffsetRect(0,30);
		m_Continue.MoveWindow(btnRC);

		btnRC.OffsetRect(0,30);
		m_Delete.MoveWindow(btnRC)	;
	}
}

void CTastListView::OnBtStop() 
{
	int nSel = m_TastList.GetSelectionMark();
	if (nSel != -1)
	{
		DWORD nItemData = m_TastList.GetItemData(nSel);
		CString csState = m_TastList.GetItemText(nSel,3);
		if (csState != "暂停")
		{
			SuspendThread((HANDLE)nItemData);
			m_TastList.SetItemText(nSel,3,"暂停");		
		}
	}	
}

void CTastListView::OnBtDelete() 
{
	int nSel = m_TastList.GetSelectionMark();
	if (nSel != -1)
	{
		DWORD nItemData = m_TastList.GetItemData(nSel);
		CMainFrame * pDlg = (CMainFrame*)AfxGetMainWnd();
		pDlg->m_dwStop = nItemData;
	}
}
