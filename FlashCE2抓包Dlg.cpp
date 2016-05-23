// FlashCE2抓包Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "FlashCE2抓包.h"
#include "FlashCE2抓包Dlg.h"

#include "TabForm.h"
#include "TabFormSet.h"
#include "TabFormRule.h"
#include "SnifferWork.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern PCAPThreadInfo MyThis;


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlashCE2Dlg dialog

CFlashCE2Dlg::CFlashCE2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFlashCE2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFlashCE2Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFlashCE2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFlashCE2Dlg)
	DDX_Control(pDX, IDC_COMBO1, m_ListDev);
	DDX_Control(pDX, IDC_TAB1, m_tab);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFlashCE2Dlg, CDialog)
	//{{AFX_MSG_MAP(CFlashCE2Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlashCE2Dlg message handlers

BOOL CFlashCE2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	//////////////////////////////////////////////////////////////////////////
	HANDLE hObject = CreateMutex(NULL,FALSE,"MYFLASHCE2_201508");
	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(hObject);
		MessageBox("程序已经运行!","抓包");
		
		exit(0);
		//AfxGetMainWnd()->CloseWindow();
		return FALSE;
	}


	initThread();

	//在属性页控件中添加2项
	m_tab.InsertItem(0, _T("主页"));
	m_tab.InsertItem(1, _T("设置"));
	m_tab.InsertItem(2, _T("规则"));
	//创建子对话框
	pForm1.Create(MAKEINTRESOURCE(IDD_DIALOG1), &m_tab);
	pForm2.Create(MAKEINTRESOURCE(IDD_DIALOG2), &m_tab);
	pForm3.Create(MAKEINTRESOURCE(IDD_DIALOG3), &m_tab);
	//计算对话框的显示位置和大小
	CRect rc;
	m_tab.GetClientRect(rc);
	rc.top += 30;
	rc.left += 8;
	rc.right -= 8;
	rc.bottom -= 8;
	//移动对话框
	pForm1.MoveWindow(rc);
	pForm2.MoveWindow(rc);
	pForm3.MoveWindow(rc);
	//默认显示第一个页，即第一个对话框
	pForm1.ShowWindow(SW_SHOW);


	//////////////////////////////////////////////////////////////////////////显示网卡
 	m_ListDev.ResetContent();

 	MyThis.tt.NetcardInfoInit();
 	int k=MyThis.tt.getNetcardCount();
 	CStringArray astr1,astr2,astr3;
 	for(int i=0;i<k;i++)
 	{
 		MyThis.tt.getNetcardIPInfo(i,astr1,astr2,astr3);
 		m_ListDev.AddString(MyThis.tt.getNetcardDescription(i));
 	}	
	m_ListDev.SetCurSel(0);
	


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFlashCE2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFlashCE2Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFlashCE2Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFlashCE2Dlg::OnOK() 
{
	// TODO: Add extra validation here
}

void CFlashCE2Dlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	switch(m_tab.GetCurSel()) 
	{
	case 0:
		pForm1.ShowWindow(SW_SHOW);
		pForm2.ShowWindow(SW_HIDE);
		pForm3.ShowWindow(SW_HIDE);
		break;
	case 1:
		pForm1.ShowWindow(SW_HIDE);
		pForm2.ShowWindow(SW_SHOW);
		pForm3.ShowWindow(SW_HIDE);
		break;
	case 2:
		pForm1.ShowWindow(SW_HIDE);
		pForm2.ShowWindow(SW_HIDE);
		pForm3.ShowWindow(SW_SHOW);
		break;

	default:
		break;
	}

	*pResult = 0;
}

//////////////////////////////////////////////////////////////////////////
UINT pcapThread(LPVOID lpParam)
{
	if(MyThis.pcapIndex>=0)
	{
		MyThis.tt.NetworkCardMonitoring(MyThis.tt.getNetcardName(MyThis.pcapIndex).GetBuffer(0),"",NetworkCardDataReceive);
		MyThis.tt.getNetcardName(MyThis.pcapIndex).ReleaseBuffer(0);
	}
	return 0;
}
void CFlashCE2Dlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	initGame();

	SetHwndShow(GetDlgItem(IDC_STATIC1)->GetSafeHwnd());

	int j = m_ListDev.GetCurSel();
	if(j>=0)
	{
		MyThis.pcapIndex = j;
		MyThis.pThread2=AfxBeginThread(&pcapThread,NULL);
	}
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
}

void testBBBB()
{
	_ConnectionPtr	m_pConnection;
	_RecordsetPtr	m_pRecordset;

	m_pConnection.CreateInstance(__uuidof(Connection));
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	try
	{	//Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" & dbPath & ";Persist Security Info=False
		m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source='001.mdb'","","",adModeUnknown);
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}
}
void testAAAA()
{
	_ConnectionPtr	m_pConnection;
	_RecordsetPtr	m_pRecordset;
	
 	m_pConnection.CreateInstance(__uuidof(Connection));
 	m_pRecordset.CreateInstance(__uuidof(Recordset));
// 	try
// 	{	//Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" & dbPath & ";Persist Security Info=False
 		m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source='001.mdb'","","",adModeUnknown);
// 	}
// 	catch(_com_error *e)
// 	{
// 		AfxMessageBox(e->ErrorMessage());
// 	}
}


DWORD WINAPI Fun1Proc(LPVOID lpParameter)
{
	//coinc
// 	_ConnectionPtr	m_pConnection;
// 	HRESULT hr = m_pConnection.CreateInstance("ADODB.Connection");
// 	if (FAILED(hr))
// 	{
// 		_com_error e(hr);
// 		AfxMessageBox(e.ErrorMessage());
// 		return 0;
// 	}
	//SetWindowText(0,"111");
	//SetDlgItemText(1,IDC_STATIC, "");
	//::CoInitialize(NULL);
//	testBBBB();
	//::CoUninitialize();
//	Sleep(2000);
	return 0;
}

void CFlashCE2Dlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	//AfxOleInit();
	//直接调用
// 	testAAAA();
// 	//线程里调用
//    	HANDLE hThread1;
//    	hThread1=CreateThread(NULL,0,Fun1Proc,NULL,0,NULL);
//    	CloseHandle(hThread1);

//	testHAHA();
}
