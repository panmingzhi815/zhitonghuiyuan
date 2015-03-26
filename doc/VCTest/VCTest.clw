; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CVCTestDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "VCTest.h"

ClassCount=3
Class1=CVCTestApp
Class2=CVCTestDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_VCTEST_DIALOG
Resource4=IDR_PICMENU

[CLS:CVCTestApp]
Type=0
HeaderFile=VCTest.h
ImplementationFile=VCTest.cpp
Filter=N

[CLS:CVCTestDlg]
Type=0
HeaderFile=VCTestDlg.h
ImplementationFile=VCTestDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_CHECK_HIGHT

[CLS:CAboutDlg]
Type=0
HeaderFile=VCTestDlg.h
ImplementationFile=VCTestDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_VCTEST_DIALOG]
Type=1
Class=CVCTestDlg
ControlCount=23
Control1=IDC_BUTTON_SCAN,button,1342242816
Control2=IDC_BUTTON_CONNECT,button,1342242816
Control3=IDC_STATIC_BIGIMAGE,static,1342177287
Control4=IDC_STATIC_CIFIMAGE,static,1342177287
Control5=IDC_STATIC_PLATEIMAGE,static,1342177287
Control6=IDC_STATIC_PLATE,static,1342177287
Control7=IDC_STATIC,button,1342177287
Control8=IDC_LIST_DEVICE,SysListView32,1350631437
Control9=IDC_BUTTON_CAPTURE,button,1342242816
Control10=IDC_BUTTON_VERIFYTIME,button,1342242816
Control11=IDC_BUTTON_SETNETPARAMS,button,1342242816
Control12=IDC_CHECK_NTP,button,1342242819
Control13=IDC_CHECK_TCP,button,1342242819
Control14=IDC_BUTTON_DISCONNECT,button,1342242816
Control15=IDC_CHECK_TIMER,button,1342242819
Control16=IDC_EDIT_TIMEOUT,edit,1350639744
Control17=IDC_STATIC,static,1342308352
Control18=IDC_BUTTON_GETPARAMS,button,1342242816
Control19=IDC_STATIC,button,1342177287
Control20=IDC_TREE_DEVICE,SysTreeView32,1350631687
Control21=IDC_BUTTON_GETVERSION,button,1342242816
Control22=IDC_BUTTON_GETALGPARAMS,button,1342242816
Control23=IDC_CHECK_HIGHT,button,1342242819

[MNU:IDR_PICMENU]
Type=1
Class=?
Command1=IDM_ZOOMVALID
CommandCount=1

