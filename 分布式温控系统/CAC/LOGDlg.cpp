// LOGDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CAC.h"
#include "LOGDlg.h"
#include "TransParentButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLOGDlg dialog


CLOGDlg::CLOGDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLOGDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLOGDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLOGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLOGDlg)
	DDX_Control(pDX, ID_CLOSE, m_close_button);
	DDX_Control(pDX, IDC_LOG_LIST, m_list);
	DDX_Control(pDX, IDC_DATETIMEPICKER, m_time);
	DDX_Control(pDX, IDC_COMBO_ROOM, m_room);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLOGDlg, CDialog)
	//{{AFX_MSG_MAP(CLOGDlg)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(ID_CLOSE, OnClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLOGDlg message handlers

BOOL CLOGDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRect rect;
	GetClientRect(&rect);
	CString temp;
	temp.Format("%d %d",rect.Width(),rect.Height());
	m_room.AddString(temp);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CLOGDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CLOGDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
		//装载背景位图 										   
        CDC BmpDC;   
        CBitmap Mybmp;													  
        CBitmap * OldBmp;   
        CRect rect;   
        Mybmp.LoadBitmap(IDB_BITMAP_BG3); 
        GetClientRect(&rect);										  
        BmpDC.CreateCompatibleDC(& dc);   
        OldBmp = BmpDC.SelectObject(& Mybmp);   
		BITMAP bm;
		memset( &bm, 0, sizeof(bm) );
		Mybmp.GetBitmap(&bm);
        dc.StretchBlt(0,0,rect.Width(),rect.Height(),& BmpDC,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);   
        BmpDC.SelectObject(OldBmp); 
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CLOGDlg::OnClose() 
{
	// TODO: Add your control notification handler code here
	SendMessage(WM_CLOSE);
	
}
