// Book.cpp: implementation of the Book class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Book.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Book::Book()
{
 sName = "";
 dPrice = 0 ;
 sDashcode = "";
 iType = 0 ;
 nPages = 0 ;
 sLang = "";
 sIngr = "";
 nAges = 0 ;
}

Book::Book(int iT, std::string s1, double dp, std::string s2, int nP, std::string sL, std::string sI , int nA)
{
	iType = iT ;
	sName = s1 ;
	dPrice = dp ;
	sDashcode=s2;
	nPages = nP;
	sLang=sL;
	sIngr=sI;
    nAges = nA;
}

std::string Book::IntToStrAges()
{
 std::string s = S::IntToStr1(nAges);
 return s.c_str();
}

std::string Book::IntToStrPages()
{
 std::string s = S::IntToStr1(nPages);
 return s.c_str();
}

Book::~Book()
{

}
