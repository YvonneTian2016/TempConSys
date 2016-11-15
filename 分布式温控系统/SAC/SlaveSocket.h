#if !defined(AFX_SLAVESOCKET_H__E124AC55_BC68_48BF_9914_72A5B205DDA2__INCLUDED_)
#define AFX_SLAVESOCKET_H__E124AC55_BC68_48BF_9914_72A5B205DDA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SlaveSocket.h : header file
//
#include "SACDlg.h"



/////////////////////////////////////////////////////////////////////////////
// CSlaveSocket command target

class CSlaveSocket : public CSocket
{
// Attributes
public:
   CSACDlg* dlgp;					//通过该指针调用对话框的成员函数
// Operations
public:
	CSlaveSocket();
	virtual ~CSlaveSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSlaveSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSlaveSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLAVESOCKET_H__E124AC55_BC68_48BF_9914_72A5B205DDA2__INCLUDED_)
