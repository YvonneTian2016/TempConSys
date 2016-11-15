// SlaveSocket.cpp : implementation file
//

#include "stdafx.h"
#include "CAC.h"
#include "SlaveSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSlaveSocket

CSlaveSocket::CSlaveSocket()
{
}

CSlaveSocket::~CSlaveSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSlaveSocket, CSocket)
	//{{AFX_MSG_MAP(CSlaveSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CSlaveSocket member functions

void CSlaveSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CSocket::OnClose(nErrorCode);
}

void CSlaveSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(dlgp)
	{
		dlgp->receivePacket(*this);			//调用主对话框类的receivePacket函数接收数据
	}
	CSocket::OnReceive(nErrorCode);
}

