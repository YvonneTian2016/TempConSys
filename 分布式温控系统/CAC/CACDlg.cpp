// CACDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CAC.h"
#include "CACDlg.h"
#include "ModifyFreq.h"
#include "LOGDlg.h"


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
// CCACDlg dialog

CCACDlg::CCACDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCACDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCACDlg)
	m_ini_cur_temp = 0.0f;
	m_ini_tar_temp = 0.0f;
	m_mode_text = _T("");
	m_state_text = _T("");
	m_time_text = _T("");
	m_host_ip_text = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCACDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCACDlg)
	DDX_Control(pDX, IDC_CHECK_LOG, m_check_log);
	DDX_Control(pDX, IDC_EDIT_STATE, m_state_ctrl);
	DDX_Control(pDX, IDC_EDIT_MODE, m_mode_ctrl);
	DDX_Control(pDX, IDC_EDIT_TIME, m_time_ctrl);
	DDX_Control(pDX, IDC_UPDATE_RATE, m_update_rate);
	DDX_Control(pDX, IDC_EDIT_INI_TAR_TEMP, m_ini_tar_temp_ctrl);
	DDX_Control(pDX, IDC_EDIT_INI_CUR_TEMP, m_ini_cur_temp_ctrl);
	DDX_Control(pDX, IDC_RADIO_COLD, m_mode_select);
	DDX_Control(pDX, IDC_ROOM_LIST, m_room_list);
	DDX_Control(pDX, IDC_CLOSE, m_close);
	DDX_Control(pDX, IDC_OPEN, m_open);
	DDX_Text(pDX, IDC_EDIT_INI_CUR_TEMP, m_ini_cur_temp);
	DDV_MinMaxFloat(pDX, m_ini_cur_temp, -40.f, 40.f);
	DDX_Text(pDX, IDC_EDIT_INI_TAR_TEMP, m_ini_tar_temp);
	DDV_MinMaxFloat(pDX, m_ini_tar_temp, -40.f, 40.f);
	DDX_Text(pDX, IDC_EDIT_MODE, m_mode_text);
	DDV_MaxChars(pDX, m_mode_text, 10);
	DDX_Text(pDX, IDC_EDIT_STATE, m_state_text);
	DDV_MaxChars(pDX, m_state_text, 10);
	DDX_Text(pDX, IDC_EDIT_TIME, m_time_text);
	DDV_MaxChars(pDX, m_time_text, 50);
	DDX_Text(pDX, IDC_EDIT_HOST_IP, m_host_ip_text);
	DDV_MaxChars(pDX, m_host_ip_text, 20);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCACDlg, CDialog)
	//{{AFX_MSG_MAP(CCACDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_CLOSE, OnCloseClicked)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_UPDATE_RATE, OnUpdateRate)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHECK_LOG, OnCheckLog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCACDlg message handlers

//自定义函数=================================================================

void decode_packet(char* packet,int *type,double* tar_temp,double* cur_temp,int *speed)//解包
{
	(*        type) = packet[0] - '0';
	(*    tar_temp) = (packet[1] - '0') * 10 + (packet[2] - '0')  + (packet[4] - '0') / 10.0;
	(*    cur_temp) = (packet[5] - '0') * 10 + (packet[6] - '0')  + (packet[8] - '0') / 10.0;
	(*       speed) = packet[9] - '0';
	return;
}

void make_send_packet(char* temp, int type, double ini_tar_temp, double cur_temp)//生成发送数据包
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
	temp[9] = '\0';

	return ;
}

void setTime(void)//设置系统时间
{
	SYSTEMTIME   mSystemTime;
    GetSystemTime(&mSystemTime); 
    GLOBAL.system_time.year = mSystemTime.wYear;
	GLOBAL.system_time.month = mSystemTime.wMonth;
	GLOBAL.system_time.day = mSystemTime.wDay;
	GLOBAL.system_time.hour = mSystemTime.wHour + 8;
	GLOBAL.system_time.min = mSystemTime.wMinute;
	GLOBAL.system_time.sec = mSystemTime.wSecond;
}

void IamClosing(void)//主控端关机时调用此函数,向所有从控端发送关机信号，并断开所有套接字
{
    int i;
	char packet[10] = "";

	for (i = 0; i <= ROOM_AMOUNT - 1; i ++)
	{
	    if (rooms[i].getPort() != 0)
		{
			//发送关机信号
			make_send_packet(packet,0,0,0);
		    slave_list[i]->Send(packet,9,0);
			//断开所有套接字
			slave_list[i]->Close();
			delete slave_list[i];
			//释放连接（显示）
			rooms[i].setIP("255.255.255.255");
			rooms[i].setPort(0);
		}
	}
	central_socket.Close();
}

