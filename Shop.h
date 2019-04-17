// Shop.h: interface for the Shop class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHOP_H__72C08C62_46DC_4050_B7FE_8EA7556EF598__INCLUDED_)
#define AFX_SHOP_H__72C08C62_46DC_4050_B7FE_8EA7556EF598__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Shop  
{
public:
	Shop();
	Shop(CString, double, CString);
	virtual ~Shop();
	
	CString sName ;
	double  dPrice ;
	CString sDashcode ;

};

#endif // !defined(AFX_SHOP_H__72C08C62_46DC_4050_B7FE_8EA7556EF598__INCLUDED_)
