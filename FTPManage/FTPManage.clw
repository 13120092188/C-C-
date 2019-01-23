; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CFormView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ftpmanage.h"
LastPage=0

ClassCount=11
Class1=CFTPManageApp
Class2=CAboutDlg
Class3=CFTPManageDoc
Class4=CFTPManageView
Class5=CLinkServer
Class6=CMainFrame
Class7=CSortHeaderCtrl
Class8=CSortListCtrl
Class9=CTastListView

ResourceCount=11
Resource1=IDD_LINKSERVER_DIALOG
Resource2=IDD_CONNECTFTPDLG
Resource3=IDD_TOOLBAR
Resource4=IDR_LOCALVIEW_TMPL
Resource5=IDD_LOCALVIEW_FORM
Resource6=IDD_ABOUTBOX
Resource7=IDD_TASTLISTVIEW_FORM
Resource8=IDR_FTPVIEW_TMPL
Class10=CLocalView
Resource9=IDR_MAINFRAME
Resource10=IDR_TASTLISTVIEW_TMPL
Class11=CFTPView
Resource11=IDD_FTPVIEW_FORM

[CLS:CFTPManageApp]
Type=0
BaseClass=CWinApp
HeaderFile=FTPManage.h
ImplementationFile=FTPManage.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=FTPManage.cpp
ImplementationFile=FTPManage.cpp
LastObject=CAboutDlg

[CLS:CFTPManageDoc]
Type=0
BaseClass=CDocument
HeaderFile=FTPManageDoc.h
ImplementationFile=FTPManageDoc.cpp

[CLS:CFTPManageView]
Type=0
BaseClass=CView
HeaderFile=FTPManageView.h
ImplementationFile=FTPManageView.cpp

[CLS:CLinkServer]
Type=0
BaseClass=CDialog
HeaderFile=LinkServer.h
ImplementationFile=LinkServer.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=CMainFrame

[CLS:CSortHeaderCtrl]
Type=0
BaseClass=CHeaderCtrl
HeaderFile=SortHeaderCtrl.h
ImplementationFile=SortHeaderCtrl.cpp

[CLS:CSortListCtrl]
Type=0
BaseClass=CListCtrl
HeaderFile=SortListCtrl.h
ImplementationFile=SortListCtrl.cpp

[CLS:CTastListView]
Type=0
BaseClass=CFormView
HeaderFile=TastList.h
ImplementationFile=TastList.cpp
Filter=D
VirtualFilter=VWC
LastObject=IDC_BT_STOP

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_LINKSERVER_DIALOG]
Type=1
Class=CLinkServer
ControlCount=21
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_FTPSERVER,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_FTPPORT,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_USER,edit,1350631552
Control9=IDC_PASSWORD,edit,1350631584
Control10=IDC_LOGIN_FTP,button,1342242816
Control11=IDC_LOCALFILES,SysListView32,1350631425
Control12=IDC_FRAME,static,1342177287
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_REMOTEFILES,SysListView32,1350631425
Control16=IDC_UPLOAD,button,1342242816
Control17=IDC_TASKLIST,SysListView32,1350631425
Control18=IDC_DOWNLOAD,button,1342242816
Control19=IDC_BT_STOP,button,1342242816
Control20=IDC_BT_DELETE,button,1342242816
Control21=IDC_BT_CONTINUE,button,1342242816

[DLG:IDD_TASTLISTVIEW_FORM]
Type=1
Class=CTastListView
ControlCount=4
Control1=IDC_TASKLIST,SysListView32,1350631425
Control2=IDC_BT_STOP,button,1342242816
Control3=IDC_BT_DELETE,button,1342242816
Control4=IDC_BT_CONTINUE,button,1342242816

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_CONNECTBAR
Command2=ID_TOOLBARINFO
Command3=ID_DOWNLOAD
Command4=ID_UPLOAD
Command5=ID_TURNOFF
Command6=ID_APP_ABOUT
CommandCount=6

[MNU:IDR_TASTLISTVIEW_TMPL]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_CONNECTFTPDLG]
Type=1
Class=?
ControlCount=9
Control1=IDC_STATIC,static,1342308352
Control2=IDC_FTPSERVER,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_FTPPORT,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_USER,edit,1350631552
Control8=IDC_PASSWORD,edit,1350631584
Control9=IDC_LOGIN_FTP,button,1342242816

[DLG:IDD_TOOLBAR]
Type=1
Class=?
ControlCount=5
Control1=IDC_BT_UPLOAD,button,1342242816
Control2=IDC_BT_DOWNLOAD,button,1342242816
Control3=IDC_SETDIR,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_SAVEDIR,edit,1350633600

[DLG:IDD_LOCALVIEW_FORM]
Type=1
Class=CLocalView
ControlCount=4
Control1=IDC_LOCALFILES,SysListView32,1350631425
Control2=IDC_FRAME,static,1342177287
Control3=IDC_STATIC,static,1342308352
Control4=IDC_BACK,static,1342177550

[CLS:CLocalView]
Type=0
HeaderFile=LocalView.h
ImplementationFile=LocalView.cpp
BaseClass=CFormView
Filter=D
VirtualFilter=VWC
LastObject=IDC_LOCALFILES

[MNU:IDR_LOCALVIEW_TMPL]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

[DLG:IDD_FTPVIEW_FORM]
Type=1
Class=CFTPView
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDC_REMOTEFILES,SysListView32,1350631425
Control3=IDC_BACK,static,1342177550

[CLS:CFTPView]
Type=0
HeaderFile=FTPView.h
ImplementationFile=FTPView.cpp
BaseClass=CFormView
Filter=D
VirtualFilter=VWC
LastObject=IDC_REMOTEFILES

[MNU:IDR_FTPVIEW_TMPL]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

