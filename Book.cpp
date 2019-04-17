// Book.cpp: implementation of the Book class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Book.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Book::Book()
{
   sName = "" ;
   dPrice = 0 ;
   sDashcode = "" ;
   iType  = 0;
   nPages = 0;
   sLang = "";
   sIngr = "";
   nAges = 0;
}

Book::Book(int iT, CString s1, double d, CString s2, int nP, CString sL, CString sI, int nA )
{
   sName = s1 ;
   dPrice = d ;
   sDashcode = s2 ;
   iType  = iT;
   nPages = nP;
   sLang =sL;
   sIngr =sI;
   nAges =nA;
}

Book::~Book()
{

}
