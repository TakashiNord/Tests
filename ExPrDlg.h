// ExPrDlg.h : header file
//

#if !defined(AFX_EXPRDLG_H__2F93F4A3_48F5_43F8_9516_8462F57A9706__INCLUDED_)
#define AFX_EXPRDLG_H__2F93F4A3_48F5_43F8_9516_8462F57A9706__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CExPrDlg dialog

class CExPrDlg : public CDialog
{
// Construction
public:
	CExPrDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CExPrDlg)
	enum { IDD = IDD_EXPR_DIALOG };
	CListCtrl	m_List;
	CTreeCtrl	m_Tree;
	//}}AFX_DATA
	
	afx_msg void MsgList();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExPrDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CExPrDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	afx_msg void OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPRDLG_H__2F93F4A3_48F5_43F8_9516_8462F57A9706__INCLUDED_)