int theOneToWait(void)//调度函数，当超过3个从控端有温控请求时，实现负载均衡。采用轮回算法
{
	int i,count = 0;
	char packet[10] = "";
	for (i = 0; i <= ROOM_AMOUNT - 1 ; i ++)
	{
	   if (rooms[i].getState() == WORKING)
		   count ++;
	}
	if (count == 3)
	{
	    GLOBAL.room_to_wait = (GLOBAL.room_to_wait + 1) % 4;
	    //发送强制待机包
		make_send_packet(packet,3,0,0);
		slave_list[GLOBAL.room_to_wait]->Send(packet,9,0);
	}
    return GLOBAL.room_to_wait;
}

void CCACDlg::acceptConnection(void)//接受来自从控端的连接请求
{
	CString addr;
	UINT port;
	int i;
	char packet[9]="";
	CSlaveSocket *tempSocket = new CSlaveSocket();//临时的接收套接字
	central_socket.Accept(*tempSocket);//暂时接受新连接
	tempSocket->GetPeerName(addr, port);

	//检查该连接是否被分配房间
	for (i = 0; i <= ROOM_AMOUNT - 1; i ++)
	{
	    if (rooms[i].getIP() == addr)
			break;
	}
	if ( i <= ROOM_AMOUNT - 1)
	{
	    AfxMessageBox("一个已经连接的从控端试图再次连接。该链接被拒绝。");
		make_send_packet(packet,0,0,0);//发送主控关机信号（表示拒绝该链接）
		tempSocket->Send(packet,9,0);
		tempSocket->Close();//关闭临时新连接
		delete tempSocket;//删除临时新连接
		return;
	}
	//查找一个可用的房间，或者该连接已被分配房间
	for (i = 0; i <= ROOM_AMOUNT - 1; i ++)
	{
	    if (rooms[i].getIP() == "255.255.255.255")
			break;
	}
	if (i <= ROOM_AMOUNT - 1)
	{
		//接受该连接
		slave_list[i] = tempSocket;
		slave_list[i]->dlgp = this;						//设置套接字对应的对话框
		rooms[i].setIP(addr);
		rooms[i].setPort(port);
		AfxMessageBox("接受一个从控端的连接请求。");
	}
	else//坑位已满，不再接受新连接
	{	
		make_send_packet(packet,0,0,0);//发送主控关机信号（表示拒绝该链接）
		tempSocket->Send(packet,9,0);
		tempSocket->Close();//关闭临时新连接
		delete tempSocket;//删除临时新连接
		AfxMessageBox("一个从控端尝试连接，但已达到最大连接数(4)，不再接受该连接");
		return;
	}
}

void CCACDlg::receivePacket(CSocket &slave_socket)//从从控端接收数据包
{
	char packet[11]="";
	int type,speed,i;
	double tar_temp,cur_temp;
	CString addr;//收到包的套接字的IP地址
	UINT port;//收到包的套接字的端口
    slave_socket.Receive(packet,10,0);
	slave_socket.GetPeerName(addr,port);
	decode_packet(packet,&type,&tar_temp,&cur_temp,&speed);

	//找到该连接对应的房间
	for (i = 0; i <= ROOM_AMOUNT - 1; i++)
	{
		if (rooms[i].getIP() == addr)
		{
			break;
		}
	}
	switch(type)
	{
		case 0://从控端发来请求初始化的数据包

			//向从控端发送初始化数据包，包括初始目标温度和初始室温
			make_send_packet(packet,1,central.ini_tar_temp,central.ini_cur_temp);
			slave_socket.Send(packet,9,0);

			//设定主控端这边的该房间的温控情况列表信息显示
			
			if (i <= ROOM_AMOUNT - 1)//修改房间信息
			{
				rooms[i].setTarTemp(central.ini_tar_temp);
				rooms[i].setCurTemp(central.ini_cur_temp);
				rooms[i].setSpeed(MEDIUM);
				rooms[i].setState(WAITING);//待从控发出温控请求再使其工作，先令其待机
			}
			break;

		case 1://从控端发来温控请求数据包
			if (((tar_temp < cur_temp && central.getMode() == COLD) || 
				(tar_temp > cur_temp && central.getMode() == WARM)) && i != theOneToWait())
			{
				//允许温控请求
				make_send_packet(packet,2,central.ini_tar_temp,central.ini_cur_temp);
				slave_socket.Send(packet,9,0);
				rooms[i].setTarTemp(tar_temp);
				rooms[i].setSpeed(speed);
				rooms[i].setState(WORKING);
			}
			else
			{
			    //拒绝温控请求，强制从控端待机

				rooms[i].setTarTemp(tar_temp);
				rooms[i].setSpeed(speed);
				rooms[i].setState(WAITING);
			}

			break;

		case 2://收到从控端发来的达到目标温度信号（含达到目标温度后发出的温控请求）

			for (i = 0; i <= ROOM_AMOUNT - 1; i++)//找到对应的房间
			{
			    if (rooms[i].getIP() == addr)
				{
				    break;
				}
			}
			if (i <= ROOM_AMOUNT - 1)
			{
				//修改房间信息
				rooms[i].setTarTemp(tar_temp);
				rooms[i].setCurTemp(cur_temp);
				rooms[i].setState(WAITING);
			}
			break;

		case 3://收到从控端发来的关机信号
			for (i = 0; i <= ROOM_AMOUNT - 1; i++)//找到对应的房间
			{
			    if (rooms[i].getIP() == addr)
				{
				    break;
				}
			}
			if (i <= ROOM_AMOUNT - 1)//修改房间信息
			{
				rooms[i].setTarTemp(central.ini_tar_temp);
				rooms[i].setCurTemp(central.ini_cur_temp);
				rooms[i].setState(CLOSED);
				rooms[i].setCount(rooms[i].getCount() + 1);
			}
			break;
	}

}

