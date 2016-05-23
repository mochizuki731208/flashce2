// TabFormSet.cpp : implementation file
//

#include "stdafx.h"
#include "FlashCE2×¥°ü.h"
#include "TabFormSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabFormSet dialog


CTabFormSet::CTabFormSet(CWnd* pParent /*=NULL*/)
	: CDialog(CTabFormSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTabFormSet)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTabFormSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabFormSet)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabFormSet, CDialog)
	//{{AFX_MSG_MAP(CTabFormSet)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabFormSet message handlers
