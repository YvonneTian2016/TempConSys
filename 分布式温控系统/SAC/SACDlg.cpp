// SACDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SAC.h"
#include "SACDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSACDlg dialog

CSACDlg::CSACDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSACDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSACDlg)
	m_cur_temp_text = _T("");
	m_ip_text = _T("");
	m_mode_text = _T("");
	m_state_text = _T("");
	m_tar_temp_text = _T("");
	m_speed_text = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSACDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSACDlg)
	DDX_Control(pDX, IDC_EDIT_MODE, m_mode_ctrl);
	DDX_Control(pDX, IDC_EDIT_STATE, m_state_ctrl);
	DDX_Control(pDX, IDC_EDIT_CUR_TEMP, m_cur_temp_ctrl);
	DDX_Control(pDX, IDC_EDIT_SPEED, m_speed_text_ctrl);
	DDX_Control(pDX, IDC_EDIT_TAR_TEMP, m_tar_temp_ctrl);
	DDX_Control(pDX, IDC_EDIT_IP, m_ip_ctrl);
	DDX_Control(pDX, IDC_SPIN_TAR, m_tar_ctrl);
	DDX_Control(pDX, IDC_SPIN_SPEED, m_speed_ctrl);
	DDX_Control(pDX, IDC_CONNECT, m_connect);
	DDX_Control(pDX, ID_OPEN, m_open);
	DDX_Control(pDX, ID_CLOSE, m_close);
	DDX_Text(pDX, IDC_EDIT_CUR_TEMP, m_cur_temp_text);
	DDV_MaxChars(pDX, m_cur_temp_text, 10);
	DDX_Text(pDX, IDC_EDIT_IP, m_ip_text);
	DDV_MaxChars(pDX, m_ip_text, 16);
	DDX_Text(pDX, IDC_EDIT_MODE, m_mode_text);
	DDV_MaxChars(pDX, m_mode_text, 10);
	DDX_Text(pDX, IDC_EDIT_STATE, m_state_text);
	DDV_MaxChars(pDX, m_state_text, 10);
	DDX_Text(pDX, IDC_EDIT_TAR_TEMP, m_tar_temp_text);
	DDV_MaxChars(pDX, m_tar_temp_text, 10);
	DDX_Text(pDX, IDC_EDIT_SPEED, m_speed_text);
	DDV_MaxChars(pDX, m_speed_text, 10);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSACDlg, CDialog)
	//{{AFX_MSG_MAP(CSACDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TAR, OnDeltaposSpinTar)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SPEED, OnDeltaposSpinSpeed)
	ON_BN_CLICKED(ID_OPEN, OnOpen)
	ON_WM_TIMER()
	ON_BN_CLICKED(ID_CLOSE, OnCloseClicked)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSACDlg message handlers

void decode_packet(char* packet,int *type,double* ini_tar_temp,double* cur_temp)//解包
{
	(*type) = packet[0] - '0';
	(*ini_tar_temp) = (packet[1] - '0') * 10 + (packet[2] - '0')  + (packet[4] - '0') / 10.0;
	(*    cur_temp) = (packet[5] - '0') * 10 + (packet[6] - '0')  + (packet[8] - '0') / 10.0;
	return;
}

void make_send_packet(char* temp, int type, double ini_tar_temp, double cur_temp,int speed)//生成发送数据包
{
	//数据包类型
	temp[0] = type + '0';
	//初始目标温度
	temp[1] = ((int)(ini_tar_temp + 0.000001) / 10) + '0';
	temp[2] = ((int)(ini_tar_temp + 0.000001) % 10) + '0';
	temp[3] = '.';
	temp[4] = ((int)((ini_tar_temp * 10) + 0.5)) % 10 + '0';
	//当前室温
	temp[5] = ((int)(cur_temp + 0.000001) / 10) + '0';
	temp[6] = ((int)(cur_temp + 0.000001) % 10) + '0';
	temp[7] = '.';
	temp[8] = ((int)((cur_temp * 10) + 0.5)) % 10 + '0';
	temp[9] = speed + '0';
	temp[10] = '\0';
	return ;
}

void CSACDlg::initiation(void)//初始化数据
{
	CString hostip;
	char name[20]="";
	PHOSTENT hostinfo;//本机host信息

    //使用SOCKET前，检查SOCKET的安装情况
    WORD Version;
    WSADATA wsaData;
    Version=MAKEWORD(1,1);
    if (WSAStartup(Version,&wsaData))//在调用winsock函数之前，检查协议安装情况
	{
		AfxMessageBox("WINSOCK协议未安装。");
		return ;
	}
    if (wsaData.wVersion!=Version)//winsock版本不匹配
	{
	    WSACleanup();
	    return ;
	}
	//获取本机IP	
	if((hostinfo = gethostbyname(name)) != NULL)
	    hostip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);

	//设定房间的当前室温、目标温度、风速、工作状态、工作模式、送风量、费用、开关次数、IP、端口等信息
	room.setCurTemp(0.0);
	room.setTarTemp(25.0);
	room.setSpeed(NONE);
	room.setState(CLOSED);
	room.setMode(STANDBY);
	room.setAmount(0.0);
	room.setCost(0);
	room.setCount(0);
	room.setIP(hostip);
    room.setPort(5005);

	//风速、工作状态和目标温度改变标志置为假
	change_speed = change_tar_temp = change_state =false;

}

