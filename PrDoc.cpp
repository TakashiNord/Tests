// PrDoc.cpp : implementation of the CPrDoc class
//

#include "stdafx.h"
#include "Pr.h"

#include "PrDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrDoc

IMPLEMENT_DYNCREATE(CPrDoc, CDocument)

BEGIN_MESSAGE_MAP(CPrDoc, CDocument)
	//{{AFX_MSG_MAP(CPrDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrDoc construction/destruction

CPrDoc::CPrDoc()
{
	// TODO: add one-time construction code here

}

CPrDoc::~CPrDoc()
{
}

BOOL CPrDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPrDoc serialization

void CPrDoc::Serialize(CArchive& ar)
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
// CPrDoc diagnostics

#ifdef _DEBUG
void CPrDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPrDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPrDoc commands
