// FTPManageView.cpp : implementation of the CFTPManageView class
//

#include "stdafx.h"
#include "FTPManage.h"

#include "FTPManageDoc.h"
#include "FTPManageView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFTPManageView

IMPLEMENT_DYNCREATE(CFTPManageView, CView)

BEGIN_MESSAGE_MAP(CFTPManageView, CView)
	//{{AFX_MSG_MAP(CFTPManageView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFTPManageView construction/destruction

CFTPManageView::CFTPManageView()
{
	// TODO: add construction code here

}

CFTPManageView::~CFTPManageView()
{
}

BOOL CFTPManageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFTPManageView drawing

void CFTPManageView::OnDraw(CDC* pDC)
{
	CFTPManageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	::SetWindowText(GetParent()->m_hWnd,"FTP管理工具");
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CFTPManageView printing

BOOL CFTPManageView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFTPManageView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFTPManageView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFTPManageView diagnostics

#ifdef _DEBUG
void CFTPManageView::AssertValid() const
{
	CView::AssertValid();
}

void CFTPManageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFTPManageDoc* CFTPManageView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFTPManageDoc)));
	return (CFTPManageDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFTPManageView message handlers
