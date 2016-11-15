// ModifyFreq.cpp : implementation file
//

#include "stdafx.h"
#include "CAC.h"
#include "ModifyFreq.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModifyFreq dialog


CModifyFreq::CModifyFreq(CWnd* pParent /*=NULL*/)
	: CDialog(CModifyFreq::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModifyFreq)
	m_cur_number = 0;
	m_new_number = 0;
	//}}AFX_DATA_INIT
}


void CModifyFreq::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModifyFreq)
	DDX_Control(pDX, IDC_NEW_FREQ, m_new_ctrl);
	DDX_Control(pDX, IDC_CUR_FREQ, m_cur_ctrl);
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Text(pDX, IDC_CUR_FREQ, m_cur_number);
	DDV_MinMaxInt(pDX, m_cur_number, 1, 5);
	DDX_Text(pDX, IDC_NEW_FREQ, m_new_number);
	DDV_MinMaxInt(pDX, m_new_number, 1, 5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModifyFreq, CDialog)
	//{{AFX_MSG_MAP(CModifyFreq)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModifyFreq message handlers

HBRUSH CModifyFreq::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	switch (nCtlColor) 
	{
		// process my edit controls by ID.
		case CTLCOLOR_EDIT:
		case CTLCOLOR_MSGBOX:
		case CTLCOLOR_LISTBOX://若控件是文本框、列表框、消息框

			pDC->SetBkColor(EDIT_BG_COLOR);    // change the background
			pDC->SetTextColor(EDIT_TEXT_COLOR); // change the text color
			hbr = (HBRUSH) m_editbrush;    
			break;
		case CTLCOLOR_STATIC://若控件为静态文本框
			pDC-> SetBkMode(TRANSPARENT);
			hbr  =  (HBRUSH)::GetStockObject(NULL_BRUSH);
			break;
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CModifyFreq::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	//装载背景位图 										   
    CDC BmpDC;   
    CBitmap Mybmp;													  
    CBitmap * OldBmp;   
    CRect rect;   
    Mybmp.LoadBitmap(IDB_BITMAP_BG2); 
    GetClientRect(&rect);										  
    BmpDC.CreateCompatibleDC(& dc);   
    OldBmp = BmpDC.SelectObject(& Mybmp);   
	BITMAP bm;
	memset( &bm, 0, sizeof(bm) );
	Mybmp.GetBitmap(&bm);
    dc.StretchBlt(0,0,rect.Width(),rect.Height(),& BmpDC,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);   
    BmpDC.SelectObject(OldBmp); 
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CModifyFreq::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(true);
	GLOBAL.refresh_freq = m_new_number * 1000;
	GLOBAL.change_freq = true;
	CDialog::OnOK();
}

BOOL CModifyFreq::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cur_ctrl.EnableWindow(FALSE);
	m_cur_number = GLOBAL.refresh_freq/1000;
	UpdateData(false);
	m_editbrush.CreateSolidBrush(EDIT_BG_COLOR); //创建设置编辑框颜色的刷子
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
