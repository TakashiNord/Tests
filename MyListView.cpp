// MyList.cpp : implementation file
//

#include "stdafx.h"
#include "Pr.h"

#include <VECTOR>

using namespace std;

#include "shop.h"
#include "book.h"
#include "disks.h"

#include "PrDoc.h"
#include "MyListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyList

IMPLEMENT_DYNCREATE(CMyList, CView)

CMyList::CMyList()
{
}

CMyList::~CMyList()
{
}


BEGIN_MESSAGE_MAP(CMyList, CView)
	//{{AFX_MSG_MAP(CMyList)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyList drawing

void CMyList::OnDraw(CDC* pDC)
{
	//CDocument* pDoc = GetDocument();
	CPrDoc* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMyList diagnostics

#ifdef _DEBUG
void CMyList::AssertValid() const
{
	CView::AssertValid();
}

void CMyList::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}


CPrDoc* CMyList::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPrDoc)));
	return (CPrDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyList message handlers

BOOL CMyList::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CView::PreCreateWindow(cs);
}


void CMyList::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType) 
{
	// TODO: Add your specialized code here and/or call the base class
	CView::CalcWindowRect(lpClientRect, nAdjustType);

	CRect rect=lpClientRect;
	m_List.MoveWindow(0,0,rect.Width()-4,rect.Height()-4);

}

BOOL CMyList::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
   CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);

//Создаём таблицу, тут this - это указатель на родительское окно.
	dwStyle = WS_CHILD|WS_VISIBLE|WS_BORDER|WS_TABSTOP|LVS_REPORT|LVS_SINGLESEL ;
	if (!m_List.Create(dwStyle, CRect(0,0,0,0),this, LIST_ID))
	{
		AfxMessageBox("Error Create m_List"); 
		return FALSE;
	}
 //Указываем различные стили
   m_List.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_ONECLICKACTIVATE);

 //Добавляем колонки
   CRect rc;
   m_List.GetClientRect(rc);

 // добавление в список просмотра 3х колонок, для реализации режима таблицы
   m_List.InsertColumn(0, _T("Название"),    LVCFMT_LEFT, 100);
   m_List.InsertColumn(1, _T("Цена"),     LVCFMT_LEFT, 50);
   m_List.InsertColumn(2, _T("Штрих-код"),     LVCFMT_LEFT, 100);

	return TRUE;
}

void CMyList::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (IsWindow(m_List)) m_List.MoveWindow(0,0,cx,cy);
}

void CMyList::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
    CString szParent=GetDocument()->GetTreeParent();
    CString szSel=GetDocument()->GetTreeSel();

	if (szParent.IsEmpty() && szSel.IsEmpty()) return ;

	//AfxMessageBox( szParent + ' ' + szSel ) ;
	MsgList(szParent, szSel);
}

