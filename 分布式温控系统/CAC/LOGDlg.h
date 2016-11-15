#if !defined(AFX_LOGDLG_H__AB0B0A1E_CDC7_4C3E_8505_FAA926CBC113__INCLUDED_)
#define AFX_LOGDLG_H__AB0B0A1E_CDC7_4C3E_8505_FAA926CBC113__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LOGDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLOGDlg dialog

class CLOGDlg : public CDialog
{
// Construction
public:
	CLOGDlg(CWnd* pParent = NULL);   // standard constructor

	CBrush m_editbrush;//±à¼­¿òË¢
	CBrush m_staticbrush;//¾²Ì¬ÎÄ±¾¿òË¢

// Dialog Data
	//{{AFX_DATA(CLOGDlg)
	enum { IDD = IDD_LOG_DIALOG };
	CTransParentButton	m_close_button;
	CListCtrl	m_list;
	CDateTimeCtrl	m_time;
	CComboBox	m_room;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLOGDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLOGDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGDLG_H__AB0B0A1E_CDC7_4C3E_8505_FAA926CBC113__INCLUDED_)
