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
	HTREEITEM  shop=m_Tree.InsertItem("������");		// ��������� �������� ������
	HTREEITEM  book=m_Tree.InsertItem("�����",shop);		// ��������� �������� ������
	HTREEITEM  disk=m_Tree.InsertItem("�����",shop);	// ��������� �������� ������
	HTREEITEM  disk1=m_Tree.InsertItem("CD",disk);	// ��������� �������� ������
	HTREEITEM  disk2=m_Tree.InsertItem("DVD",disk);	// ��������� �������� ������
	m_Tree.InsertItem("����������������",book);			// �������� �������
	m_Tree.InsertItem("���������",book);			// �������� �������
	m_Tree.InsertItem("���������",book);			// �������� �������
	m_Tree.InsertItem("������",disk1);				// �������� �������
	m_Tree.InsertItem("�����",disk1);				// �������� �������
	m_Tree.InsertItem("��",disk1);			// �������� �������
	m_Tree.InsertItem("������",disk2);				// �������� �������
	m_Tree.InsertItem("�����",disk2);				// �������� �������
	m_Tree.InsertItem("��",disk2);			// �������� �������


    CRect rect;
    m_List.GetClientRect(rect);

    // ���������� � ������� ��������� 3� �������, ��� ���������� ������ �������
    m_List.InsertColumn(0, _T("��������"),    LVCFMT_LEFT, rect.Width() / 3);
    m_List.InsertColumn(1, _T("����"),     LVCFMT_LEFT, rect.Width() / 9);
    m_List.InsertColumn(2, _T("�����-���"),     LVCFMT_LEFT, 2 * rect.Width() / 9);

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

    if (0==strSelected.Compare("�����")) {

     //while ( m_List.DeleteColumn (0));
	 for (int i=0;i < nColumnCount;i++)  m_List.DeleteColumn(0);

      m_List.EnableWindow(TRUE);
      m_List.DeleteAllItems();
	  m_List.SetRedraw(TRUE);
	  m_List.Update(TRUE);

	  m_List.InsertColumn(0, _T("��������"),    LVCFMT_LEFT, rect.Width() / 3);
      m_List.InsertColumn(1, _T("����"),     LVCFMT_LEFT, rect.Width() / 9);
      m_List.InsertColumn(2, _T("�����-���"),     LVCFMT_LEFT, 2 * rect.Width() / 9);
  	  m_List.InsertColumn(4, _T("���������� �������"), LVCFMT_LEFT, rect.Width() / 3);

	} else if (!strSelected.Compare("����������������")) {

	  while ( m_List.DeleteColumn (0));
	  //for (int i=0;i < nColumnCount;i++)  m_List.DeleteColumn(0);

      m_List.EnableWindow(TRUE);
      m_List.DeleteAllItems();
	  m_List.Update(TRUE);

	  m_List.InsertColumn(0, _T("��������"),    LVCFMT_LEFT, rect.Width() / 2);
      m_List.InsertColumn(1, _T("����"),     LVCFMT_LEFT, rect.Width() / 9);
      m_List.InsertColumn(2, _T("�����-���"),     LVCFMT_LEFT, 2 * rect.Width() / 9);
  	  m_List.InsertColumn(4, _T("���������� �������"), LVCFMT_LEFT, rect.Width() / 3);
	  m_List.InsertColumn(5, _T("���� ����������������"), LVCFMT_LEFT, rect.Width() / 3);

	  CArray <Book,Book&> myBook ;

	  Book b1(1,"���������������� � (������)", 0, "SDSdwere4355gf5",100, "��", "", 18 );
	  myBook.Add(b1);
	  Book b2(1,"���������������� �++ (�����)", 12.56, "e54rt355gf5",17, "��++", "", 18 );
	  myBook.Add(b2);
	  Book b3(1,"Delphi (��������)", 1234, "APGpeHvH4JHUfBjrBZWR",150, "Object Pascal", "", 20 );
	  myBook.Add(b3);
	  Book b4(1,"������ Perl", 567, "daUR5VeNVgWQRt2JVDIa",50, "Perl", "", 23 );
	  myBook.Add(b4);
	  Book b5(1,"������� �� Tcl", 435.6, "I2iySPQQ2uQSZ08Q5P7M",34, "Tcl", "", 25 );
	  myBook.Add(b5);
	  Book b6(1,"������ Python", 33, "HeoXWUDZfNGaYwzJ5u6A",256, "Python", "", 26 );
	  myBook.Add(b6);
	  Book b7(1,"��� ����� ���������� �� AutoLisp", 6578.5, "OkGfThFKHZUhxV71FthE",324, "AutoLisp", "", 30 );
	  myBook.Add(b7);

      LV_ITEM item;
      item.iItem = 0;
      item.iImage = 0;

      CString csText;
	  for( int i = 0; i<myBook.GetSize() ; i++) {

        item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;

        // ��������
        item.iSubItem = 0;
        item.pszText = (LPTSTR)(LPCTSTR) myBook.GetAt(i).sName;
        m_List.InsertItem(&item);

        item.mask = LVIF_TEXT;

        // ����
        item.iSubItem = 1;
	    csText.Format(_T("%.2f"), myBook.GetAt(i).dPrice);
        item.pszText = (LPTSTR)(LPCTSTR)csText;
        m_List.SetItem(&item);

        // �����-���
        item.iSubItem = 2;
        item.pszText = (LPTSTR)(LPCTSTR) myBook.GetAt(i).sDashcode ;
        m_List.SetItem(&item);

        // ���������� �������
        item.iSubItem = 3;
		csText.Format(_T("%d"), myBook.GetAt(i).nPages );
        item.pszText = (LPTSTR)(LPCTSTR)csText;
        m_List.SetItem(&item);

        // ���� ����������������
        item.iSubItem = 4;
        item.pszText = (LPTSTR)(LPCTSTR) myBook.GetAt(i).sLang;
        m_List.SetItem(&item);

        item.iItem++;
	  }

	 } else if (!strSelected.Compare("���������")) {

		while ( m_List.DeleteColumn (0));
		//for (int i=0;i < nColumnCount;i++)  m_List.DeleteColumn(0);

        m_List.EnableWindow(TRUE);
        m_List.DeleteAllItems();
		m_List.Update(TRUE);

		m_List.InsertColumn(0, _T("��������"),    LVCFMT_LEFT, rect.Width() / 3);
        m_List.InsertColumn(1, _T("����"),     LVCFMT_LEFT, rect.Width() / 9);
        m_List.InsertColumn(2, _T("�����-���"),     LVCFMT_LEFT, 2 * rect.Width() / 9);
  	    m_List.InsertColumn(4, _T("���������� �������"), LVCFMT_LEFT, rect.Width() / 3);
		m_List.InsertColumn(5, _T("�������� ����������"), LVCFMT_LEFT, rect.Width() / 3);


		CArray <Book,Book&> myBook ;

		Book b1(2,"���� ���������", 23, "RS2MSrZiq0WzqZ2IFeOj",453, "", "����", 33 );
		myBook.Add(b1);
		Book b2(2,"��� ����� ���", 568, "Enfvd5jpEHFslSRUotB0",2, "", "���", 10 );
		myBook.Add(b2);
		Book b3(2,"������� �����", 12, "qbku1xBJ3ZxGuq8vTjoA",1000, "", "�����", 18 );
		myBook.Add(b3);
		Book b4(2,"��� �������� �� ������", 689, "yIoxpO0y46USWyZtaswn",5, "", "����", 40 );
		myBook.Add(b4);

        LV_ITEM item;
        item.iItem = 0;
        item.iImage = 0;

        CString csText;
		for( int i = 0; i<myBook.GetSize() ; i++) {

         item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;

         // ��������
         item.iSubItem = 0;
         item.pszText = (LPTSTR)(LPCTSTR) myBook.GetAt(i).sName;
         m_List.InsertItem(&item);

         item.mask = LVIF_TEXT;

         // ����
         item.iSubItem = 1;
		 csText.Format(_T("%.2f"), myBook.GetAt(i).dPrice);
         item.pszText = (LPTSTR)(LPCTSTR)csText;
         m_List.SetItem(&item);

         // �����-���
         item.iSubItem = 2;
         item.pszText = (LPTSTR)(LPCTSTR) myBook.GetAt(i).sDashcode ;
         m_List.SetItem(&item);

         // ���������� �������
         item.iSubItem = 3;
		 csText.Format(_T("%d"), myBook.GetAt(i).nPages );
         item.pszText = (LPTSTR)(LPCTSTR)csText;
         m_List.SetItem(&item);

         // �������� ����������
         item.iSubItem = 4;
         item.pszText = (LPTSTR)(LPCTSTR) myBook.GetAt(i).sIngr ;
         m_List.SetItem(&item);

         item.iItem++;
		}

	  } else if (!strSelected.Compare("���������")) {

		while ( m_List.DeleteColumn (0));
		//for (int i=0;i < nColumnCount;i++)  m_List.DeleteColumn(0);

        m_List.EnableWindow(TRUE);
        m_List.DeleteAllItems();
		m_List.Update(TRUE);

		m_List.InsertColumn(0, _T("��������"),    LVCFMT_LEFT, rect.Width() / 3);
        m_List.InsertColumn(1, _T("����"),     LVCFMT_LEFT, rect.Width() / 9);
        m_List.InsertColumn(2, _T("�����-���"),     LVCFMT_LEFT, 2 * rect.Width() / 9);
  	    m_List.InsertColumn(4, _T("���������� �������"), LVCFMT_LEFT, rect.Width() / 3);
		m_List.InsertColumn(5, _T("����������� �������"), LVCFMT_LEFT, rect.Width() / 3);

		CArray <Book,Book&> myBook ;

		Book b1(3,"������� ����", 77, "l8ENJR4PMGMFVWdsiN8G",100, "", "", 15 );
		myBook.Add(b1);
		Book b2(3,"������� ������", 23489, "Katk4ImwmQZ2fCO0cocA",17, "", "", 15 );
		myBook.Add(b2);

        LV_ITEM item;
        item.iItem = 0;
        item.iImage = 0;

        CString csText;
		for( int i = 0; i<myBook.GetSize() ; i++) {

         item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;

         // ��������
         item.iSubItem = 0;
         item.pszText = (LPTSTR)(LPCTSTR) myBook.GetAt(i).sName;
         m_List.InsertItem(&item);

         item.mask = LVIF_TEXT;

         // ����
         item.iSubItem = 1;
		 csText.Format(_T("%.2f"), myBook.GetAt(i).dPrice);
         item.pszText = (LPTSTR)(LPCTSTR)csText;
         m_List.SetItem(&item);

         // �����-���
         item.iSubItem = 2;
         item.pszText = (LPTSTR)(LPCTSTR) myBook.GetAt(i).sDashcode ;
         m_List.SetItem(&item);

         // ���������� �������
         item.iSubItem = 3;
		 csText.Format(_T("%d"), myBook.GetAt(i).nPages );
         item.pszText = (LPTSTR)(LPCTSTR)csText;
         m_List.SetItem(&item);

         // ����������� �������
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

	   m_List.InsertColumn(0, _T("��������"),    LVCFMT_LEFT, rect.Width() / 3);
       m_List.InsertColumn(1, _T("����"),     LVCFMT_LEFT, rect.Width() / 9);
       m_List.InsertColumn(2, _T("�����-���"),     LVCFMT_LEFT, 2 * rect.Width() / 9);



	   typedef CArray < Disks,Disks& > CmyDisk ;
	   CmyDisk  myDisk1, myDisk ;

	   Disks d1(1,"������","������� ����", 75, "Tq6Fzv865M8AR" );
	   myDisk.Add(d1);
	   Disks d2(1,"������","������ � ��������", 68.9, "Ko6bTsThMc3Mf");
	   myDisk.Add(d2);
	   Disks d3(1,"�����","����������� - ?", 4, "T6tPUMtSVnxG7" );
	   myDisk.Add(d3);
	   Disks d4(1,"�����","�������", 23, "9gzaQXOp4AQX9");
	   myDisk.Add(d4);
	   Disks d5(1,"��","Adobe", 50000, "tRE3Rp670dGmp" );
	   myDisk.Add(d5);
	   Disks d6(1,"��","MS Office", 10000, "wzUQsfQuH272z");
	   myDisk.Add(d6);

	   Disks d7(2,"������","���-�-����", 0, "qOw4y2l27LbYK" );
	   myDisk.Add(d7);
	   Disks d8(2,"�����","�������� �����", 11, "p2xQJzsapieLA" );
	   myDisk.Add(d8);
	   Disks d9(2,"��","AutoCad Revit", 146, "SCYKoVFaf65kD");
	   myDisk.Add(d9);

       if ((!strSelected.CompareNoCase(_T("������"))) || 
	  	    (!strSelected.CompareNoCase(_T("�����"))) || 
			 (!strSelected.CompareNoCase(_T("��")))) {

	    // ������� ����
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

         // ��������
         item.iSubItem = 0;
         item.pszText = (LPTSTR)(LPCTSTR) myDisk1.GetAt(i).sName;
         m_List.InsertItem(&item);

         item.mask = LVIF_TEXT;

		 // ����
         item.iSubItem = 1;
		 csText.Format(_T("%.2f"), myDisk1.GetAt(i).dPrice);
         item.pszText = (LPTSTR)(LPCTSTR)csText;
         m_List.SetItem(&item);

         // �����-���
         item.iSubItem = 2;
         item.pszText = (LPTSTR)(LPCTSTR) myDisk1.GetAt(i).sDashcode ;
         m_List.SetItem(&item);

         item.iItem++;
		}

	   }

	  }



	*pResult = 0;
}
