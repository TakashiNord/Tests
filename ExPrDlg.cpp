// ExPrDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ExPr.h"
#include "ExPrDlg.h"


#include "stdio.h"
#include <afxtempl.h>
#include <VECTOR>

using namespace std;

#include "shop.h"
#include "book.h"
#include "disks.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExPrDlg dialog

CExPrDlg::CExPrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExPrDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExPrDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExPrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExPrDlg)
	DDX_Control(pDX, IDC_LIST_CTRL, m_List);
	DDX_Control(pDX, IDC_TREE1, m_Tree);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExPrDlg, CDialog)
	//{{AFX_MSG_MAP(CExPrDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, OnSelchangedTree1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExPrDlg message handlers

BOOL CExPrDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
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

    CRect rect;
    m_List.GetClientRect(rect);

    // добавление в список просмотра 3х колонок, для реализации режима таблицы
    m_List.InsertColumn(0, _T("Название"),    LVCFMT_LEFT, rect.Width() / 3);
    m_List.InsertColumn(1, _T("Цена"),     LVCFMT_LEFT, rect.Width() / 9);
    m_List.InsertColumn(2, _T("Штрих-код"),     LVCFMT_LEFT, 2 * rect.Width() / 9);

    LONG lStyle = m_List.SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE);
    lStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES| LVS_EX_HEADERDRAGDROP;
    m_List.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)lStyle);
    m_List.SetExtendedStyle(lStyle);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CExPrDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CExPrDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CExPrDlg::OnCancel()
{
	// TODO: Add extra cleanup here

	CDialog::OnCancel();
}

void CExPrDlg::OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	MsgList() ;

	*pResult = 0;
}


void CExPrDlg::MsgList ( ) 
{
   HTREEITEM nodSelected = m_Tree.GetSelectedItem();
   if (nodSelected<0) { return ; }
	
   CString strSelected=m_Tree.GetItemText(nodSelected);
	
   HTREEITEM nodParent = m_Tree.GetParentItem(nodSelected);
   CString strParent = "" ;
   if (nodParent) {
      strParent=m_Tree.GetItemText(nodParent);
   }

   CRect rect;
   m_List.GetClientRect(rect);

   //int nColumnCount = m_List.GetHeaderCtrl()->GetItemCount();
   //for (int i=0;i < nColumnCount;i++)  m_List.DeleteColumn(0);
   while ( m_List.DeleteColumn (0));

   m_List.EnableWindow(TRUE);
   m_List.DeleteAllItems();
   m_List.SetRedraw(TRUE);
   m_List.Update(TRUE);

   m_List.InsertColumn(0, _T("Название"),    LVCFMT_LEFT, rect.Width() / 3);
   m_List.InsertColumn(1, _T("Цена"),     LVCFMT_LEFT, rect.Width() / 9);
   m_List.InsertColumn(2, _T("Штрих-код"),     LVCFMT_LEFT, 2 * rect.Width() / 9);
    
   
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
