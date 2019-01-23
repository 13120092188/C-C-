// FTPManageDoc.cpp : implementation of the CFTPManageDoc class
//

#include "stdafx.h"
#include "FTPManage.h"

#include "FTPManageDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFTPManageDoc

IMPLEMENT_DYNCREATE(CFTPManageDoc, CDocument)

BEGIN_MESSAGE_MAP(CFTPManageDoc, CDocument)
	//{{AFX_MSG_MAP(CFTPManageDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFTPManageDoc construction/destruction

CFTPManageDoc::CFTPManageDoc()
{
	// TODO: add one-time construction code here

}

CFTPManageDoc::~CFTPManageDoc()
{
}

BOOL CFTPManageDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFTPManageDoc serialization

void CFTPManageDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFTPManageDoc diagnostics

#ifdef _DEBUG
void CFTPManageDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFTPManageDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFTPManageDoc commands