void CCACDlg::sendPacket(CSocket &slave_socket,int i)//向从控端发送数据包
{
    CString addr;
	UINT port;
	char packet[10] = "";
	slave_socket.GetPeerName(addr,port);

	if (i <= ROOM_AMOUNT - 1)
	{
	    switch(rooms[i].getState())//根据房间空调工作状态不同，发送不同的数据包
		{
			case WORKING://房间空调处于工作状态
				//发送当前室温
				make_send_packet(packet,2,rooms[i].getTarTemp(),rooms[i].getCurTemp());
				slave_socket.Send(packet,9,0);
				break;
		}
	}
}

void CCACDlg::initiation(void)//初始化数据
{
	int i;
	CString temp;

    for (i = 0 ; i <= ROOM_AMOUNT - 1; i ++)
    {
	     //初始化每个房间的房间号、工作状态、当前室温、目标温度、风速、送风量、费用、开关次数等
		 rooms[i].setRoomNo(101 + i);
		 rooms[i].setState(CLOSED);
		 rooms[i].setCurTemp(00.0);
		 rooms[i].setTarTemp(00.0);
		 rooms[i].setSpeed(NONE);
		 rooms[i].setAmount(0.0);
		 rooms[i].setCost(0);
		 rooms[i].setCount(0);
         temp.Format("255.255.255.255");
		 rooms[i].setIP(temp);
		 rooms[i].setPort(0);

		 //从控套接字列表初始化
		 slave_list[i] = NULL;

		 //负载均衡调度标志初始化(假想第四个从控机的要求被拒绝)
		 GLOBAL.room_to_wait = 3;
	}

}

void CCACDlg::setListInfo(void)//设置房间温控情况列表显示的信息
{
	int i;
	CString temp;
    for (i = 0; i <= ROOM_AMOUNT - 1; i ++)
	{
		//设定每个房间的工作状态
		switch(rooms[i].getState())
		{
			case WORKING:
				temp.Format("工作");
				break;
			case WAITING:
				temp.Format("待机");
				break;
			default:
				temp.Format("关机");
				break;
		}
		m_room_list.SetItemText(i,1,temp);

		//设定每个房间的当前室温
		temp.Format("%.1lf℃",rooms[i].getCurTemp());
		m_room_list.SetItemText(i,2,temp);

		//设定每个房间的目标温度
		temp.Format("%.1lf℃",rooms[i].getTarTemp());
		m_room_list.SetItemText(i,3,temp);

		//设定每个房间的风速
		switch(rooms[i].getSpeed())
		{
			case SLOW:
				temp.Format("慢速");
				break;
			case MEDIUM:
				temp.Format("中速");
				break;
			case FAST:
				temp.Format("快速");
				break;
			default:
				temp.Format("无风");
				break;
		}
		m_room_list.SetItemText(i,4,temp);

		//设定每个房间的送风量
		temp.Format("%.1lf",rooms[i].getAmount());
		m_room_list.SetItemText(i,5,temp);

		//设定每个房间的费用
		temp.Format("%d",rooms[i].getCost());
		m_room_list.SetItemText(i,6,temp);

		//设定每个房间对应的从控端的IP地址
		m_room_list.SetItemText(i,7,rooms[i].getIP());

		//设定每个房间对应的从控端的端口
		temp.Format("%d",rooms[i].getPort());
		m_room_list.SetItemText(i,8,temp);
	}
}

