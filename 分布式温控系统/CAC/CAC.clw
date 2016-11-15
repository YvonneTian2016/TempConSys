; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLOGDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CAC.h"

ClassCount=8
Class1=CCACApp
Class2=CCACDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CTransParentButton
Resource3=IDD_CAC_DIALOG
Class5=CModifyFreq
Class6=CCentralSocket
Class7=CSlaveSocket
Resource4=IDD_MODIFY_FREQ
Class8=CLOGDlg
Resource5=IDD_LOG_DIALOG

[CLS:CCACApp]
Type=0
HeaderFile=CAC.h
ImplementationFile=CAC.cpp
Filter=N
LastObject=CCACApp

[CLS:CCACDlg]
Type=0
HeaderFile=CACDlg.h
ImplementationFile=CACDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_CHECK_LOG

[CLS:CAboutDlg]
Type=0
HeaderFile=CACDlg.h
ImplementationFile=CACDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CAC_DIALOG]
Type=1
Class=CCACDlg
ControlCount=25
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT_INI_CUR_TEMP,edit,1342242944
Control4=IDC_OPEN,button,1342242816
Control5=IDC_EDIT_INI_TAR_TEMP,edit,1342242944
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_CLOSE,button,1342242816
Control9=IDC_ROOM_LIST,SysListView32,1350633473
Control10=IDC_RADIO_COLD,button,1342308361
Control11=IDC_RADIO_WARM,button,1342177289
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_EDIT_MODE,edit,1342244992
Control20=IDC_EDIT_STATE,edit,1342244992
Control21=IDC_EDIT_TIME,edit,1342244992
Control22=IDC_UPDATE_RATE,button,1342242816
Control23=IDC_STATIC,static,1342308352
Control24=IDC_EDIT_HOST_IP,edit,1476460672
Control25=IDC_CHECK_LOG,button,1342242816

[CLS:CTransParentButton]
Type=0
HeaderFile=TransParentButton.h
ImplementationFile=TransParentButton.cpp
BaseClass=CButton
Filter=W
VirtualFilter=BWC
LastObject=CTransParentButton

[DLG:IDD_MODIFY_FREQ]
Type=1
Class=CModifyFreq
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_CUR_FREQ,edit,1342244864
Control6=IDC_NEW_FREQ,edit,1342251136
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[CLS:CModifyFreq]
Type=0
HeaderFile=ModifyFreq.h
ImplementationFile=ModifyFreq.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CModifyFreq

[CLS:CCentralSocket]
Type=0
HeaderFile=CentralSocket.h
ImplementationFile=CentralSocket.cpp
BaseClass=CSocket
Filter=N
LastObject=CCentralSocket
VirtualFilter=uq

[CLS:CSlaveSocket]
Type=0
HeaderFile=SlaveSocket.h
ImplementationFile=SlaveSocket.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq
LastObject=CSlaveSocket

[DLG:IDD_LOG_DIALOG]
Type=1
Class=CLOGDlg
ControlCount=7
Control1=ID_CLOSE,button,1342242817
Control2=IDC_LOG_LIST,SysListView32,1350635521
Control3=IDC_DATETIMEPICKER,SysDateTimePick32,1342242848
Control4=IDC_COMBO_ROOM,combobox,1342242819
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[CLS:CLOGDlg]
Type=0
HeaderFile=LOGDlg.h
ImplementationFile=LOGDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_LOG_LIST
VirtualFilter=dWC

