// ExPr6.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

//#define STRICT

#include <VECTOR>

using namespace std;

//#include "S.h"
#include "Book.h"
#include "Disks.h"

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>

#pragma comment(lib,"comctl32.lib") //for linker

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

#define IDC_TREEVIEW 101
#define IDC_LISTVIEW 102
HWND hwndTree , hwndList ;

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

//WndProc_OnCommand(hWnd, (int)LOWORD(wParam),(HWND)(lParam),(UINT)HIWORD(wParam));
void WndProc_OnCommand(HWND , int , HWND , UINT );
BOOL WndProc_OnCreate(HWND , LPCREATESTRUCT ) ;
void WndProc_OnDestroy(HWND ) ;
void WndProc_OnPaint(HWND);
void WndProc_OnSize(HWND , UINT , int , int );
LRESULT WndProc_OnNotify(HWND , int , NMHDR* );

HTREEITEM InsTreeItem(HTREEITEM hParent, LPSTR szText, HTREEITEM hAfter);
void MsgList(LPCSTR ,LPCSTR );


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_EXPR6, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	InitCommonControls();   //make sure dll is loaded
    
	//INITCOMMONCONTROLSEX iccx;
    //iccx.dwSize = sizeof(INITCOMMONCONTROLSEX);
    //iccx.dwICC = ICC_BAR_CLASSES|ICC_LISTVIEW_CLASSES|ICC_TREEVIEW_CLASSES;
    //InitCommonControlsEx(&iccx);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_EXPR6);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_EXPR6);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_EXPR6;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

// Проверяем, не было ли это приложение запущено ранее
   hWnd = FindWindow(szWindowClass, NULL);
   if(hWnd)
   {
     // Если окно приложения было свернуто в пиктограмму,
     // восстанавливаем его
     if(IsIconic(hWnd)) ShowWindow(hWnd, SW_RESTORE);

     // Выдвигаем окно приложения на передний план
	 SetForegroundWindow(hWnd);
	 return TRUE;
   }

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
       HANDLE_MSG(hWnd, WM_CREATE, WndProc_OnCreate );
	   HANDLE_MSG(hWnd, WM_COMMAND, WndProc_OnCommand );
	   HANDLE_MSG(hWnd, WM_NOTIFY, WndProc_OnNotify);
	   HANDLE_MSG(hWnd, WM_PAINT, WndProc_OnPaint );
	   HANDLE_MSG(hWnd, WM_DESTROY, WndProc_OnDestroy );
	default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}


#pragma warning(disable: 4098)

void WndProc_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	// Parse the menu selections:
	switch (id)
	{
		case IDM_ABOUT:
		   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
		   break;
		case IDM_EXIT:
		   DestroyWindow(hWnd);
		   break;
		default:
		   return ;
	}
   
   return ;
}


