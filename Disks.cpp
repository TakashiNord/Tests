// Disks.cpp: implementation of the Disks class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Disks.h"

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

Disks::Disks(int iT, std::string sT, std::string s1, double d, std::string s2 )
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



