// myTreeView.cpp : implementation of the CMyTree class
//

#include "stdafx.h"
#include "Pr.h"

#include "PrDoc.h"
#include "myTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyTree

IMPLEMENT_DYNCREATE(CMyTree, CView)

BEGIN_MESSAGE_MAP(CMyTree, CView)
	//{{AFX_MSG_MAP(CMyTree)
	ON_WM_SIZE()
	ON_NOTIFY(TVN_SELCHANGED, TREE_ID, OnSelchangedTree1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTree construction/destruction

CMyTree::CMyTree()
{
	// TODO: add construction code here

}

CMyTree::~CMyTree()
{
}

BOOL CMyTree::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyTree drawing

void CMyTree::OnDraw(CDC* pDC)
{
	CPrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMyTree diagnostics

#ifdef _DEBUG
void CMyTree::AssertValid() const
{
	CView::AssertValid();
}

void CMyTree::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPrDoc* CMyTree::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPrDoc)));
	return (CPrDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyTree message handlers

void CMyTree::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType) 
{
	// TODO: Add your specialized code here and/or call the base class
	CView::CalcWindowRect(lpClientRect, nAdjustType);
	
	CRect rect=lpClientRect;
	m_Tree.MoveWindow(0,0,rect.Width()-4,rect.Height()-4);
}

BOOL CMyTree::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);

	dwStyle = WS_CHILD | WS_VISIBLE|TCS_BOTTOM|TVS_HASBUTTONS |TVS_HASLINES | TVS_LINESATROOT | WS_BORDER | WS_TABSTOP ;
	if (!m_Tree.Create(dwStyle,	rect,this,TREE_ID))
	{	
		AfxMessageBox("Error Create m_Tree"); 
		return FALSE;
	}

	HTREEITEM  shop=m_Tree.InsertItem(_T("Товары"));		// структура элемента дерево
	HTREEITEM  book=m_Tree.InsertItem(_T("Книги"),shop);		// структура элемента дерево
	HTREEITEM  disk=m_Tree.InsertItem(_T("Диски"),shop);	// структура элемента дерево
	HTREEITEM  disk1=m_Tree.InsertItem(_T("CD"),disk);	// структура элемента дерево
	HTREEITEM  disk2=m_Tree.InsertItem(_T("DVD"),disk);	// структура элемента дерево
	m_Tree.InsertItem(_T("Программирование"),book);			// добавить элемент
	m_Tree.InsertItem(_T("Кулинария"),book);			// добавить элемент
	m_Tree.InsertItem(_T("Эзотерика"),book);			// добавить элемент
	m_Tree.InsertItem(_T("Музыка"),disk1);				// добавить элемент
	m_Tree.InsertItem(_T("Видео"),disk1);				// добавить элемент
	m_Tree.InsertItem(_T("ПО"),disk1);			// добавить элемент
	m_Tree.InsertItem(_T("Музыка"),disk2);				// добавить элемент
	m_Tree.InsertItem(_T("Видео"),disk2);				// добавить элемент
	m_Tree.InsertItem(_T("ПО"),disk2);			// добавить элемент

	m_Tree.Expand(shop,TVE_EXPAND );
	m_Tree.Expand(book,TVE_EXPAND );
	m_Tree.Expand(disk,TVE_EXPAND );
	m_Tree.Expand(disk1,TVE_EXPAND );
	m_Tree.Expand(disk2,TVE_EXPAND );
	
	return TRUE ;
}

void CMyTree::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (IsWindow(m_Tree)) m_Tree.MoveWindow(0,0,cx,cy);
}

void CMyTree::OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
   HTREEITEM nodSelected = m_Tree.GetSelectedItem();
   if (nodSelected<0) { return ; }
	
   CString strSelected=m_Tree.GetItemText(nodSelected);
	
   HTREEITEM nodParent = m_Tree.GetParentItem(nodSelected);
   CString strParent = "" ;
   if (nodParent) {
      strParent=m_Tree.GetItemText(nodParent);
   }

   GetDocument()->SetTreeText(strParent,strSelected); // тут мы передадим наш параметр
   GetDocument()->UpdateAllViews(this);     // а тут скажем обновить все контролы

	*pResult = 0;
}


