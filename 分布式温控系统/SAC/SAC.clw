; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSACDlg
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SAC.h"

ClassCount=5
Class1=CSACApp
Class2=CSACDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CTransParentButton
Class5=CSlaveSocket
Resource3=IDD_SAC_DIALOG

[CLS:CSACApp]
Type=0
HeaderFile=SAC.h
ImplementationFile=SAC.cpp
Filter=N
LastObject=CSACApp

[CLS:CSACDlg]
Type=0
HeaderFile=SACDlg.h
ImplementationFile=SACDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=ID_CLOSE

[CLS:CAboutDlg]
Type=0
HeaderFile=SACDlg.h
ImplementationFile=SACDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SAC_DIALOG]
Type=1
Class=CSACDlg
ControlCount=20
Control1=ID_OPEN,button,1342242817
Control2=ID_CLOSE,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_CONNECT,button,1342242816
Control5=IDC_EDIT_IP,edit,1342242944
Control6=IDC_STATIC,button,1342210055
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_CUR_TEMP,edit,1476460672
Control9=IDC_STATIC,static,1342308352
Control10=IDC_SPIN_TAR,msctls_updown32,1342177312
Control11=IDC_EDIT_TAR_TEMP,edit,1476460672
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_EDIT_STATE,edit,1476460672
Control16=IDC_EDIT_MODE,edit,1476460672
Control17=IDC_EDIT_SPEED,edit,1476460672
Control18=IDC_STATIC,static,1342308352
Control19=IDC_SPIN_SPEED,msctls_updown32,1342177312
Control20=IDC_STATIC,static,1342308352

[CLS:CTransParentButton]
Type=0
HeaderFile=TransParentButton.h
ImplementationFile=TransParentButton.cpp
BaseClass=CButton
Filter=W
LastObject=CTransParentButton

[CLS:CSlaveSocket]
Type=0
HeaderFile=SlaveSocket.h
ImplementationFile=SlaveSocket.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq
LastObject=CSlaveSocket

