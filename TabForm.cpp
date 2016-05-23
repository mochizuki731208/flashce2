// TabForm.cpp : implementation file
//

#include "stdafx.h"
#include "FlashCE2抓包.h"
#include "TabForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabForm dialog


CTabForm::CTabForm(CWnd* pParent /*=NULL*/)
	: CDialog(CTabForm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTabForm)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTabForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabForm)
	DDX_Control(pDX, IDC_LIST1, m_List1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabForm, CDialog)
	//{{AFX_MSG_MAP(CTabForm)
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabForm message handlers

BOOL CTabForm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//设置list 行选,显示网格
	m_List1.SetExtendedStyle(m_List1.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	m_List1.DeleteAllItems();//清空(不会清空列头)
	//添加列 
	m_List1.InsertColumn(0,_T("桌号")); 
	m_List1.InsertColumn(1,_T("总分"));  
	m_List1.InsertColumn(2,_T("详情"));  
	//设置列宽  
	m_List1.SetColumnWidth(0, 50);
 	m_List1.SetColumnWidth(1, 50);  
	m_List1.SetColumnWidth(2, 400); 

// 	//添加
// 	m_List1.InsertItem(  0,    _T("A001")     );  //重载了多种方式可用
// 	m_List1.SetItemText( 0, 1, "55" );  
// 	
// 	m_List1.InsertItem(  1,   _T("A002")     );//成功则返回添加的位置 
// 	m_List1.SetItemText( 1, 1,  "22" ); 



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTabForm::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}
