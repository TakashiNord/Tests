// S.cpp: implementation of the S class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <stdio.h>
#include "S.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

S::S()
{
 sName = "";
 dPrice = 0 ;
 sDashcode = "";
}

S::S(std::string s1, double dp, std::string s2)
{
	sName = s1;
	dPrice = dp ;
	sDashcode = s2;
}

std::string S::IntToStr1( int Number )
{
 std::string s;
 std::stringstream out;
 out << Number;
 s = out.str();
 return s.c_str();
}

std::string S::IntToStr()
{
 std::string s = IntToStr1(dPrice);
 return s.c_str();
}

std::string S::DblToStr1( double Number )
{
  std::string s ; 
  std::stringstream out;
  out << Number;
  s = out.str();

  char buf[30];  sprintf(buf,"%.2lf", Number) ;  s = buf;

  return s.c_str();
}

std::string S::DblToStr( )
{
  std::string s = DblToStr1( dPrice ); 
  return s.c_str();
}

S::~S()
{

}
