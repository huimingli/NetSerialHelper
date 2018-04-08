; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CNetProjectDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "NetProject.h"

ClassCount=3
Class1=CNetProjectApp
Class2=CNetProjectDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_NETPROJECT_DIALOG

[CLS:CNetProjectApp]
Type=0
HeaderFile=NetProject.h
ImplementationFile=NetProject.cpp
Filter=N

[CLS:CNetProjectDlg]
Type=0
HeaderFile=NetProjectDlg.h
ImplementationFile=NetProjectDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT_IP

[CLS:CAboutDlg]
Type=0
HeaderFile=NetProjectDlg.h
ImplementationFile=NetProjectDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_NETPROJECT_DIALOG]
Type=1
Class=CNetProjectDlg
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_EDIT_SEND,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_IP,edit,1350631552
Control9=IDC_EDIT_PORT,edit,1350631552
Control10=IDC_EDIT_NICKNAME,edit,1350631552
Control11=IDC_LIST_RECEIVE,listbox,1352728835

