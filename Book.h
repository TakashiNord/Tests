// Book.h: interface for the Book class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOOK_H__79D50F6D_E37A_4AAF_9008_544C6B732F2F__INCLUDED_)
#define AFX_BOOK_H__79D50F6D_E37A_4AAF_9008_544C6B732F2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shop.h"

class Book : public Shop  
{
public:
	Book();
	Book(int , CString, double, CString, int, CString, CString , int );
	virtual ~Book();

	// 1 - �� ����������������
	// 2 - �� ���������
	// 3 - �� ���������
	int iType ;

	int  nPages; // ���������� �������
	CString  sLang ; // ���� ����������������
	CString  sIngr ; // �������� ����������
	int  nAges ; // ����������� �������

};

#endif // !defined(AFX_BOOK_H__79D50F6D_E37A_4AAF_9008_544C6B732F2F__INCLUDED_)
