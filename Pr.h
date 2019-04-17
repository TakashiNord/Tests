// Pr.h : main header file for the PR application
//

#if !defined(AFX_PR_H__E1A59AFD_1210_4133_BF8D_845A74BD335C__INCLUDED_)
#define AFX_PR_H__E1A59AFD_1210_4133_BF8D_845A74BD335C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPrApp:
// See Pr.cpp for the implementation of this class
//

class CPrApp : public CWinApp
{
public:
	CPrApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPrApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PR_H__E1A59AFD_1210_4133_BF8D_845A74BD335C__INCLUDED_)