BOOL WndProc_OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
   RECT rc ;
   HTREEITEM hRootItem;
   HTREEITEM hBSPItem1,hBSPItem2;
   HTREEITEM hDItem1,hDItem2;

   DWORD dwStyle = 0;

   LV_COLUMN lvc;
   

   GetClientRect(hWnd,&rc);
	
   hwndTree = CreateWindowEx(0L, WC_TREEVIEW, "",
    WS_VISIBLE | WS_CHILD | WS_BORDER |
    TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT,
    0, 0, (rc.right - rc.left)/3, rc.bottom - rc.top,
    hWnd, (HMENU)IDC_TREEVIEW, hInst, NULL);
   
   if (hwndTree==NULL) return FALSE ;

   hRootItem = InsTreeItem((HTREEITEM)TVI_ROOT, _T("Shop"),(HTREEITEM)TVI_FIRST);

   hBSPItem1 = InsTreeItem(hRootItem, _T("Книги"),(HTREEITEM)TVI_LAST);
   hBSPItem2 = InsTreeItem(hRootItem, _T("Диски"),(HTREEITEM)TVI_LAST);

   InsTreeItem(hBSPItem1, _T("Программирование"),(HTREEITEM)TVI_LAST);
   InsTreeItem(hBSPItem1, _T("Кулинария"),(HTREEITEM)TVI_LAST);
   InsTreeItem(hBSPItem1, _T("Эзотерика"),(HTREEITEM)TVI_LAST);

   hDItem1=InsTreeItem(hBSPItem2, _T("CD"),(HTREEITEM)TVI_LAST);
   hDItem2=InsTreeItem(hBSPItem2, _T("DVD"),(HTREEITEM)TVI_LAST);

   InsTreeItem(hDItem1, _T("Музыка"),(HTREEITEM)TVI_LAST);
   InsTreeItem(hDItem1, _T("Видео"),(HTREEITEM)TVI_LAST);
   InsTreeItem(hDItem1, _T("ПО"),(HTREEITEM)TVI_LAST);
   
   InsTreeItem(hDItem2, _T("Музыка"),(HTREEITEM)TVI_LAST);
   InsTreeItem(hDItem2, _T("Видео"),(HTREEITEM)TVI_LAST);
   InsTreeItem(hDItem2, _T("ПО"),(HTREEITEM)TVI_LAST);

   TreeView_SetTextColor(hwndTree,(COLORREF)(LPARAM)RGB(0,0,160));   
   TreeView_SetBkColor(hwndTree,(COLORREF)(LPARAM)RGB(200,200,200)); 

   //SendMessage(hwndTree,TVM_EXPAND, TVE_EXPAND, (LPARAM)hRootItem);
   TreeView_Expand(hwndTree,hRootItem, TVE_EXPAND);

   
  // Создаем орган управления List View
  hwndList = CreateWindowEx(0L, WC_LISTVIEW, "",
    WS_VISIBLE | WS_CHILD | WS_BORDER |WS_TABSTOP| 
	 WS_HSCROLL | WS_VSCROLL | 
	 LVS_REPORT | LVS_EDITLABELS | LVS_SINGLESEL,
    (rc.right - rc.left)/3+1, 0, rc.right - rc.left, rc.bottom - rc.top,
    hWnd, (HMENU)IDC_LISTVIEW, hInst, NULL);

  //dwStyle = GetWindowLong(hwndList, GWL_STYLE);
  dwStyle |=  LVS_EX_GRIDLINES; // LVS_EX_FULLROWSELECT
  //SetWindowLong(hwndList, GWL_STYLE, dwStyle );
  ListView_SetExtendedListViewStyle(hwndList, dwStyle);

  if(hwndList == NULL) return FALSE;

  // Вставляем столбцы
  memset(&lvc, 0, sizeof(lvc));

  lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH ;
  lvc.fmt = LVCFMT_LEFT;
  lvc.cx = (rc.right - rc.left) / 4;
  
  lvc.iSubItem = 0;
  lvc.pszText = "Название";
  lvc.cx = 200 ;
  ListView_InsertColumn(hwndList, 0, &lvc);

  lvc.iSubItem = 1;
  lvc.pszText = "Цена";
  lvc.cx = 50 ;
  ListView_InsertColumn(hwndList, 1, &lvc);

  lvc.iSubItem = 2;
  lvc.pszText = "Штрих-код";
  lvc.cx = 150 ;
  ListView_InsertColumn(hwndList, 2, &lvc);
  
  //ListView_SetColumnWidth(hwndList,2,(rc.right-rc.left) / 8);

   return TRUE;
}


LRESULT WndProc_OnNotify(HWND hWnd, int idFrom, NMHDR* pnmhdr)
{
  LV_DISPINFO * lpLvdi = (LV_DISPINFO *)pnmhdr;
  NM_TREEVIEW *lpNm = (NM_TREEVIEW *)pnmhdr;

  static TV_ITEM TV_Item1, TV_Item2 ;
  char str1[100], str2[100] ;
  HTREEITEM hItem, hItemParent;

  //if (idFrom!=IDC_TREEVIEW) return 0L;

  switch(pnmhdr->code)
  {
    case TVN_SELCHANGED:
    {

        /*HTREEITEM*/ hItem = TreeView_GetSelection(hwndTree);
        TV_Item1.mask=TVIF_TEXT | TVIF_HANDLE;
        TV_Item1.hItem = hItem;
        TV_Item1.pszText = str1;
        TV_Item1.cchTextMax = 100;

        /*HTREEITEM*/ hItemParent = TreeView_GetParent( hwndTree, hItem );
        TV_Item2.mask=TVIF_TEXT | TVIF_HANDLE;
        TV_Item2.hItem = hItemParent;
        TV_Item2.pszText = str2;
        TV_Item2.cchTextMax = 100;		
		
		if(TreeView_GetItem(pnmhdr->hwndFrom, &TV_Item1))
         {
            if(TreeView_GetItem(pnmhdr->hwndFrom, &TV_Item2))
           	  MsgList(TV_Item2.pszText,TV_Item1.pszText);
            else 
			  MsgList("",TV_Item1.pszText);
		 }
    }
	break ;

  }
  return 0L;
}


