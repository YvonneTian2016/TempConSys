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

	VIRTUALTIME system_time;//ϵͳʱ��
	int refresh_freq;//�б�ˢ��Ƶ��
	bool change_freq;//�б�ˢ���ʸı��־
	int room_to_wait;//���ؾ������ʱ����ǿ�ƴ����Ĵӿػ����
	r_record r;//�ձ�����Ӽ�¼�ṹ
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
