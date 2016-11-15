#if !defined(AFX_MODIFYFREQ_H__0660BD78_4C1B_48C0_8DD7_91D955029BF9__INCLUDED_)
#define AFX_MODIFYFREQ_H__0660BD78_4C1B_48C0_8DD7_91D955029BF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModifyFreq.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModifyFreq dialog

class CModifyFreq : public CDialog
{
// Construction
public:
	CModifyFreq(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModifyFreq)
	enum { IDD = IDD_MODIFY_FREQ };
	CEdit	m_new_ctrl;
	CEdit	m_cur_ctrl;
	CTransParentButton	m_cancel;
	CTransParentButton	m_ok;
	int		m_cur_number;
	int		m_new_number;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModifyFreq)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CBrush m_editbrush;//±à¼­¿òË¢
	CBrush m_staticbrush;//¾²Ì¬ÎÄ±¾¿òË¢
	// Generated message map functions
	//{{AFX_MSG(CModifyFreq)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFYFREQ_H__0660BD78_4C1B_48C0_8DD7_91D955029BF9__INCLUDED_)
