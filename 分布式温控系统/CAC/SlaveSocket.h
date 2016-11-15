#if !defined(AFX_SLAVESOCKET_H__051B5823_4A00_45B6_B9FC_719085CDDF23__INCLUDED_)
#define AFX_SLAVESOCKET_H__051B5823_4A00_45B6_B9FC_719085CDDF23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SlaveSocket.h : header file
//
#include "CACDlg.h"


/////////////////////////////////////////////////////////////////////////////
// CSlaveSocket command target

class CSlaveSocket : public CSocket
{
// Attributes
public:
	CCACDlg* dlgp;					//通过该指针调用对话框的成员函数
// Operations
public:
	CSlaveSocket();
	virtual ~CSlaveSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSlaveSocket)
	public:
	virtual void OnClose(int nErrorCode);
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

#endif // !defined(AFX_SLAVESOCKET_H__051B5823_4A00_45B6_B9FC_719085CDDF23__INCLUDED_)