BOOL CSACDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	m_editbrush.CreateSolidBrush(EDIT_BG_COLOR); //创建设置编辑框颜色的刷子
	
	initiation();//初始化数据

	//初始化各项显示
	m_ip_text.Format(room.getIP());
	m_state_text.Format("关机");
	m_mode_text.Format("待定");
	m_speed_text.Format("待定");
	m_cur_temp_text.Format("0.0");
	m_tar_temp_text.Format("25.0");

	//初始时开机、关机、调节目标温度、调节风速等均不可用
	m_open.EnableWindow(false);
	m_close.EnableWindow(false);
	m_tar_ctrl.EnableWindow(false);
	m_speed_ctrl.EnableWindow(false);

	UpdateData(false);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSACDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSACDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//装载背景位图 
		CPaintDC dc (this);												   
        CDC BmpDC;   
        CBitmap Mybmp;													  
        CBitmap * OldBmp;   
        CRect rect;   
        Mybmp.LoadBitmap(IDB_BITMAP_BG); 
        GetClientRect(&rect);										  
        BmpDC.CreateCompatibleDC(& dc);   
        OldBmp = BmpDC.SelectObject(& Mybmp);   
		BITMAP bm;
		memset( &bm, 0, sizeof(bm) );
		Mybmp.GetBitmap(&bm);
        dc.StretchBlt(0,0,rect.Width(),rect.Height(),& BmpDC,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);   
        BmpDC.SelectObject(OldBmp); 

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSACDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

HBRUSH CSACDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

void CSACDlg::OnConnect() 
{
	// TODO: Add your control notification handler code here

	UpdateData(true);
	slave_socket.Create();	
	if (m_ip_text.IsEmpty())
	{
	    MessageBox("请输入主控端IP。");
		return;
	}
	if(slave_socket.Connect(m_ip_text, 5005))
	{
	    AfxMessageBox("连接主控端成功。");
		m_connect.EnableWindow(false);

		//此时开机按钮、调节风速等均可用,调节目标温度、IP输入框、关机按钮不可用
		m_ip_ctrl.EnableWindow(false);
		m_open.EnableWindow(true);
		m_tar_ctrl.EnableWindow(false);
		m_speed_ctrl.EnableWindow(true);

		//设定初始风速为中速
		room.setSpeed(MEDIUM);
		m_speed_text.Format("中速");
		UpdateData(false);
		m_speed_text_ctrl.ShowWindow(false);
		m_speed_text_ctrl.ShowWindow(true);	
	

	}
	else
	{
	    AfxMessageBox("连接失败。请检查输入的IP是否正确。");
		slave_socket.Close();
	}
}

void CSACDlg::OnDeltaposSpinTar(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	if (pNMUpDown->iDelta == -1) //升高目标温度
	{
		if (room.getMode() == WARM)
		{
			if (room.getTarTemp() < WARM_MAX)
				room.setTarTemp(room.getTarTemp() + 0.1);
			else
			{
			    AfxMessageBox("制热模式下，最大目标温度不超过30℃。");
				return;
			}
		}
		else if (room.getMode() == COLD)
		{
			if (room.getTarTemp() < COLD_MAX)
				room.setTarTemp(room.getTarTemp() + 0.1);
			else
			{
			    AfxMessageBox("制冷模式下，最大目标温度不超过25℃。");
				return;
			}
		}
		else
		{
		    if (room.getTarTemp() < WARM_MAX)
				room.setTarTemp(room.getTarTemp() + 0.1);
			else
				return;
		}
	}
	else if (pNMUpDown->iDelta == 1) //降低目标温度
	{
		if (room.getMode() == WARM)
		{
			if (room.getTarTemp() > WARM_MIN)
				room.setTarTemp(room.getTarTemp() - 0.1);
			else
			{
			    AfxMessageBox("制热模式下，最低目标温度不低于25℃。");
				return;
			}
		}
		else if (room.getMode() == COLD)
		{
			if (room.getTarTemp() > COLD_MIN)
				room.setTarTemp(room.getTarTemp() - 0.1);
			else
			{
			    AfxMessageBox("制冷模式下，最低目标温度不低于18℃。");
				return;
			}
		}
		else
		{
		    if (room.getTarTemp() > COLD_MIN)
				room.setTarTemp(room.getTarTemp() - 0.1);
			else
				return;
		}
	}
	m_tar_temp_text.Format("%.1lf",room.getTarTemp());
	UpdateData(false);
	m_cur_temp_ctrl.ShowWindow(false);
	m_cur_temp_ctrl.ShowWindow(true);
	m_tar_temp_ctrl.ShowWindow(false);
	m_tar_temp_ctrl.ShowWindow(true);

	//更改目标温度标志，表明目标温度已经改变
	change_tar_temp = true;

	*pResult = 0;
}