void WndProc_OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	
	hdc = BeginPaint(hWnd, &ps);
	// TODO: Add any drawing code here...
	RECT rt;
	GetClientRect(hWnd, &rt);
	//
	EndPaint(hWnd, &ps);
   
   return ;
}


void WndProc_OnSize(HWND hWnd, UINT state, int cx, int cy)
{
   RECT rc ;
   GetClientRect(hWnd,&rc);
	
   //MoveWindow(hwndTree, 0, 0, cx, cy, TRUE);
   //MoveWindow(hwndList, 0, 0, cx, cy, TRUE);
}


#pragma warning(disable: 4098)
void WndProc_OnDestroy(HWND hWnd)
{
   if (hwndTree) DestroyWindow(hwndTree);
   if (hwndList) DestroyWindow(hwndList);
   PostQuitMessage(0);
   return ;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}


HTREEITEM InsTreeItem(HTREEITEM hParent, LPSTR szText, HTREEITEM hAfter)
{
  TV_INSERTSTRUCT tvins;
  HTREEITEM hItem;

  memset(&tvins, 0, sizeof(tvins));
  tvins.item.mask = TVIF_TEXT | TVIF_PARAM ;
  tvins.item.pszText = szText;
  tvins.item.cchTextMax = lstrlen(szText);
  tvins.hInsertAfter = hAfter;
  tvins.hParent = hParent;
  
  hItem = TreeView_InsertItem(hwndTree, &tvins); 
  return hItem;
} 


