// ExPrDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ExPr.h"
#include "ExPrDlg.h"


#include "stdio.h"
#include <afxtempl.h>

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
	HTREEITEM  shop=m_Tree.InsertItem("Товары");		// структура элемента дерево
	HTREEITEM  book=m_Tree.InsertItem("Книги",shop);		// структура элемента дерево
	HTREEITEM  disk=m_Tree.InsertItem("Диски",shop);	// структура элемента дерево
	HTREEITEM  disk1=m_Tree.InsertItem("CD",disk);	// структура элемента дерево
	HTREEITEM  disk2=m_Tree.InsertItem("DVD",disk);	// структура элемента дерево
	m_Tree.InsertItem("Программирование",book);			// добавить элемент
	m_Tree.InsertItem("Кулинария",book);			// добавить элемент
	m_Tree.InsertItem("Эзотерика",book);			// добавить элемент
	m_Tree.InsertItem("Музыка",disk1);				// добавить элемент
	m_Tree.InsertItem("Видео",disk1);				// добавить элемент
	m_Tree.InsertItem("ПО",disk1);			// добавить элемент
	m_Tree.InsertItem("Музыка",disk2);				// добавить элемент
	m_Tree.InsertItem("Видео",disk2);				// добавить элемент
	m_Tree.InsertItem("ПО",disk2);			// добавить элемент


    CRect rect;
    m_List.GetClientRect(rect);

    // добавление в спискок просмотра 3х колонок, для реализации режима таблицы
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

	HTREEITEM nodSelected = m_Tree.GetSelectedItem();

	HTREEITEM nodParent = m_Tree.GetParentItem(nodSelected);
	CString strParent = "" ;

	if (nodParent) {
      strParent=m_Tree.GetItemText(nodParent);
	}

    if (nodSelected<0) { *pResult = 0; return ; }


	CString strSelected=m_Tree.GetItemText(nodSelected);

    CRect rect;
    m_List.GetClientRect(rect);

	int nColumnCount = m_List.GetHeaderCtrl()->GetItemCount();

    if (0==strSelected.Compare("Книги")) {

     //while ( m_List.DeleteColumn (0));
	 for (int i=0;i < nColumnCount;i++)  m_List.DeleteColumn(0);

      m_List.EnableWindow(TRUE);
      m_List.DeleteAllItems();
	  m_List.SetRedraw(TRUE);
	  m_List.Update(TRUE);

	  m_List.InsertColumn(0, _T("Название"),    LVCFMT_LEFT, rect.Width() / 3);
      m_List.InsertColumn(1, _T("Цена"),     LVCFMT_LEFT, rect.Width() / 9);
      m_List.InsertColumn(2, _T("Штрих-код"),     LVCFMT_LEFT, 2 * rect.Width() / 9);
  	  m_List.InsertColumn(4, _T("Количество страниц"), LVCFMT_LEFT, rect.Width() / 3);

	} else if (!strSelected.Compare("Программирование")) {

	  while ( m_List.DeleteColumn (0));
	  //for (int i=0;i < nColumnCount;i++)  m_List.DeleteColumn(0);

      m_List.EnableWindow(TRUE);
      m_List.DeleteAllItems();
	  m_List.Update(TRUE);

	  m_List.InsertColumn(0, _T("Название"),    LVCFMT_LEFT, rect.Width() / 2);
      m_List.InsertColumn(1, _T("Цена"),     LVCFMT_LEFT, rect.Width() / 9);
      m_List.InsertColumn(2, _T("Штрих-код"),     LVCFMT_LEFT, 2 * rect.Width() / 9);
  	  m_List.InsertColumn(4, _T("Количество страниц"), LVCFMT_LEFT, rect.Width() / 3);
	  m_List.InsertColumn(5, _T("Язык программирования"), LVCFMT_LEFT, rect.Width() / 3);

	  CArray <Book,Book&> myBook ;

	  Book b1(1,"Программирование С (Сталин)", 0, "SDSdwere4355gf5",100, "Си", "", 18 );
	  myBook.Add(b1);
	  Book b2(1,"Программирование С++ (Ленин)", 12.56, "e54rt355gf5",17, "Си++", "", 18 );
	  myBook.Add(b2);
	  Book b3(1,"Delphi (Куйбышев)", 1234, "APGpeHvH4JHUfBjrBZWR",150, "Object Pascal", "", 20 );
	  myBook.Add(b3);
	  Book b4(1,"Основы Perl", 567, "daUR5VeNVgWQRt2JVDIa",50, "Perl", "", 23 );
	  myBook.Add(b4);
	  Book b5(1,"Радость на Tcl", 435.6, "I2iySPQQ2uQSZ08Q5P7M",34, "Tcl", "", 25 );
	  myBook.Add(b5);
	  Book b6(1,"Изврат Python", 33, "HeoXWUDZfNGaYwzJ5u6A",256, "Python", "", 26 );
	  myBook.Add(b6);
	  Book b7(1,"Как стать сумашедшим на AutoLisp", 6578.5, "OkGfThFKHZUhxV71FthE",324, "AutoLisp", "", 30 );
	  myBook.Add(b7);

      LV_ITEM item;
      item.iItem = 0;
      item.iImage = 0;

      CString csText;
	  for( int i = 0; i<myBook.GetSize() ; i++) {

        item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;

        // название
        item.iSubItem = 0;
        item.pszText = (LPTSTR)(LPCTSTR) myBook.GetAt(i).sName;
        m_List.InsertItem(&item);

        item.mask = LVIF_TEXT;

        // цена
        item.iSubItem = 1;
	    csText.Format(_T("%.2f"), myBook.GetAt(i).dPrice);
        item.pszText = (LPTSTR)(LPCTSTR)csText;
        m_List.SetItem(&item);

        // штрих-код
        item.iSubItem = 2;
        item.pszText = (LPTSTR)(LPCTSTR) myBook.GetAt(i).sDashcode ;
        m_List.SetItem(&item);

        // Количество страниц
        item.iSubItem = 3;
		csText.Format(_T("%d"), myBook.GetAt(i).nPages );
        item.pszText = (LPTSTR)(LPCTSTR)csText;
        m_List.SetItem(&item);

        // Язык программирования
        item.iSubItem = 4;
        item.pszText = (LPTSTR)(LPCTSTR) myBook.GetAt(i).sLang;
        m_List.SetItem(&item);

        item.iItem++;
	  }

	 } else if (!strSelected.Compare("Кулинария")) {

		while ( m_List.DeleteColumn (0));
		//for (int i=0;i < nColumnCount;i++)  m_List.DeleteColumn(0);

        m_List.EnableWindow(TRUE);
        m_List.DeleteAllItems();
		m_List.Update(TRUE);

		m_List.InsertColumn(0, _T("Название"),    LVCFMT_LEFT, rect.Width() / 3);
        m_List.InsertColumn(1, _T("Цена"),     LVCFMT_LEFT, rect.Width() / 9);
        m_List.InsertColumn(2, _T("Штрих-код"),     LVCFMT_LEFT, 2 * rect.Width() / 9);
  	    m_List.InsertColumn(4, _T("Количество страниц"), LVCFMT_LEFT, rect.Width() / 3);
		m_List.InsertColumn(5, _T("Основной ингредиент"), LVCFMT_LEFT, rect.Width() / 3);


		CArray <Book,Book&> myBook ;

		Book b1(2,"Пища холостяка", 23, "RS2MSrZiq0WzqZ2IFeOj",453, "", "пища", 33 );
		myBook.Add(b1);
		Book b2(2,"Как найти еду", 568, "Enfvd5jpEHFslSRUotB0",2, "", "еда", 10 );
		myBook.Add(b2);
		Book b3(2,"История водки", 12, "qbku1xBJ3ZxGuq8vTjoA",1000, "", "водка", 18 );
		myBook.Add(b3);
		Book b4(2,"Как готовить не умерев", 689, "yIoxpO0y46USWyZtaswn",5, "", "хлеб", 40 );
		myBook.Add(b4);

        LV_ITEM item;
        item.iItem = 0;
        item.iImage = 0;

        CString csText;
		for( int i = 0; i<myBook.GetSize() ; i++) {

         item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;

         // название
         item.iSubItem = 0;
         item.pszText = (LPTSTR)(LPCTSTR) myBook.GetAt(i).sName;
         m_List.InsertItem(&item);

         item.mask = LVIF_TEXT;

         // цена
         item.iSubItem = 1;
		 csText.Format(_T("%.2f"), myBook.GetAt(i).dPrice);
         item.pszText = (LPTSTR)(LPCTSTR)csText;
         m_List.SetItem(&item);

         // штрих-код
         item.iSubItem = 2;
         item.pszText = (LPTSTR)(LPCTSTR) myBook.GetAt(i).sDashcode ;
         m_List.SetItem(&item);

         // Количество страниц
         item.iSubItem = 3;
		 csText.Format(_T("%d"), myBook.GetAt(i).nPages );
         item.pszText = (LPTSTR)(LPCTSTR)csText;
         m_List.SetItem(&item);

         // Основной ингредиент
         item.iSubItem = 4;
         item.pszText = (LPTSTR)(LPCTSTR) myBook.GetAt(i).sIngr ;
         m_List.SetItem(&item);

         item.iItem++;
		}

	  } else if (!strSelected.Compare("Эзотерика")) {

		while ( m_List.DeleteColumn (0));
		//for (int i=0;i < nColumnCount;i++)  m_List.DeleteColumn(0);

        m_List.EnableWindow(TRUE);
        m_List.DeleteAllItems();
		m_List.Update(TRUE);

		m_List.InsertColumn(0, _T("Название"),    LVCFMT_LEFT, rect.Width() / 3);
        m_List.InsertColumn(1, _T("Цена"),     LVCFMT_LEFT, rect.Width() / 9);
        m_List.InsertColumn(2, _T("Штрих-код"),     LVCFMT_LEFT, 2 * rect.Width() / 9);
  	    m_List.InsertColumn(4, _T("Количество страниц"), LVCFMT_LEFT, rect.Width() / 3);
		m_List.InsertColumn(5, _T("Минимальный возраст"), LVCFMT_LEFT, rect.Width() / 3);

		CArray <Book,Book&> myBook ;

		Book b1(3,"История мира", 77, "l8ENJR4PMGMFVWdsiN8G",100, "", "", 15 );
		myBook.Add(b1);
		Book b2(3,"История России", 23489, "Katk4ImwmQZ2fCO0cocA",17, "", "", 15 );
		myBook.Add(b2);

        LV_ITEM item;
        item.iItem = 0;
        item.iImage = 0;

        CString csText;
		for( int i = 0; i<myBook.GetSize() ; i++) {

         item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;

         // название
         item.iSubItem = 0;
         item.pszText = (LPTSTR)(LPCTSTR) myBook.GetAt(i).sName;
         m_List.InsertItem(&item);

         item.mask = LVIF_TEXT;

         // цена
         item.iSubItem = 1;
		 csText.Format(_T("%.2f"), myBook.GetAt(i).dPrice);
         item.pszText = (LPTSTR)(LPCTSTR)csText;
         m_List.SetItem(&item);

         // штрих-код
         item.iSubItem = 2;
         item.pszText = (LPTSTR)(LPCTSTR) myBook.GetAt(i).sDashcode ;
         m_List.SetItem(&item);

         // Количество страниц
         item.iSubItem = 3;
		 csText.Format(_T("%d"), myBook.GetAt(i).nPages );
         item.pszText = (LPTSTR)(LPCTSTR)csText;
         m_List.SetItem(&item);

         // Минимальный возраст
         item.iSubItem = 4;
		 csText.Format(_T("R+%d"), myBook.GetAt(i).nAges );
         item.pszText = (LPTSTR)(LPCTSTR) csText ;
         m_List.SetItem(&item);

         item.iItem++;
		}

	  } else {

	   while ( m_List.DeleteColumn (0));

       m_List.EnableWindow(TRUE);
       m_List.DeleteAllItems();
	   m_List.Update(TRUE);

	   m_List.InsertColumn(0, _T("Название"),    LVCFMT_LEFT, rect.Width() / 3);
       m_List.InsertColumn(1, _T("Цена"),     LVCFMT_LEFT, rect.Width() / 9);
       m_List.InsertColumn(2, _T("Штрих-код"),     LVCFMT_LEFT, 2 * rect.Width() / 9);



	   typedef CArray < Disks,Disks& > CmyDisk ;
	   CmyDisk  myDisk1, myDisk ;

	   Disks d1(1,"Музыка","История мира", 75, "Tq6Fzv865M8AR" );
	   myDisk.Add(d1);
	   Disks d2(1,"Музыка","Привет с Магадана", 68.9, "Ko6bTsThMc3Mf");
	   myDisk.Add(d2);
	   Disks d3(1,"Видео","Новосибирск - ?", 4, "T6tPUMtSVnxG7" );
	   myDisk.Add(d3);
	   Disks d4(1,"Видео","Сахалин", 23, "9gzaQXOp4AQX9");
	   myDisk.Add(d4);
	   Disks d5(1,"ПО","Adobe", 50000, "tRE3Rp670dGmp" );
	   myDisk.Add(d5);
	   Disks d6(1,"ПО","MS Office", 10000, "wzUQsfQuH272z");
	   myDisk.Add(d6);

	   Disks d7(2,"Музыка","Рок-н-Ролл", 0, "qOw4y2l27LbYK" );
	   myDisk.Add(d7);
	   Disks d8(2,"Видео","Кровавый спорт", 11, "p2xQJzsapieLA" );
	   myDisk.Add(d8);
	   Disks d9(2,"ПО","AutoCad Revit", 146, "SCYKoVFaf65kD");
	   myDisk.Add(d9);

       if ((!strSelected.CompareNoCase(_T("Музыка"))) || 
	  	    (!strSelected.CompareNoCase(_T("Видео"))) || 
			 (!strSelected.CompareNoCase(_T("ПО")))) {

	    // Создаем срез
		int iIndex = (!strParent.CompareNoCase(_T("CD")))?1:2 ;
		for( int j = 0; j<myDisk.GetSize() ; j++) {
		 if ((myDisk.GetAt(j).iType==iIndex) && 
			 (!strSelected.CompareNoCase(myDisk.GetAt(j).sType))) myDisk1.Add(myDisk.GetAt(j));
		}

        LV_ITEM item;
        item.iItem = 0;
        item.iImage = 0;

        CString csText;
		for( int i = 0; i<myDisk1.GetSize() ; i++) {

         item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;

         // название
         item.iSubItem = 0;
         item.pszText = (LPTSTR)(LPCTSTR) myDisk1.GetAt(i).sName;
         m_List.InsertItem(&item);

         item.mask = LVIF_TEXT;

		 // цена
         item.iSubItem = 1;
		 csText.Format(_T("%.2f"), myDisk1.GetAt(i).dPrice);
         item.pszText = (LPTSTR)(LPCTSTR)csText;
         m_List.SetItem(&item);

         // штрих-код
         item.iSubItem = 2;
         item.pszText = (LPTSTR)(LPCTSTR) myDisk1.GetAt(i).sDashcode ;
         m_List.SetItem(&item);

         item.iItem++;
		}

	   }

	  }



	*pResult = 0;
}
