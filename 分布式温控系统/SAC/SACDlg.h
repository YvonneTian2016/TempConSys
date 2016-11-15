// SACDlg.h : header file
//

#if !defined(AFX_SACDLG_H__5BA37532_CF4F_4A7A_8AEC_EA4A42C83025__INCLUDED_)
#define AFX_SACDLG_H__5BA37532_CF4F_4A7A_8AEC_EA4A42C83025__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Resource.h"

/////////////////////////////////////////////////////////////////////////////
// CSACDlg dialog

class CSACDlg : public CDialog
{
// Construction
public:
	CSACDlg(CWnd* pParent = NULL);	// standard constructor

	void initiation(void);

// Dialog Data
	//{{AFX_DATA(CSACDlg)
	enum { IDD = IDD_SAC_DIALOG };
	CEdit	m_mode_ctrl;
	CEdit	m_state_ctrl;
	CEdit	m_cur_temp_ctrl;
	CEdit	m_speed_text_ctrl;
	CEdit	m_tar_temp_ctrl;
	CEdit	m_ip_ctrl;
	CSpinButtonCtrl	m_tar_ctrl;
	CSpinButtonCtrl	m_speed_ctrl;
	CTransParentButton	m_connect;
	CTransParentButton	m_open;
	CTransParentButton	m_close;
	CTransParentButton	m_cancel;
	CTransParentButton	m_ok;
	CString	m_cur_temp_text;
	CString	m_ip_text;
	CString	m_mode_text;
	CString	m_state_text;
	CString	m_tar_temp_text;
	CString	m_speed_text;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSACDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	CBrush m_editbrush;//±à¼­¿òË¢
	CBrush m_staticbrush;//¾²Ì¬ÎÄ±¾¿òË¢
	// Generated message map functions
	//{{AFX_MSG(CSACDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnConnect();
	afx_msg void OnDeltaposSpinTar(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinSpeed(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOpen();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCloseClicked();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
void decode_packet(char* packet,int *type,double* ini_tar_temp,double* cur_temp);//½â°ü
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SACDLG_H__5BA37532_CF4F_4A7A_8AEC_EA4A42C83025__INCLUDED_)