void CMyList::MsgList(CString strParent,CString strSelected)
{
   CRect rect;
   m_List.GetClientRect(rect);

   while ( m_List.DeleteColumn (0));

   m_List.EnableWindow(TRUE);
   m_List.DeleteAllItems();
   m_List.SetRedraw(TRUE);
   m_List.Update(TRUE);

   m_List.InsertColumn(0, _T("Название"),    LVCFMT_LEFT, rect.Width() / 3);
   m_List.InsertColumn(1, _T("Цена"),     LVCFMT_LEFT, rect.Width() / 9);
   m_List.InsertColumn(2, _T("Штрих-код"),     LVCFMT_LEFT, 2 * rect.Width() / 9);

 //m_List.InsertItem(1,"Строка 2, колонка 1");
 //m_List.SetItemText(1,1,"Строка 2, колонка 2");
   
   if (0==strSelected.CompareNoCase(_T("Книги"))) {

  	  m_List.InsertColumn(4, _T("Количество страниц"), LVCFMT_LEFT, rect.Width() / 3);

	  return ;
   }

   if (!strSelected.CompareNoCase(_T("Программирование"))) {

  	  m_List.InsertColumn(4, _T("Количество страниц"), LVCFMT_LEFT, rect.Width() / 3);
	  m_List.InsertColumn(5, _T("Язык программирования"), LVCFMT_LEFT, rect.Width() / 3);

	  int n = 10;
      vector <Book *> myBook(n);
	  myBook[0]=new Book(1,"Программирование С ", 0, "SDSdwere4355gf5",100, "С", "", 18 );
	  myBook[1]=new Book(1,"Программирование С++ ", 12.56, "e54rt355gf5",17, "C++", "", 18 );
	  myBook[2]=new Book(1,"Delphi", 1234, "APGpeHvH4JHUfBjrBZWR",150, "Object Pascal", "", 20 );
	  myBook[3]=new Book(1,"Основы Perl", 567, "daUR5VeNVgWQRt2JVDIa",50, "Perl", "", 23 );
	  myBook[4]=new Book(1,"Lua", 435.6, "I2iySPQQ2uQSZ08Q5P7M",34, "Lua", "", 25 );
	  myBook[5]=new Book(1,"Python", 33, "HeoXWUDZfNGaYwzJ5u6A",256, "Python", "", 26 );
	  myBook[6]=new Book(1,"Library Qt", 6578.5, "OkGfThFKHZUhxV71FthE",324, "C++", "", 30 );
	  
      LV_ITEM item;
      item.iItem = 0;
      item.iImage = 0;

	  CString csText;
	  for( int i = 0; i<myBook.size() ; i++) {

		if (myBook[i]==NULL) continue ;

        item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;

        // название
        item.iSubItem = 0;
        item.pszText = (LPTSTR)(LPCTSTR) myBook[i]->sName;
        m_List.InsertItem(&item);

        item.mask = LVIF_TEXT;

        // цена
        item.iSubItem = 1;
	    csText.Format(_T("%.2f"), myBook[i]->dPrice);
        item.pszText = (LPTSTR)(LPCTSTR)csText;
        m_List.SetItem(&item);

        // штрих-код
        item.iSubItem = 2;
        item.pszText = (LPTSTR)(LPCTSTR) myBook[i]->sDashcode ;
        m_List.SetItem(&item);

        // Количество страниц
        item.iSubItem = 3;
		csText.Format(_T("%d"), myBook[i]->nPages );
        item.pszText = (LPTSTR)(LPCTSTR)csText;
        m_List.SetItem(&item);

        // Язык программирования
        item.iSubItem = 4;
        item.pszText = (LPTSTR)(LPCTSTR) myBook[i]->sLang;
        m_List.SetItem(&item);

        item.iItem++;
	  }

	  for( i = 0; i<myBook.size() ; i++) if (myBook[i]!=NULL) delete myBook[i] ;
	  myBook.clear();
	  return ;
	} 
	

	if (0==strSelected.CompareNoCase(_T("Кулинария"))) {

  	  m_List.InsertColumn(4, _T("Количество страниц"), LVCFMT_LEFT, rect.Width() / 3);
	  m_List.InsertColumn(5, _T("Основной ингредиент"), LVCFMT_LEFT, rect.Width() / 3);

	  int n = 5;
      vector <Book *> myBook(n);
	  myBook[0]=new Book(2,"Как найти еду", 109, "RS2MSrZiq0WzqZ2IFeOj",453, "", "мясо", 33 );
	  myBook[1]=new Book(2,"Как приготовить еду", 568, "Enfvd5jpEHFslSRUotB0",2, "", "еда", 10 );
	  myBook[2]=new Book(2,"Как сьесть еду", 12, "qbku1xBJ3ZxGuq8vTjoA",1000, "", "пшеница", 18 );
	  myBook[3]=new Book(2,"Как переваривать еду", 689, "yIoxpO0y46USWyZtaswn",5, "", "хлеб", 40 );

      LV_ITEM item;
      item.iItem = 0;
      item.iImage = 0;

      CString csText;
	  for( int i = 0; i<myBook.size() ; i++) {

		 if (myBook[i]==NULL) continue ;

         item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;

         // название
         item.iSubItem = 0;
         item.pszText = (LPTSTR)(LPCTSTR) myBook[i]->sName;
         m_List.InsertItem(&item);

         item.mask = LVIF_TEXT;

         // цена
         item.iSubItem = 1;
		 csText.Format(_T("%.2f"), myBook[i]->dPrice);
         item.pszText = (LPTSTR)(LPCTSTR)csText;
         m_List.SetItem(&item);

         // штрих-код
         item.iSubItem = 2;
         item.pszText = (LPTSTR)(LPCTSTR) myBook[i]->sDashcode ;
         m_List.SetItem(&item);

         // Количество страниц
         item.iSubItem = 3;
		 csText.Format(_T("%d"), myBook[i]->nPages );
         item.pszText = (LPTSTR)(LPCTSTR)csText;
         m_List.SetItem(&item);

         // Основной ингредиент
         item.iSubItem = 4;
         item.pszText = (LPTSTR)(LPCTSTR) myBook[i]->sIngr ;
         m_List.SetItem(&item);

         item.iItem++;
		}

	  myBook.clear();
	  return ;
	}
	

	if (0==strSelected.CompareNoCase(_T("Эзотерика"))) {

  	  m_List.InsertColumn(4, _T("Количество страниц"), LVCFMT_LEFT, rect.Width() / 3);
	  m_List.InsertColumn(5, _T("Минимальный возраст"), LVCFMT_LEFT, rect.Width() / 3);

	  int n = 5;
      vector <Book *> myBook(n);
	  myBook[0]=new Book(3,"Буддизм Востока", 77, "l8ENJR4PMGMFVWdsiN8G",100, "", "", 15 );
	  myBook[1]=new Book(3,"Ислам и религии Востока", 0.6, "Katk4ImwmQZ2fCO0cocA",17, "", "", 15 );

      LV_ITEM item;
      item.iItem = 0;
      item.iImage = 0;

      CString csText;
	  for( int i = 0; i<myBook.size() ; i++) {

		 if (myBook[i]==NULL) continue ;

         item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;

         // название
         item.iSubItem = 0;
         item.pszText = (LPTSTR)(LPCTSTR) myBook[i]->sName;
         m_List.InsertItem(&item);

         item.mask = LVIF_TEXT;

         // цена
         item.iSubItem = 1;
		 csText.Format(_T("%.2f"), myBook[i]->dPrice);
         item.pszText = (LPTSTR)(LPCTSTR)csText;
         m_List.SetItem(&item);

         // штрих-код
         item.iSubItem = 2;
         item.pszText = (LPTSTR)(LPCTSTR) myBook[i]->sDashcode ;
         m_List.SetItem(&item);

         // Количество страниц
         item.iSubItem = 3;
		 csText.Format(_T("%d"), myBook[i]->nPages );
         item.pszText = (LPTSTR)(LPCTSTR)csText;
         m_List.SetItem(&item);

         // Минимальный возраст
         item.iSubItem = 4;
		 csText.Format(_T("R+%d"), myBook[i]->nAges );
         item.pszText = (LPTSTR)(LPCTSTR) csText ;
         m_List.SetItem(&item);

         item.iItem++;
		}

	  myBook.clear(); 
	  return ;

	} 


   if ((!strSelected.CompareNoCase(_T("Музыка"))) || 
  	    (!strSelected.CompareNoCase(_T("Видео"))) || 
		 (!strSelected.CompareNoCase(_T("ПО")))) {

    int n = 15;
    vector <Disks *> myDisk(n);
   
    myDisk[0]=new Disks(1,"Музыка","Анжелика Варум", 1, "Tq6Fzv865M8AR" );
    myDisk[1]=new Disks(1,"Музыка","ДДТ", 1.9, "Ko6bTsThMc3Mf");
   
    myDisk[2]=new Disks(1,"Видео","Чудеса в решете", 12, "T6tPUMtSVnxG7" );
    myDisk[3]=new Disks(1,"Видео","Пятница 13", 6, "9gzaQXOp4AQX9");
   
    myDisk[4]=new Disks(1,"ПО","Adobe", 50000, "tRE3Rp670dGmp" );
    myDisk[5]=new Disks(1,"ПО","MS Office", 10000, "wzUQsfQuH272z");

    myDisk[6]=new Disks(2,"Музыка","Челентано", 89, "qOw4y2l27LbYK" );
   
    myDisk[7]=new Disks(2,"Видео","Смешарики", 13, "p2xQJzsapieLA" );
	myDisk[8]=new Disks(2,"Видео","Спокойной Ночи, малыши", 0.3, "p243DDFreapieLA" );
   
    myDisk[9]=new Disks(2,"ПО","WinRar", 45.2, "SCYKoVFaf65kD");
	myDisk[10]=new Disks(2,"ПО","TC", 2.5, "12d3248af65kD");

	int iIndex = (0==strParent.CompareNoCase(_T("CD")))?1:2 ;

    LV_ITEM item;
    item.iItem = 0;
    item.iImage = 0;

    CString csText;
	for( int i = 0; i<myDisk.size() ; i++) {

	  if (myDisk[i]==NULL) continue ;

	  if ((myDisk[i]->iType!=iIndex) || 
		  (0!=strSelected.CompareNoCase(myDisk[i]->sType))) continue ;

      item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;

      // название
      item.iSubItem = 0;
      item.pszText = (LPTSTR)(LPCTSTR) myDisk[i]->sName;
      m_List.InsertItem(&item);

      item.mask = LVIF_TEXT;

	  // цена
      item.iSubItem = 1;
	  csText.Format(_T("%.2f"), myDisk[i]->dPrice);
      item.pszText = (LPTSTR)(LPCTSTR)csText;
      m_List.SetItem(&item);

      // штрих-код
      item.iSubItem = 2;
      item.pszText = (LPTSTR)(LPCTSTR) myDisk[i]->sDashcode ;
      m_List.SetItem(&item);

      item.iItem++;
	}
	
	for( i = 0; i<myDisk.size() ; i++) if (myDisk[i]!=NULL) delete myDisk[i] ;
	myDisk.clear();
	
	//csText.Format(_T("%d %d"), myDisk.size(), myDisk.capacity() );
	//AfxMessageBox(csText);

	return ;

   }


}
