// CAC.h : main header file for the CAC application
//

#if !defined(AFX_CAC_H__76764F57_EB2F_400D_A27B_645A30DBF258__INCLUDED_)
#define AFX_CAC_H__76764F57_EB2F_400D_A27B_645A30DBF258__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCACApp:
// See CAC.cpp for the implementation of this class
//

class CCACApp : public CWinApp
{
public:
	CCACApp();

	VIRTUALTIME system_time;//系统时间
	int refresh_freq;//列表刷新频率
	bool change_freq;//列表刷新率改变标志
	int room_to_wait;//负载均衡调度时，被强制待机的从控机编号
	r_record r;//日报表添加记录结构
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCACApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCACApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAC_H__76764F57_EB2F_400D_A27B_645A30DBF258__INCLUDED_)
