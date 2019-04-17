// Disks.h: interface for the Disks class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISKS_H__880114A8_41DC_4728_A462_72E66AC85CD3__INCLUDED_)
#define AFX_DISKS_H__880114A8_41DC_4728_A462_72E66AC85CD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "S.h"

class Disks : public S  
{
public:
	Disks();
	Disks(int , std::string, std::string , double , std::string );
	virtual ~Disks();
	
	// 1 - CD , 2 - DVD
	int iType ;

	// музыка, Видео, ПО
	std::string sType ;
};

#endif // !defined(AFX_DISKS_H__880114A8_41DC_4728_A462_72E66AC85CD3__INCLUDED_)
