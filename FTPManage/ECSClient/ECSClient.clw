; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSendDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ecsclient.h"
LastPage=0

ClassCount=7
Class1=CClientSock
Class2=CECSClientApp
Class3=CAboutDlg
Class4=CECSClientDlg
Class5=CSendDlg

ResourceCount=4
Resource1=IDD_ECSCLIENT_DIALOG
Resource2=IDD_SENDDLG_DIALOG
Class6=CRvFileSock
Resource3=IDD_ABOUTBOX
Class7=CLogin
Resource4=IDD_LOGIN_DIALOG

[CLS:CClientSock]
Type=0
BaseClass=CSocket
HeaderFile=ClientSock.h
ImplementationFile=ClientSock.cpp

[CLS:CECSClientApp]
Type=0
BaseClass=CWinApp
HeaderFile=ECSClient.h
ImplementationFile=ECSClient.cpp
Filter=N
VirtualFilter=AC

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ECSClientDlg.cpp
ImplementationFile=ECSClientDlg.cpp

[CLS:CECSClientDlg]
Type=0
BaseClass=CDialog
HeaderFile=ECSClientDlg.h
ImplementationFile=ECSClientDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CECSClientDlg

[CLS:CSendDlg]
Type=0
BaseClass=CDialog
HeaderFile=SendDlg.h
ImplementationFile=SendDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_SHOWLIST

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ECSCLIENT_DIALOG]
Type=1
Class=CECSClientDlg
ControlCount=1
Control1=IDC_ACLIST,SysTreeView32,1350631431

[DLG:IDD_SENDDLG_DIALOG]
Type=1
Class=CSendDlg
ControlCount=17
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,button,1342177287
Control3=IDC_SHOWLIST,RICHEDIT,1353783492
Control4=IDC_SENDLIST,RICHEDIT,1353781444
Control5=IDC_BTSEND,button,1342242816
Control6=IDC_CLOSE,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_DESID,combobox,1344340227
Control9=IDC_STATIC,static,1342308352
Control10=IDC_DESNAME,combobox,1344340227
Control11=IDC_STATIC,static,1342308352
Control12=IDC_LOCALID,edit,1350633600
Control13=IDC_STATIC,static,1342308352
Control14=IDC_LOCALNAME,edit,1350633600
Control15=IDC_SEND_FILE,button,1342242816
Control16=IDC_FILEPROGRESS,msctls_progress32,1082130433
Control17=IDC_CHOOSE_IMG,button,1342242816

[CLS:CRvFileSock]
Type=0
HeaderFile=RvFileSock.h
ImplementationFile=RvFileSock.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq

[DLG:IDD_LOGIN_DIALOG]
Type=1
Class=CLogin
ControlCount=13
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_USERID,edit,1350639744
Control4=IDC_STATIC,static,1342308352
Control5=IDC_PASSWORD,edit,1350631584
Control6=IDC_BT_LOGIN,button,1342242816
Control7=IDC_BT_CANCEL,button,1342242816
Control8=IDC_STATIC,button,1342177287
Control9=IDC_SVRIP,SysIPAddress32,1342242816
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_SVRPORT,edit,1350639744
Control13=IDC_CHK_AUTOLOGIN,button,1342242819

[CLS:CLogin]
Type=0
HeaderFile=Login.h
ImplementationFile=Login.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

