; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDB_service_managerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DB_service_manager.h"

ClassCount=3
Class1=CDB_service_managerApp
Class2=CDB_service_managerDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_DB_SERVICE_MANAGER_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDR_RM

[CLS:CDB_service_managerApp]
Type=0
HeaderFile=DB_service_manager.h
ImplementationFile=DB_service_manager.cpp
Filter=N

[CLS:CDB_service_managerDlg]
Type=0
HeaderFile=DB_service_managerDlg.h
ImplementationFile=DB_service_managerDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CDB_service_managerDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=DB_service_managerDlg.h
ImplementationFile=DB_service_managerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DB_SERVICE_MANAGER_DIALOG]
Type=1
Class=CDB_service_managerDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDC_LIST,SysListView32,1350633491
Control3=IDC_SHOWALL,button,1342242819
Control4=IDC_REFILL,button,1342242816
Control5=IDC_STATIC1,static,1342308352

[MNU:IDR_RM]
Type=1
Class=?
Command1=ID_MENUITEM_START
Command2=ID_MENUITEM_STOP
Command3=ID_MENUITEM_AUTO
Command4=ID_MENUITEM_MANAGE
Command5=ID_MENUITEM_DISABLED
CommandCount=5

