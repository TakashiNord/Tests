// Shop.cpp: implementation of the Shop class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Shop.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Shop::Shop()
{
   sName = "" ;
   dPrice = 0 ;
   sDashcode = "" ;
}

Shop::Shop(CString s1, double d, CString s2)
{
   sName = s1 ;
   dPrice = d ;
   sDashcode = s2 ;
}

Shop::~Shop()
{

}
