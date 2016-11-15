// CAC.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CAC.h"
#include "CACDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCACApp

BEGIN_MESSAGE_MAP(CCACApp, CWinApp)
	//{{AFX_MSG_MAP(CCACApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCACApp construction

CCACApp::CCACApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCACApp object

CCACApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCACApp initialization

BOOL CCACApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Standard initialization

	//初始化ROOM_AMOUNT个房间
	for (int i = 0 ; i <= ROOM_AMOUNT - 1; i ++)
	{
		rooms[i].setRoomNo(100 + i);
		rooms[i].setCurTemp(0);
		rooms[i].setTarTemp(0);
		rooms[i].setSpeed(0);
		rooms[i].setState(CLOSED);
	}

	//中央空调初始时处于关闭状态
	central.setState(CLOSED);

	//设置对话框颜色
	SetDialogBkColor(DLG_BG_COLOR,DLG_TEXT_COLOR);

	//设置提示框标题栏
	AfxGetApp()-> m_pszAppName = "系统提示";


	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CCACDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
