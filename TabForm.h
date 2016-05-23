#if !defined(AFX_TABFORM_H__14DDE60E_B769_4A6B_AB66_AA23B3F731E2__INCLUDED_)
#define AFX_TABFORM_H__14DDE60E_B769_4A6B_AB66_AA23B3F731E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabForm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabForm dialog

class CTabForm : public CDialog
{
// Construction
public:
	CTabForm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTabForm)
	enum { IDD = IDD_DIALOG1 };
	CListCtrl	m_List1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTabForm)
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABFORM_H__14DDE60E_B769_4A6B_AB66_AA23B3F731E2__INCLUDED_)
