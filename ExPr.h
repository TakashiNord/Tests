// ExPr.h : main header file for the EXPR application
//

#if !defined(AFX_EXPR_H__F9730FBF_B013_453B_8A87_D47C04299072__INCLUDED_)
#define AFX_EXPR_H__F9730FBF_B013_453B_8A87_D47C04299072__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CExPrApp:
// See ExPr.cpp for the implementation of this class
//

class CExPrApp : public CWinApp
{
public:
	CExPrApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExPrApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CExPrApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPR_H__F9730FBF_B013_453B_8A87_D47C04299072__INCLUDED_)
