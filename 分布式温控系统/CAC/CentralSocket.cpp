// CentralSocket.cpp : implementation file
//

#include "stdafx.h"
#include "CAC.h"
#include "CentralSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCentralSocket

CCentralSocket::CCentralSocket()
{
}

CCentralSocket::~CCentralSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CCentralSocket, CSocket)
	//{{AFX_MSG_MAP(CCentralSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CCentralSocket member functions

void CCentralSocket::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class	
	if (dlgp)
		dlgp->acceptConnection();		//接受连接
	CSocket::OnAccept(nErrorCode);
}

void CCentralSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CSocket::OnReceive(nErrorCode);
}
