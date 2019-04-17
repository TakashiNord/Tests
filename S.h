// S.h: interface for the S class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_S_H__095394A7_F608_4848_A13B_B12D6C3C007A__INCLUDED_)
#define AFX_S_H__095394A7_F608_4848_A13B_B12D6C3C007A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include <iostream >
#include <sstream>
//#include <string>

//using namespace std;

class S  
{
public:
	S();
	S(std::string , double, std::string );
	virtual ~S();

	std::string IntToStr1( int );
	std::string IntToStr() ;
	std::string DblToStr1( double );
	std::string DblToStr();
	
	std::string sName ;
	double  dPrice ;
	std::string sDashcode ;

};

#endif // !defined(AFX_S_H__095394A7_F608_4848_A13B_B12D6C3C007A__INCLUDED_)
