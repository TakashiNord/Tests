// PrView.h : interface of the CPrView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRVIEW_H__F083BDFF_C4A8_4B08_8FA6_E5538D40A12D__INCLUDED_)
#define AFX_PRVIEW_H__F083BDFF_C4A8_4B08_8FA6_E5538D40A12D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPrView : public CView
{
protected: // create from serialization only
	CPrView();
	DECLARE_DYNCREATE(CPrView)

// Attributes
public:
	CPrDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPrView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPrView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PrView.cpp
inline CPrDoc* CPrView::GetDocument()
   { return (CPrDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRVIEW_H__F083BDFF_C4A8_4B08_8FA6_E5538D40A12D__INCLUDED_)
