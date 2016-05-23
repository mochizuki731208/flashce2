// FlashCE2×¥°üDlg.h : header file
//
#include "TabForm.h"
#include "TabFormSet.h"
#include "TabFormRule.h"
//#include "MyWinpCap.h"



#if !defined(AFX_FLASHCE2DLG_H__ABB677A6_D177_48D9_8F6B_B8AE3502228B__INCLUDED_)
#define AFX_FLASHCE2DLG_H__ABB677A6_D177_48D9_8F6B_B8AE3502228B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFlashCE2Dlg dialog

class CFlashCE2Dlg : public CDialog
{
// Construction
public:
	CFlashCE2Dlg(CWnd* pParent = NULL);	// standard constructor
	CTabForm	pForm1;
	CTabFormSet pForm2;
	CTabFormRule pForm3;
	

// Dialog Data
	//{{AFX_DATA(CFlashCE2Dlg)
	enum { IDD = IDD_FLASHCE2_DIALOG };
	CComboBox	m_ListDev;
	CTabCtrl	m_tab;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlashCE2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFlashCE2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLASHCE2DLG_H__ABB677A6_D177_48D9_8F6B_B8AE3502228B__INCLUDED_)
