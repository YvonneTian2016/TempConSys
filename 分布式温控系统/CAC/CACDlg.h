// CACDlg.h : header file
//
#include "Resource.h"
#include "SlaveSocket.h"

#if !defined(AFX_CACDLG_H__4182ACFB_8165_4B9E_9621_EE8C4B1224D4__INCLUDED_)
#define AFX_CACDLG_H__4182ACFB_8165_4B9E_9621_EE8C4B1224D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCACDlg dialog

class CCACDlg : public CDialog
{
// Construction
public:
	CCACDlg(CWnd* pParent = NULL);	// standard constructor

	void setListInfo(void);//设置房间情况列表信息
	void initiation(void);//初始化数据
	void acceptConnection(void);//接受来自从控端的连接请求
	void receivePacket(CSocket &slave_socket);//接受来自从控端的数据包
	void sendPacket(CSocket &slave_socket,int i);//向从控端发送数据包

// Dialog Data
	//{{AFX_DATA(CCACDlg)
	enum { IDD = IDD_CAC_DIALOG };
	CTransParentButton	m_check_log;
	CEdit	m_state_ctrl;
	CEdit	m_mode_ctrl;
	CEdit	m_time_ctrl;
	CTransParentButton	m_update_rate;
	CEdit	m_ini_tar_temp_ctrl;
	CEdit	m_ini_cur_temp_ctrl;
	CButton	m_mode_select;
	CListCtrl	m_room_list;
	CTransParentButton	m_close;
	CTransParentButton	m_open;
	float	m_ini_cur_temp;
	float	m_ini_tar_temp;
	CString	m_mode_text;
	CString	m_state_text;
	CString	m_time_text;
	CString	m_host_ip_text;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCACDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	CBrush m_editbrush;//编辑框刷
	CBrush m_staticbrush;//静态文本框刷

	// Generated message map functions
	//{{AFX_MSG(CCACDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnOpen();
	afx_msg void OnCloseClicked();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnUpdateRate();
	afx_msg void OnClose();
	afx_msg void OnCheckLog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CACDLG_H__4182ACFB_8165_4B9E_9621_EE8C4B1224D4__INCLUDED_)