void calculate(void)//计算房间各项数据
{
    int i;
	char packet[10] = "";
	for (i = 0; i <= ROOM_AMOUNT - 1; i ++)
	{
	    if (rooms[i].getState() != CLOSED)//若房间空调没关机，则房间温控数据会发生变化
		{
		    switch(rooms[i].getState())
			{
				case WORKING://房间空调处于工作状态

					switch(rooms[i].getSpeed())//根据风速不同，数据变化不同
					{
						case SLOW://慢速
							//更新室温
							if (central.getMode() == COLD)
							    rooms[i].setCurTemp(rooms[i].getCurTemp() - LOW);
							else if (central.getMode() == WARM)
							    rooms[i].setCurTemp(rooms[i].getCurTemp() + LOW);
							//更新送风量
							rooms[i].setAmount(rooms[i].getAmount() + 0.8);
							break;

						case MEDIUM://中速
							//更新室温
							if (central.getMode() == COLD)
							    rooms[i].setCurTemp(rooms[i].getCurTemp() - MED);
							else if (central.getMode() == WARM)
							    rooms[i].setCurTemp(rooms[i].getCurTemp() + MED);
							//更新送风量
							rooms[i].setAmount(rooms[i].getAmount() + 1);
							break;

						case FAST://快速
							//更新室温
							if (central.getMode() == COLD)
							    rooms[i].setCurTemp(rooms[i].getCurTemp() - HIGH);
							else if (central.getMode() == WARM)
							    rooms[i].setCurTemp(rooms[i].getCurTemp() + HIGH);
							//更新送风量
							rooms[i].setAmount(rooms[i].getAmount() + 1.3);
							break;

						default:
							AfxMessageBox("No wind.");
							break;
					}
					//更新费用
					rooms[i].setCost((int)(rooms[i].getAmount() * 10));
					
					break;
			}
		}
	}
}

//===========================================================================

BOOL CCACDlg::OnInitDialog()
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

	//初始化数据
	initiation();

	HICON m_hIcon_open = AfxGetApp()->LoadIcon(IDI_ICON_OPEN);//加载开机按钮的图标
    HICON m_hIcon_close = AfxGetApp()->LoadIcon(IDI_ICON_CLOSE);//加载关机按钮的图标
	HICON m_hIcon_update_rate = AfxGetApp()->LoadIcon(IDI_ICON_UPDATE_RATE);//加载设定房间状况列表的刷新频率按钮的图标

    m_editbrush.CreateSolidBrush(EDIT_BG_COLOR); //创建设置编辑框颜色的刷子

	m_open.SetIcon(m_hIcon_open,m_hIcon_open);//设置开机按钮的图标
	m_close.SetIcon(m_hIcon_close,m_hIcon_close);//设置关机按钮的图标
	m_update_rate.SetIcon(m_hIcon_update_rate,m_hIcon_update_rate);//设置关机按钮的图标

	m_close.EnableWindow (FALSE);//关机按钮初始时不可用

	m_mode_select.SetCheck(TRUE);//模式选择默认为制冷

//设置中央空调信息显示
	switch(central.getMode())
	{
		case COLD:
			m_mode_text.Format("制冷");
			break;
		case WARM:
			m_mode_text.Format("制热");
			break;
		default:
			m_mode_text.Format("待定");
	}
	m_state_text.Format("关闭");
	UpdateData(false);
	m_mode_ctrl.EnableWindow(false);
	m_state_ctrl.EnableWindow(false);
	m_time_ctrl.EnableWindow(false);
	