void CSACDlg::OnDeltaposSpinSpeed(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	if (pNMUpDown->iDelta == -1) 
	{
		if (room.getSpeed() == SLOW)
			room.setSpeed(MEDIUM);
		else if (room.getSpeed() == MEDIUM)
			room.setSpeed(FAST);
		else if (room.getSpeed() == FAST)
			return;
		else
			room.setSpeed(MEDIUM);
	}
	else if (pNMUpDown->iDelta == 1)
	{
		if (room.getSpeed() == SLOW)
			return;
		else if (room.getSpeed() == MEDIUM)
			room.setSpeed(SLOW);
		else if (room.getSpeed() == FAST)
			room.setSpeed(MEDIUM);
		else
			room.setSpeed(MEDIUM);
	}
	if (room.getSpeed() == SLOW)
		m_speed_text.Format("慢速");
	else if (room.getSpeed() == MEDIUM)
		m_speed_text.Format("中速");
	else if (room.getSpeed() == FAST)
		m_speed_text.Format("快速");
	else 
		m_speed_text.Format("待定");
	UpdateData(false);
	m_cur_temp_ctrl.ShowWindow(false);
	m_cur_temp_ctrl.ShowWindow(true);
	m_speed_text_ctrl.ShowWindow(false);
	m_speed_text_ctrl.ShowWindow(true);

	//更改目标温度标志，表明风速已经改变
	change_tar_temp = true;

	*pResult = 0;
}

void CSACDlg::OnOpen() 
{
	// TODO: Add your control notification handler code here
	char packet[11]="";
	int type;
	double ini_tar_temp,cur_temp;

//向主控端发送表示开机状态的数据包
	make_send_packet(packet,0,0,0,0);
    slave_socket.Send(packet,10,0);
//获取主控端发送的初始化信息
	slave_socket.Receive(packet,9,0);
	decode_packet(packet,&type,&ini_tar_temp,&cur_temp);
	if (type == 1)
	{
		room.setTarTemp(ini_tar_temp);
		room.setCurTemp(cur_temp);

		//设定初始室温。这是为从控端关机时正常显示初始室温所用
		GLOBAL.ini_cur_temp = cur_temp;
	}
	else if (type == 0)
	{
		AfxMessageBox("主控端已关机。");
	}
//根据初始化温度比较结果，设定工作模式,并设工作状态为待机
	if (ini_tar_temp < cur_temp)
		room.setMode(COLD);
	else if (ini_tar_temp > cur_temp)
		room.setMode(WARM);
	else
		room.setMode(STANDBY);
	room.setState(WAITING);

//更新界面显示
	m_tar_temp_text.Format("%.1lf",room.getTarTemp());
	m_cur_temp_text.Format("%.1lf",room.getCurTemp());
	//工作模式显示
	if (room.getMode() == COLD)
		m_mode_text.Format("制冷");
	else if (room.getMode() == WARM)
		m_mode_text.Format("制热");
	else
		m_mode_text.Format("待定");
	//工作状态显示
	m_state_text.Format("待机");

	UpdateData(false);

	m_state_ctrl.ShowWindow(false);
	m_state_ctrl.ShowWindow(true);

	m_mode_ctrl.ShowWindow(false);
	m_mode_ctrl.ShowWindow(true);

	m_tar_temp_ctrl.ShowWindow(false);
	m_tar_temp_ctrl.ShowWindow(true);

	m_cur_temp_ctrl.ShowWindow(false);
	m_cur_temp_ctrl.ShowWindow(true);

//启动全局计数器，作为与主控端的同步时钟
	SetTimer(GTimer,1000,NULL);

//此时关机按钮、调节目标温度、调节风速等均可用,开机按钮不可用
	m_open.EnableWindow(false);
	m_close.EnableWindow(true);
	m_tar_ctrl.EnableWindow(true);
	m_speed_ctrl.EnableWindow(true);
}


