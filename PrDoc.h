// PrDoc.h : interface of the CPrDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRDOC_H__727D00D4_E2A6_413E_A5C9_3DBEB95560D0__INCLUDED_)
#define AFX_PRDOC_H__727D00D4_E2A6_413E_A5C9_3DBEB95560D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPrDoc : public CDocument
{
protected: // create from serialization only
	CPrDoc();
	DECLARE_DYNCREATE(CPrDoc)

// Attributes
public:
	CString m_szTreeParent;    // а это, собственно, наш параметр - Родитель
	CString m_szTreeSel;       // а это, собственно, наш параметр - Выделенный элемент
// Operations
public:
    void SetTreeText(CString szParent,CString szSel)
	{m_szTreeParent=szParent;m_szTreeSel=szSel;} //это функции для передачи параметра между контролами
    CString GetTreeParent(){ return m_szTreeParent;}
	CString GetTreeSel(){ return m_szTreeSel;}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPrDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPrDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRDOC_H__727D00D4_E2A6_413E_A5C9_3DBEB95560D0__INCLUDED_)