void MsgList(LPCSTR strParent,LPCSTR strSelected)
{
   RECT rc;
   LV_COLUMN lvc;
   int i ;

   //::SendMessage (hwndList, WM_SETREDRAW, FALSE, 0);

   ListView_DeleteAllItems(hwndList) ;
   UpdateWindow(hwndList);
   while (ListView_DeleteColumn(hwndList, 0) );
   //UpdateWindow(hwndList);

  GetClientRect(hwndList, &rc);

   // Вставляем столбцы
  memset(&lvc, 0, sizeof(lvc));

  lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
  lvc.fmt = LVCFMT_LEFT;
  lvc.cx = (rc.right - rc.left) / 5;
  
  lvc.iSubItem = 0;
  lvc.pszText = "Название";
  lvc.cx = 200 ;
  ListView_InsertColumn(hwndList, 0, &lvc);

  lvc.iSubItem = 1;
  lvc.pszText = "Цена";
  lvc.cx = 50 ;
  ListView_InsertColumn(hwndList, 1, &lvc);

  lvc.iSubItem = 2;
  lvc.pszText = "Штрих-код";
  lvc.cx = 150 ;
  ListView_InsertColumn(hwndList, 2, &lvc);

  //ListView_SetColumnWidth(hwndList,2,(rc.right-rc.left) / 8);

  if (0==strcmp(strSelected,"Книги")) {
     lvc.iSubItem = 3;
     lvc.pszText = "Количество страниц";
	 lvc.cx = 140 ;
     ListView_InsertColumn(hwndList, 3, &lvc);

	 //::SendMessage (hwndList, WM_SETREDRAW, TRUE, 0);
	 UpdateWindow(hwndList);
	 return ;
  }

  if (0==strcmp(strSelected,_T("Программирование"))) {
     lvc.iSubItem = 3;
     lvc.pszText = "Количество страниц";
	 lvc.cx = 140 ;
     ListView_InsertColumn(hwndList, 3, &lvc);

     lvc.iSubItem = 4;
     lvc.pszText = "Язык программирования";
	 lvc.cx = 140 ;
     ListView_InsertColumn(hwndList, 4, &lvc);

	  int n = 10;
      vector <Book *> myBook(n);
	  myBook[0]=new Book(1,"Программирование С ", 0, "SDSdwere4355gf5",100, "С", "", 18 );
	  myBook[1]=new Book(1,"Программирование С++ ", 12.56, "e54rt355gf5",17, "C++", "", 18 );
	  myBook[2]=new Book(1,"Delphi", 1234, "APGpeHvH4JHUfBjrBZWR",150, "Object Pascal", "", 20 );
	  myBook[3]=new Book(1,"Основы Perl", 567, "daUR5VeNVgWQRt2JVDIa",50, "Perl", "", 23 );
	  myBook[4]=new Book(1,"Lua", 435.6, "I2iySPQQ2uQSZ08Q5P7M",34, "Lua", "", 25 );
	  myBook[5]=new Book(1,"Python", 33, "HeoXWUDZfNGaYwzJ5u6A",256, "Python", "", 26 );
	  myBook[6]=new Book(1,"Library Qt", 6578.5, "OkGfThFKHZUhxV71FthE",324, "C++", "", 30 );

      LVITEM item;
      item.iItem = 0;
      item.iImage = 0;
	  item.mask = LVIF_TEXT | LVCF_SUBITEM ;
      item.iSubItem = 0;
      item.state = 0; 
      item.stateMask = 0;

	  for(i = 0; i<myBook.size() ; i++) {

		if (myBook[i]==NULL) continue ;
        
        item.pszText = (LPSTR)"";
		ListView_InsertItem(hwndList, &item);

		// название
        ListView_SetItemText(hwndList,item.iItem,0,(LPSTR)myBook[i]->sName.c_str());
        // цена
		ListView_SetItemText(hwndList,item.iItem,1,(LPSTR)myBook[i]->DblToStr().c_str());
        // штрих-код
		ListView_SetItemText(hwndList,item.iItem,2,(LPSTR)myBook[i]->sDashcode.c_str());
        // Количество страниц
        ListView_SetItemText(hwndList,item.iItem,3,(LPSTR)myBook[i]->IntToStrPages().c_str());
        // Язык программирования
        ListView_SetItemText(hwndList,item.iItem,4,(LPSTR)myBook[i]->sLang.c_str());

		item.iItem++;

	  }

	  for( i = 0; i<myBook.size() ; i++) if (myBook[i]!=NULL) delete myBook[i] ;
	  myBook.clear();

	 EnableScrollBar(hwndList,SB_BOTH,ESB_ENABLE_BOTH);
	  //::SendMessage (hwndList, WM_SETREDRAW, TRUE, 0);
	 UpdateWindow(hwndList);
	 return ;
  }

  if (0==strcmp(strSelected,_T("Кулинария"))) {
     lvc.iSubItem = 3;
     lvc.pszText = "Количество страниц";
	 lvc.cx = 80 ;
     ListView_InsertColumn(hwndList, 3, &lvc);

     lvc.iSubItem = 4;
     lvc.pszText = "Основной ингредиент";
	 lvc.cx = 80 ;
     ListView_InsertColumn(hwndList, 4, &lvc);


	  int n = 5;
      vector <Book *> myBook(n);
	  myBook[0]=new Book(2,"Как найти еду", 109, "RS2MSrZiq0WzqZ2IFeOj",453, "", "мясо", 33 );
	  myBook[1]=new Book(2,"Как приготовить еду", 568, "Enfvd5jpEHFslSRUotB0",2, "", "еда", 10 );
	  myBook[2]=new Book(2,"Как сьесть еду", 12, "qbku1xBJ3ZxGuq8vTjoA",1000, "", "пшеница", 18 );
	  myBook[3]=new Book(2,"Как переваривать еду", 689, "yIoxpO0y46USWyZtaswn",5, "", "хлеб", 40 );

      LVITEM item;
      item.iItem = 0;
      item.iImage = 0;
	  item.mask = LVIF_TEXT | LVCF_SUBITEM ;
      item.iSubItem = 0;
      item.state = 0; 
      item.stateMask = 0;

	  for(i = 0; i<myBook.size() ; i++) {

		if (myBook[i]==NULL) continue ;
        
        item.pszText = (LPSTR)"";
		ListView_InsertItem(hwndList, &item);

		// название
        ListView_SetItemText(hwndList,item.iItem,0,(LPSTR)myBook[i]->sName.c_str());
        // цена
		ListView_SetItemText(hwndList,item.iItem,1,(LPSTR)myBook[i]->DblToStr().c_str());
        // штрих-код
		ListView_SetItemText(hwndList,item.iItem,2,(LPSTR)myBook[i]->sDashcode.c_str());
        // Количество страниц
        ListView_SetItemText(hwndList,item.iItem,3,(LPSTR)myBook[i]->IntToStrPages().c_str());
        // Основной ингредиент
        ListView_SetItemText(hwndList,item.iItem,4,(LPSTR)myBook[i]->sIngr.c_str());

		item.iItem++;

	  }

	  for( i = 0; i<myBook.size() ; i++) if (myBook[i]!=NULL) delete myBook[i] ;
	  myBook.clear();

	 UpdateWindow(hwndList);
	 return ;
  }

  if (0==strcmp(strSelected,_T("Эзотерика"))) {
     lvc.iSubItem = 3;
     lvc.pszText = "Количество страниц";
	 lvc.cx = 80 ;
     ListView_InsertColumn(hwndList, 3, &lvc);

     lvc.iSubItem = 4;
     lvc.pszText = "Минимальный возраст";
	 lvc.cx = 80 ;
     ListView_InsertColumn(hwndList, 4, &lvc);

	  int n = 5;
      vector <Book *> myBook(n);
	  myBook[0]=new Book(3,"Буддизм Востока", 77, "l8ENJR4PMGMFVWdsiN8G",100, "", "", 15 );
	  myBook[1]=new Book(3,"Ислам и религии Востока", 0.6, "Katk4ImwmQZ2fCO0cocA",17, "", "", 15 );

      LVITEM item;
      item.iItem = 0;
      item.iImage = 0;
	  item.mask = LVIF_TEXT | LVCF_SUBITEM ;
      item.iSubItem = 0;
      item.state = 0; 
      item.stateMask = 0;

	  for(i = 0; i<myBook.size() ; i++) {

		if (myBook[i]==NULL) continue ;
        
        item.pszText = (LPSTR)"";
		ListView_InsertItem(hwndList, &item);

		// название
        ListView_SetItemText(hwndList,item.iItem,0,(LPSTR)myBook[i]->sName.c_str());
        // цена
		ListView_SetItemText(hwndList,item.iItem,1,(LPSTR)myBook[i]->DblToStr().c_str());
        // штрих-код
		ListView_SetItemText(hwndList,item.iItem,2,(LPSTR)myBook[i]->sDashcode.c_str());
        // Количество страниц
        ListView_SetItemText(hwndList,item.iItem,3,(LPSTR)myBook[i]->IntToStrPages().c_str());
        // Минимальный возраст
        ListView_SetItemText(hwndList,item.iItem,4,(LPSTR)myBook[i]->IntToStrAges().c_str());

		item.iItem++;

	  }

	  for( i = 0; i<myBook.size() ; i++) if (myBook[i]!=NULL) delete myBook[i] ;
	  myBook.clear();

	 UpdateWindow(hwndList);
	 return ;
  }

  if ((!stricmp(strSelected,_T("Музыка"))) || 
  	    (!stricmp(strSelected,_T("Видео"))) || 
		 (!stricmp(strSelected,_T("ПО")))) {
  
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


	int iIndex = (0==stricmp(strParent,_T("CD")))?1:2 ;

      LVITEM item;
      item.iItem = 0;
      item.iImage = 0;
	  item.mask = LVIF_TEXT | LVCF_SUBITEM ;
      item.iSubItem = 0;
      item.state = 0; 
      item.stateMask = 0;

	  std::string s = strSelected ;

	  for(i = 0; i<myDisk.size() ; i++) {

		if (myDisk[i]==NULL) continue ;

		if ((myDisk[i]->iType!=iIndex) || 
		  (s!=myDisk[i]->sType)) continue ;

        item.pszText = (LPSTR)"";
		ListView_InsertItem(hwndList, &item);

		// название
        ListView_SetItemText(hwndList,item.iItem,0,(LPSTR)myDisk[i]->sName.c_str());
        // цена
		ListView_SetItemText(hwndList,item.iItem,1,(LPSTR)myDisk[i]->DblToStr().c_str());
        // штрих-код
		ListView_SetItemText(hwndList,item.iItem,2,(LPSTR)myDisk[i]->sDashcode.c_str());

		item.iItem++;

	  }

	for( i = 0; i<myDisk.size() ; i++) if (myDisk[i]!=NULL) delete myDisk[i] ;
	myDisk.clear();
  
  }
  
  UpdateWindow(hwndList);
  return ;

}
