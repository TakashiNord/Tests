// Book.h: interface for the Book class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOOK_H__9B8BE4B6_8597_4698_B0A5_25354482D99E__INCLUDED_)
#define AFX_BOOK_H__9B8BE4B6_8597_4698_B0A5_25354482D99E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "S.h"

class Book : public S  
{
public:
	Book();
	Book(int , std::string , double, std::string , int, std::string , std::string , int );
	virtual ~Book();

	std::string Book::IntToStrAges() ;
    std::string Book::IntToStrPages() ;
	
	// 1 - по программированию
	// 2 - по кулинарии
	// 3 - по эзотерика
	int iType ;

	int  nPages; // количество страниц
	std::string  sLang ; // язык программирования
	std::string  sIngr ; // основной ингридиент
	int  nAges ; // минимальный возраст
};

#endif // !defined(AFX_BOOK_H__9B8BE4B6_8597_4698_B0A5_25354482D99E__INCLUDED_)
