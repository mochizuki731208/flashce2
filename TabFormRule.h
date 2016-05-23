#if !defined(AFX_TABFORMRULE_H__B9737EFC_4A86_4F79_9157_4D0C9D32E718__INCLUDED_)
#define AFX_TABFORMRULE_H__B9737EFC_4A86_4F79_9157_4D0C9D32E718__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabFormRule.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabFormRule dialog

class CTabFormRule : public CDialog
{
// Construction
public:
	CTabFormRule(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTabFormRule)
	enum { IDD = IDD_DIALOG3 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabFormRule)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTabFormRule)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABFORMRULE_H__B9737EFC_4A86_4F79_9157_4D0C9D32E718__INCLUDED_)
