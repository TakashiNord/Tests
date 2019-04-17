#if !defined(AFX_MYLIST_H__AC6E701B_87D2_4BDD_AC1D_B7949B6B8DD4__INCLUDED_)
#define AFX_MYLIST_H__AC6E701B_87D2_4BDD_AC1D_B7949B6B8DD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyListView.h : header file
//

#define LIST_ID 101

/////////////////////////////////////////////////////////////////////////////
// CMyListView view

class CMyList : public CView
{
protected:
	CMyList();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyList)

// Attributes
public:
	CPrDoc* GetDocument();

// Operations
public:
	void MsgList(CString ,CString );
	CListCtrl m_List;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyList)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyList();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyList)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in myList.cpp
inline CPrDoc* CMyList::GetDocument()
   { return (CPrDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLIST_H__AC6E701B_87D2_4BDD_AC1D_B7949B6B8DD4__INCLUDED_)
