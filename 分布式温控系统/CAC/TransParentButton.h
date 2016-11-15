#if !defined(AFX_TRANSPARENTBUTTON_H__1988383D_963B_4860_8AF9_0A00BCFF2B86__INCLUDED_)
#define AFX_TRANSPARENTBUTTON_H__1988383D_963B_4860_8AF9_0A00BCFF2B86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransParentButton.h : header file
//
// the align of the icon
#define AL_LEFT     0
#define AL_TOP      1
// the state to draw
#define ST_MOVEIN    0
#define ST_MOVEOUT   1
#define ST_MOUSEUP   2
#define ST_MOUSEDOWN 3
/////////////////////////////////////////////////////////////////////////////
// CTransParentButton window

class CTransParentButton : public CButton
{
// Construction
public:
	CTransParentButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransParentButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetIcon(UINT  nNormal,UINT nMouseIn);
	BOOL SetCursor(UINT nCursorID);
	void SetStyle(bool bIsflat=false);
	void SetBkMode(bool bTransparent);
	void SetMouseDownTextColor(COLORREF color);
	void SetNormalTextColor(COLORREF color);
	void SetActiveTextColor(COLORREF color);
	void SetIconYPos(int y);
	void SetAlign(int nAlign);
	void SetIconXPos(int x);
	void Draw();
	void DrawIcon(HICON hIcon,BOOL bDisabled=FALSE);
	void DrawIcon();
	void SetIcon(HICON  hNormal,HICON hMouseIn);
	void DrawText();
	void Refresh();
	CDC memDC;
	bool m_bDCStored;
	bool m_bMove;
	void DrawBorders();
	virtual ~CTransParentButton();

	// Generated message map functions
protected:
	bool m_bIsEnabled;
	HCURSOR m_hCursor;
	bool m_bHasFocus;
	bool m_bIsFlat;
	bool m_bBkTransparent;
	COLORREF m_clText;
	COLORREF m_clMouseDownText;
	COLORREF m_clActiveText;
	COLORREF m_clNormalText;
	bool m_bUseIcon;
	int m_IconYPos;
	int m_IconXPos;
	int m_DrawState;
	int m_IconAlign;
	HICON m_hMouseInIcon;
	HICON m_hNormalIcon;
	//{{AFX_MSG(CTransParentButton)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSPARENTBUTTON_H__1988383D_963B_4860_8AF9_0A00BCFF2B86__INCLUDED_)
