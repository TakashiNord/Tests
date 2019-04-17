// PrView.cpp : implementation of the CPrView class
//

#include "stdafx.h"
#include "Pr.h"

#include "PrDoc.h"
#include "PrView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrView

IMPLEMENT_DYNCREATE(CPrView, CView)

BEGIN_MESSAGE_MAP(CPrView, CView)
	//{{AFX_MSG_MAP(CPrView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrView construction/destruction

CPrView::CPrView()
{
	// TODO: add construction code here

}

CPrView::~CPrView()
{
}

BOOL CPrView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPrView drawing

void CPrView::OnDraw(CDC* pDC)
{
	CPrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CPrView diagnostics

#ifdef _DEBUG
void CPrView::AssertValid() const
{
	CView::AssertValid();
}

void CPrView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPrDoc* CPrView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPrDoc)));
	return (CPrDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPrView message handlers
