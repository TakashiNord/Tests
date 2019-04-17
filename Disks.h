// Disks.h: interface for the Disks class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISKS_H__600C7E9A_44D6_4EA2_98E8_DCB6E99FEA33__INCLUDED_)
#define AFX_DISKS_H__600C7E9A_44D6_4EA2_98E8_DCB6E99FEA33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shop.h"

class Disks : public Shop  
{
public:
	Disks();
	Disks(int , CString, CString , double , CString );
	virtual ~Disks();

	// 1 - CD
	// 2 - DVD
	int iType ;

	// музыка, Видео, ПО
	CString sType ;
};

#endif // !defined(AFX_DISKS_H__600C7E9A_44D6_4EA2_98E8_DCB6E99FEA33__INCLUDED_)
