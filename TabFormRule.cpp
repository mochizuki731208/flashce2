// TabFormRule.cpp : implementation file
//

#include "stdafx.h"
#include "FlashCE2×¥°ü.h"
#include "TabFormRule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabFormRule dialog


CTabFormRule::CTabFormRule(CWnd* pParent /*=NULL*/)
	: CDialog(CTabFormRule::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTabFormRule)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTabFormRule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabFormRule)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabFormRule, CDialog)
	//{{AFX_MSG_MAP(CTabFormRule)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabFormRule message handlers
