// Disks.cpp: implementation of the Disks class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ExPr.h"
#include "Disks.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Disks::Disks()
{
   sName = "" ;
   dPrice = 0 ;
   sDashcode = "" ;
   iType  = 0;
   sType = "";
}

Disks::Disks(int iT, CString sT, CString s1, double d, CString s2 )
{
   sName = s1 ;
   dPrice = d ;
   sDashcode = s2 ;
   iType  = iT;
   sType = sT ;
}

Disks::~Disks()
{

}