void CSACDlg::OnCloseClicked() 
{
	// TODO: Add your control notification handler code here
	char packet[11] = "";
	//向主控端发送关机信号
	make_send_packet(packet,3,0,0,0);
	slave_socket.Send(packet,10,0);

	//设定从控机工作状态为关机
	room.setState(CLOSED);
	change_state = true;

	//将室温设定回初始室温
	room.setCurTemp(GLOBAL.ini_cur_temp);
	m_cur_temp_text.Format("%.1lf",room.getCurTemp());
	UpdateData(false);
	m_cur_temp_ctrl.ShowWindow(false);
	m_cur_temp_ctrl.ShowWindow(true);
	
	//开机按钮可用，调节风速、目标温度旋转控件及关机不可用
	m_open.EnableWindow(true);
	m_speed_ctrl.EnableWindow(false);
	m_tar_ctrl.EnableWindow(false);
	m_close.EnableWindow(false);

	//关闭全局计数器
	KillTimer(GTimer);
}


void CSACDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	char packet[11] = "";
	switch(nIDEvent)
	{
		case GTimer://全局计数器触发
			//根据从控端状态，做出不同动作
			switch(room.getState())
			{
				case WAITING://从控端处于待机状态。此时由从控端完成室温的计算，并发送给主控端
					//计算从控端当前室温
					if (room.getMode() == WARM) room.setCurTemp(room.getCurTemp() - 0.1);//若之前从控处于制热状态，则待机后室温每秒降低0.1℃
					else if (room.getMode() == COLD) room.setCurTemp(room.getCurTemp() + 0.1);//若之前从控处于制冷状态，则待机后室温每秒上升0.1℃
					
					//若制热时室温低于目标温度1℃或者制冷时室温高于目标温度1℃，则发送温控请求包
					if ( (room.getMode() == WARM && (room.getCurTemp() < room.getTarTemp() - 1)) || 
						 (room.getMode() == COLD && (room.getCurTemp() > room.getTarTemp() + 1)) )
					{
						make_send_packet(packet,1,room.getTarTemp(),room.getCurTemp(),room.getSpeed());
						slave_socket.Send(packet,10,0);
					}
					else if(change_speed || change_tar_temp)//若有风速或者目标温度温控请求，则发送温控请求包
					{
					    make_send_packet(packet,1,room.getTarTemp(),room.getCurTemp(),room.getSpeed());
						slave_socket.Send(packet,10,0);
						if (change_speed) change_speed = false;//复原风速改变标志
						if (change_tar_temp) change_tar_temp = false;//复原目标温度改变标志
					}
					else//否则，发送室温数据包
					{
						make_send_packet(packet,2,room.getTarTemp(),room.getCurTemp(),room.getSpeed());
						slave_socket.Send(packet,10,0);
					}
					break;

				case WORKING://从控端处于工作状态。此时由主控端完成室温计算，从控端负责接收。从控端只发送温控请求，并判断是否达到目标温度。若达到目标温度，则发送待机请求包
					
					//如果房间空调达到目标温度，则从控端待机
					if ((room.getMode() == COLD && room.getCurTemp() < room.getTarTemp()) || 
						(room.getMode() == WARM && room.getCurTemp() > room.getTarTemp()))
					{
						//发送待机请求
						make_send_packet(packet,2,room.getTarTemp(),room.getCurTemp(),room.getSpeed());
						slave_socket.Send(packet,10,0);
						room.setState(WAITING);
						change_state = true;
					}

					//若有风速或者目标温度温控请求，则发送温控请求包
					if(change_speed || change_tar_temp)
					{
					    make_send_packet(packet,1,room.getTarTemp(),room.getCurTemp(),room.getSpeed());
						slave_socket.Send(packet,10,0);
						if (change_speed) change_speed = false;//复原风速改变标志
						if (change_tar_temp) change_tar_temp = false;//复原目标温度改变标志
					}
					break;

				case CLOSED://从控端关机
					//发送表示关机的数据包
					make_send_packet(packet,3,room.getTarTemp(),room.getCurTemp(),room.getSpeed());
					slave_socket.Send(packet,10,0);
					break;
			}

			//若工作状态发生改变，则改变显示值
			if (change_state)
			{
				if (room.getState() == WORKING)
					m_state_text.Format("工作");
				else if (room.getState() == WAITING)
					m_state_text.Format("待机");
				else 
					m_state_text.Format("关机");
			}
			
			//更新显示的当前室温	
			m_cur_temp_text.Format("%.1lf",room.getCurTemp());
			UpdateData(false);
			m_cur_temp_ctrl.ShowWindow(false);
			m_cur_temp_ctrl.ShowWindow(true);		

			//更新工作状态
			if (change_state)
			{
				m_state_ctrl.ShowWindow(false);
				m_state_ctrl.ShowWindow(true);
				change_state = false;
			}

			break;
		default:
			break;
	}
	CDialog::OnTimer(nIDEvent);
}

void CSACDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	char packet[11] = "";	
	//向主机发送关机信号
	make_send_packet(packet,3,0,0,0);
	slave_socket.Send(packet,10,0);
	slave_socket.Close();
	CDialog::OnClose();
}
