; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGoViewerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "GoViewer.h"

ClassCount=3
Class1=CGoViewerApp
Class2=CGoViewerDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_GOVIEWER_DIALOG
Resource4=IDR_MENU1

[CLS:CGoViewerApp]
Type=0
HeaderFile=GoViewer.h
ImplementationFile=GoViewer.cpp
Filter=N

[CLS:CGoViewerDlg]
Type=0
HeaderFile=GoViewerDlg.h
ImplementationFile=GoViewerDlg.cpp
Filter=D
LastObject=CGoViewerDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=GoViewerDlg.h
ImplementationFile=GoViewerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_GOVIEWER_DIALOG]
Type=1
Class=CGoViewerDlg
ControlCount=1
Control1=IDC_AI,button,1342242816

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=IDM_NEW
Command2=IDM_SAVE
Command3=IDM_LOAD
Command4=IDM_QUIT
CommandCount=4