//设置房间空调状况列表的样式和表头信息
	m_room_list.ModifyStyle (LVS_EDITLABELS, 0);
	m_room_list.SetExtendedStyle (LVS_EX_HEADERDRAGDROP | LVS_EX_GRIDLINES);
	m_room_list.InsertColumn (0, "房间号", LVCFMT_LEFT, 60, 0);
	m_room_list.InsertColumn (1, "工作状态", LVCFMT_LEFT, 80, 1);
	m_room_list.InsertColumn (2, "当前室温", LVCFMT_LEFT, 80, 2);
	m_room_list.InsertColumn (3, "目标温度", LVCFMT_LEFT, 80, 3);
	m_room_list.InsertColumn (4, "风速", LVCFMT_LEFT, 45, 4);
	m_room_list.InsertColumn (5, "风量", LVCFMT_LEFT, 45, 5);
	m_room_list.InsertColumn (6, "费用", LVCFMT_LEFT, 45, 6);
	m_room_list.InsertColumn (7, "IP地址", LVCFMT_LEFT, 135, 7);
	m_room_list.InsertColumn (8, "端口", LVCFMT_LEFT, 60, 8);

	//向列表控件中添加4个房间号
	m_room_list.InsertItem(0, "101");
	m_room_list.InsertItem(1, "102");
	m_room_list.InsertItem(2, "103");
	m_room_list.InsertItem(3, "104");

	//设定默认刷新频率（默认1秒一次）
	GLOBAL.refresh_freq = 1000;
	GLOBAL.change_freq = false;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCACDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCACDlg::OnPaint() 
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
HCURSOR CCACDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

HBRUSH CCACDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

void CCACDlg::OnOpen() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	//更新中央空调参数设置
    central.setState(WAITING);
	m_state_text.Format("待机");
	m_state_ctrl.ShowWindow(false);
	m_state_ctrl.ShowWindow(true);
	central.setMode((m_mode_select.GetCheck()) ? COLD : WARM);
	central.ini_cur_temp = m_ini_cur_temp;
	central.ini_tar_temp = m_ini_tar_temp;
	
	//判断输入的各项参数是否合法,若合法，则中央空调顺利开启，否则重新输入参数
	switch(central.getMode())
	{
		case COLD:
			if (central.ini_cur_temp <= COLD_MAX)
			{
				AfxMessageBox("初始室温 输入错误：制冷模式下，请输入 大于25.0 的浮点数。");
			    return;
			}
			if (central.ini_tar_temp < COLD_MIN || central.ini_tar_temp > COLD_MAX)
			{
				AfxMessageBox("初始目标温度 输入错误：制冷模式下，请输入 18.0 至 25.0 的浮点数。");
			    return;
			}
			m_mode_text.Format("制冷");
			UpdateData(false);
			m_mode_ctrl.ShowWindow(false);
			m_mode_ctrl.ShowWindow(true);
			break;
		case WARM:
			if (central.ini_cur_temp >= WARM_MIN)
			{
				AfxMessageBox("初始室温 输入错误：制热模式下，请输入 小于25.0 的浮点数。");
			    return;
			}
			if (central.ini_tar_temp < WARM_MIN || central.ini_tar_temp > WARM_MAX)
			{
				AfxMessageBox("初始目标温度 输入错误：制热模式下，请输入 25.0 至 30.0 的浮点数。");
			    return;
			}
			m_mode_text.Format("制热");
			UpdateData(false);
			m_mode_ctrl.ShowWindow(false);
			m_mode_ctrl.ShowWindow(true);
			break;
		default:
			break;
	}

	//开机后，开机按钮、模式选择、初始室温和初始目标温度的设置均不可用，开机按钮变为可用，系统时间及房间情况显示列表变为可用    
	m_open.EnableWindow(FALSE);
	m_mode_select.EnableWindow(FALSE);
	((CButton *)GetDlgItem(IDC_RADIO_WARM))->EnableWindow(FALSE);
	m_ini_cur_temp_ctrl.EnableWindow(FALSE);
	m_ini_tar_temp_ctrl.EnableWindow(FALSE);
	m_close.EnableWindow(TRUE);
	m_time_ctrl.ShowWindow(TRUE);
	m_room_list.EnableWindow(TRUE);

	//开机后，初始时没有从控端的温控请求，因此中央空调待机
	central.setState(WAITING);

	//为即时显示设置计数器，及获取系统时间
	setTime();
    SetTimer(1,1000,NULL); 

	//为房间温控情况列表的刷新设置计数器
	SetTimer(2,GLOBAL.refresh_freq,NULL);

	//设置房间温控列表里面所有房间的初始室温、初始目标温度
	int i;
	for (i = 0; i <= ROOM_AMOUNT - 1; i++)
	{
		rooms[i].setCurTemp(central.ini_cur_temp);
		rooms[i].setTarTemp(central.ini_tar_temp);
	}
	setListInfo();

