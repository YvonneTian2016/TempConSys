#if !defined(AFX_CENTRALSOCKET_H__6AB44E29_3C8A_40CE_B861_EE8F73851E18__INCLUDED_)
#define AFX_CENTRALSOCKET_H__6AB44E29_3C8A_40CE_B861_EE8F73851E18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CentralSocket.h : header file
//
#include "CACDlg.h"



/////////////////////////////////////////////////////////////////////////////
// CCentralSocket command target

class CCentralSocket : public CSocket
{
// Attributes
public:
	CCACDlg* dlgp;					//通过该指针调用对话框的成员函数
// Operations
public:
	CCentralSocket();
	virtual ~CCentralSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCentralSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CCentralSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CENTRALSOCKET_H__6AB44E29_3C8A_40CE_B861_EE8F73851E18__INCLUDED_)
