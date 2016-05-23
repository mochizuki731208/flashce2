; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFlashCE2Dlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "FlashCE2抓包.h"

ClassCount=6
Class1=CFlashCE2App
Class2=CFlashCE2Dlg
Class3=CAboutDlg

ResourceCount=6
Resource1=IDD_FLASHCE2_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_DIALOG2
Class4=CTabForm
Resource4=IDD_DIALOG1
Class5=CTabFormSet
Resource5=IDD_ABOUTBOX
Class6=CTabFormRule
Resource6=IDD_DIALOG3

[CLS:CFlashCE2App]
Type=0
HeaderFile=FlashCE2抓包.h
ImplementationFile=FlashCE2抓包.cpp
Filter=N

[CLS:CFlashCE2Dlg]
Type=0
HeaderFile=FlashCE2抓包Dlg.h
ImplementationFile=FlashCE2抓包Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_COMBO1

[CLS:CAboutDlg]
Type=0
HeaderFile=FlashCE2抓包Dlg.h
ImplementationFile=FlashCE2抓包Dlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_FLASHCE2_DIALOG]
Type=1
Class=CFlashCE2Dlg
ControlCount=6
Control1=IDC_TAB1,SysTabControl32,1342177280
Control2=IDC_COMBO1,combobox,1344340226
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_BUTTON2,button,1342242816
Control5=IDC_STATIC1,static,1342308352
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG1]
Type=1
Class=CTabForm
ControlCount=1
Control1=IDC_LIST1,SysListView32,1350631425

[CLS:CTabForm]
Type=0
HeaderFile=TabForm.h
ImplementationFile=TabForm.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_LIST1
VirtualFilter=dWC

[DLG:IDD_DIALOG2]
Type=1
Class=CTabFormSet
ControlCount=5
Control1=IDC_STATIC,button,1342177287
Control2=IDC_CHECK1,button,1342242819
Control3=IDC_CHECK2,button,1342242819
Control4=IDC_CHECK3,button,1342242819
Control5=IDC_CHECK4,button,1342242819

[CLS:CTabFormSet]
Type=0
HeaderFile=TabFormSet.h
ImplementationFile=TabFormSet.cpp
BaseClass=CDialog
Filter=D

[DLG:IDD_DIALOG3]
Type=1
Class=CTabFormRule
ControlCount=11
Control1=IDC_STATIC,button,1342177287
Control2=IDC_CHECK_LX_HL,button,1342242819
Control3=IDC_CHECK_LX_ZL,button,1342242819
Control4=IDC_CHECK_LX_HD,button,1342242819
Control5=IDC_CHECK_LX_ZD,button,1342242819
Control6=IDC_STATIC,button,1342177287
Control7=IDC_CHECK_DJ_YZ,button,1342242819
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT_DJ_NUM,edit,1350631552
Control10=IDC_STATIC,button,1342177287
Control11=IDC_CHECK6,button,1342242819

[CLS:CTabFormRule]
Type=0
HeaderFile=TabFormRule.h
ImplementationFile=TabFormRule.cpp
BaseClass=CDialog
Filter=D
LastObject=CTabFormRule