//网络通信相关============================================================

	//使用SOCKET前，检查SOCKET的安装情况
    WORD Version;
    WSADATA wsaData;
    Version=MAKEWORD(1,1);
	PHOSTENT hostinfo;//本机host信息
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

	//设置主控端套接字，现在开始可以接受从控端连接请求
	central_socket.dlgp = this;	

	//获取本机IP
	CString hostip;
	char name[20]="";
	if((hostinfo = gethostbyname(name)) != NULL)
	    hostip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
	m_host_ip_text = hostip;

	central_socket.Create(5005,SOCK_STREAM,hostip);	//创建套接字
	BOOL ret = central_socket.Listen();				//将套接字置于监听模式
	
	if (ret)
	{
	    AfxMessageBox("服务器开启成功。");
	}
	else
	{
	    AfxMessageBox("服务器开启失败。");
	}
}

void CCACDlg::OnCloseClicked() 
{
	// TODO: Add your control notification handler code here
	
	//关机后，关机按钮不可用，系统时间及房间情况显示列表不可用；开机按钮、模式选择、初始室温和初始目标温度的设置均变为可用    
	m_open.EnableWindow(TRUE);
	m_mode_select.EnableWindow(TRUE);
	((CButton *)GetDlgItem(IDC_RADIO_WARM))->EnableWindow(TRUE);
	m_ini_cur_temp_ctrl.EnableWindow(TRUE);
	m_ini_tar_temp_ctrl.EnableWindow(TRUE);
	m_close.EnableWindow(FALSE);
	m_time_ctrl.ShowWindow(FALSE);
	m_room_list.EnableWindow(FALSE);

	//关机后，中央空调关闭
	central.setState(CLOSED);
	central.setMode(STANDBY);
	m_state_text.Format("关闭");
	m_mode_text.Format("待定");
	UpdateData(false);
	m_state_ctrl.ShowWindow(false);
	m_mode_ctrl.ShowWindow(false);
	m_state_ctrl.ShowWindow(true);
	m_mode_ctrl.ShowWindow(true);

	//关闭系统时间计数器，待下次开机时再启动	
	KillTimer(1);

	//关闭列表刷新计数器，待下次开机时再启动	
	KillTimer(2);

	//向所有房间发送主控关机信号
	IamClosing();

	//初始化系统信息
	initiation();

	//更改房间温控情况列表显示的信息
	setListInfo();

}

void CCACDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	int i;
	switch(nIDEvent)
	{
		case 1:
			//更新系统时间显示
			setTime();
			m_time_text.Format( "%4d年%2d月%2d日%2d点%2d分%2d秒", 
				GLOBAL.system_time.year,
				GLOBAL.system_time.month,
				GLOBAL.system_time.day,
				GLOBAL.system_time.hour,
				GLOBAL.system_time.min,
				GLOBAL.system_time.sec
			);
			UpdateData(false); 	
			m_time_ctrl.ShowWindow(false);
			m_time_ctrl.ShowWindow(true);

			//计算房间室温、送风量、费用等信息
			calculate();

			//向各房间发送数据包
			for (i = 0 ; i <= ROOM_AMOUNT - 1; i ++)
			{
			    if (rooms[i].getPort() != 0)
				{
					sendPacket((*slave_list[i]),i);
				}

			}

			//设定中央空调的工作状态。若没有房间有温控请求，则待机；否则工作
			central.setState(WORKING);
			for (i = 0 ; i <= ROOM_AMOUNT - 1 ; i ++)
			{
			    if (rooms[i].getState() == WORKING)
				{
					m_state_text.Format("工作");
					break;
				}
			}
			if ( i == ROOM_AMOUNT)
			{
				central.setState(WAITING);
				m_state_text.Format("待机");
			}
			UpdateData(false);
			m_state_ctrl.ShowWindow(false);
			m_state_ctrl.ShowWindow(true);
				
			break;
		case 2:
			setListInfo();
			if (GLOBAL.change_freq)
			{
			    KillTimer(2);
				SetTimer(2,GLOBAL.refresh_freq,NULL);
				GLOBAL.change_freq = false;
			}
			break;
		default:
			break;
	}

	CDialog::OnTimer(nIDEvent);
}

void CCACDlg::OnUpdateRate() 
{
	// TODO: Add your control notification handler code here
	CModifyFreq dlg;
	dlg.DoModal();
	
}

void CCACDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	//向所有房间发送主控关机信号
	IamClosing();
	CDialog::OnClose();
}

void CCACDlg::OnCheckLog() 
{
	// TODO: Add your control notification handler code here
	CLOGDlg dlg;
	dlg.DoModal();
}
