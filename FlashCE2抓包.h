// FlashCE2抓包.h : main header file for the FLASHCE2抓包 application
//

#if !defined(AFX_FLASHCE2_H__058E5ED8_CC95_4291_82EF_0AD0B62E6389__INCLUDED_)
#define AFX_FLASHCE2_H__058E5ED8_CC95_4291_82EF_0AD0B62E6389__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFlashCE2App:
// See FlashCE2抓包.cpp for the implementation of this class
//

class CFlashCE2App : public CWinApp
{
public:
	CFlashCE2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlashCE2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFlashCE2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLASHCE2_H__058E5ED8_CC95_4291_82EF_0AD0B62E6389__INCLUDED_)
