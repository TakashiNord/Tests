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
	
	// 1 - �� ����������������
	// 2 - �� ���������
	// 3 - �� ���������
	int iType ;

	int  nPages; // ���������� �������
	std::string  sLang ; // ���� ����������������
	std::string  sIngr ; // �������� ����������
	int  nAges ; // ����������� �������
};

#endif // !defined(AFX_BOOK_H__9B8BE4B6_8597_4698_B0A5_25354482D99E__INCLUDED_)
