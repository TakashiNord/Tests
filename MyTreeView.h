// myTreeView.h : interface of the CMyTree class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYTREEVIEW_H__E62D7947_BD49_4F01_A165_07844A9075AF__INCLUDED_)
#define AFX_MYTREEVIEW_H__E62D7947_BD49_4F01_A165_07844A9075AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define TREE_ID 102

class CMyTree : public CView
{
protected: // create from serialization only
	CMyTree();
	DECLARE_DYNCREATE(CMyTree)

// Attributes
public:
	CPrDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTree)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
	//}}AFX_VIRTUAL

// Implementation
public:
	CTreeCtrl m_Tree;
	virtual ~CMyTree();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyTree)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in myTreeView.cpp
inline CPrDoc* CMyTree::GetDocument()
   { return (CPrDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTREEVIEW_H__E62D7947_BD49_4F01_A165_07844A9075AF__INCLUDED_)
