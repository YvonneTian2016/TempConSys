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

void decode_packet(char* packet,int *type,double* ini_tar_temp,double* cur_temp)//���
{
	(*type) = packet[0] - '0';
	(*ini_tar_temp) = (packet[1] - '0') * 10 + (packet[2] - '0')  + (packet[4] - '0') / 10.0;
	(*    cur_temp) = (packet[5] - '0') * 10 + (packet[6] - '0')  + (packet[8] - '0') / 10.0;
	return;
}

void make_send_packet(char* temp, int type, double ini_tar_temp, double cur_temp,int speed)//���ɷ������ݰ�
{
	//���ݰ�����
	temp[0] = type + '0';
	//��ʼĿ���¶�
	temp[1] = ((int)(ini_tar_temp + 0.000001) / 10) + '0';
	temp[2] = ((int)(ini_tar_temp + 0.000001) % 10) + '0';
	temp[3] = '.';
	temp[4] = ((int)((ini_tar_temp * 10) + 0.5)) % 10 + '0';
	//��ǰ����
	temp[5] = ((int)(cur_temp + 0.000001) / 10) + '0';
	temp[6] = ((int)(cur_temp + 0.000001) % 10) + '0';
	temp[7] = '.';
	temp[8] = ((int)((cur_temp * 10) + 0.5)) % 10 + '0';
	temp[9] = speed + '0';
	temp[10] = '\0';
	return ;
}

void CSACDlg::initiation(void)//��ʼ������
{
	CString hostip;
	char name[20]="";
	PHOSTENT hostinfo;//����host��Ϣ

    //ʹ��SOCKETǰ�����SOCKET�İ�װ���
    WORD Version;
    WSADATA wsaData;
    Version=MAKEWORD(1,1);
    if (WSAStartup(Version,&wsaData))//�ڵ���winsock����֮ǰ�����Э�鰲װ���
	{
		AfxMessageBox("WINSOCKЭ��δ��װ��");
		return ;
	}
    if (wsaData.wVersion!=Version)//winsock�汾��ƥ��
	{
	    WSACleanup();
	    return ;
	}
	//��ȡ����IP	
	if((hostinfo = gethostbyname(name)) != NULL)
	    hostip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);

	//�趨����ĵ�ǰ���¡�Ŀ���¶ȡ����١�����״̬������ģʽ���ͷ��������á����ش�����IP���˿ڵ���Ϣ
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

	//���١�����״̬��Ŀ���¶ȸı��־��Ϊ��
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

	m_editbrush.CreateSolidBrush(EDIT_BG_COLOR); //�������ñ༭����ɫ��ˢ��
	
	initiation();//��ʼ������

	//��ʼ��������ʾ
	m_ip_text.Format(room.getIP());
	m_state_text.Format("�ػ�");
	m_mode_text.Format("����");
	m_speed_text.Format("����");
	m_cur_temp_text.Format("0.0");
	m_tar_temp_text.Format("25.0");

	//��ʼʱ�������ػ�������Ŀ���¶ȡ����ڷ��ٵȾ�������
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
		//װ�ر���λͼ 
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
		case CTLCOLOR_LISTBOX://���ؼ����ı����б����Ϣ��

			pDC->SetBkColor(EDIT_BG_COLOR);    // change the background
			pDC->SetTextColor(EDIT_TEXT_COLOR); // change the text color
			hbr = (HBRUSH) m_editbrush;    
			break;
		case CTLCOLOR_STATIC://���ؼ�Ϊ��̬�ı���
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
	    MessageBox("���������ض�IP��");
		return;
	}
	if(slave_socket.Connect(m_ip_text, 5005))
	{
	    AfxMessageBox("�������ض˳ɹ���");
		m_connect.EnableWindow(false);

		//��ʱ������ť�����ڷ��ٵȾ�����,����Ŀ���¶ȡ�IP����򡢹ػ���ť������
		m_ip_ctrl.EnableWindow(false);
		m_open.EnableWindow(true);
		m_tar_ctrl.EnableWindow(false);
		m_speed_ctrl.EnableWindow(true);

		//�趨��ʼ����Ϊ����
		room.setSpeed(MEDIUM);
		m_speed_text.Format("����");
		UpdateData(false);
		m_speed_text_ctrl.ShowWindow(false);
		m_speed_text_ctrl.ShowWindow(true);	
	

	}
	else
	{
	    AfxMessageBox("����ʧ�ܡ����������IP�Ƿ���ȷ��");
		slave_socket.Close();
	}
}

void CSACDlg::OnDeltaposSpinTar(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	if (pNMUpDown->iDelta == -1) //����Ŀ���¶�
	{
		if (room.getMode() == WARM)
		{
			if (room.getTarTemp() < WARM_MAX)
				room.setTarTemp(room.getTarTemp() + 0.1);
			else
			{
			    AfxMessageBox("����ģʽ�£����Ŀ���¶Ȳ�����30�档");
				return;
			}
		}
		else if (room.getMode() == COLD)
		{
			if (room.getTarTemp() < COLD_MAX)
				room.setTarTemp(room.getTarTemp() + 0.1);
			else
			{
			    AfxMessageBox("����ģʽ�£����Ŀ���¶Ȳ�����25�档");
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
	else if (pNMUpDown->iDelta == 1) //����Ŀ���¶�
	{
		if (room.getMode() == WARM)
		{
			if (room.getTarTemp() > WARM_MIN)
				room.setTarTemp(room.getTarTemp() - 0.1);
			else
			{
			    AfxMessageBox("����ģʽ�£����Ŀ���¶Ȳ�����25�档");
				return;
			}
		}
		else if (room.getMode() == COLD)
		{
			if (room.getTarTemp() > COLD_MIN)
				room.setTarTemp(room.getTarTemp() - 0.1);
			else
			{
			    AfxMessageBox("����ģʽ�£����Ŀ���¶Ȳ�����18�档");
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

	//����Ŀ���¶ȱ�־������Ŀ���¶��Ѿ��ı�
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
		m_speed_text.Format("����");
	else if (room.getSpeed() == MEDIUM)
		m_speed_text.Format("����");
	else if (room.getSpeed() == FAST)
		m_speed_text.Format("����");
	else 
		m_speed_text.Format("����");
	UpdateData(false);
	m_cur_temp_ctrl.ShowWindow(false);
	m_cur_temp_ctrl.ShowWindow(true);
	m_speed_text_ctrl.ShowWindow(false);
	m_speed_text_ctrl.ShowWindow(true);

	//����Ŀ���¶ȱ�־�����������Ѿ��ı�
	change_tar_temp = true;

	*pResult = 0;
}

void CSACDlg::OnOpen() 
{
	// TODO: Add your control notification handler code here
	char packet[11]="";
	int type;
	double ini_tar_temp,cur_temp;

//�����ض˷��ͱ�ʾ����״̬�����ݰ�
	make_send_packet(packet,0,0,0,0);
    slave_socket.Send(packet,10,0);
//��ȡ���ض˷��͵ĳ�ʼ����Ϣ
	slave_socket.Receive(packet,9,0);
	decode_packet(packet,&type,&ini_tar_temp,&cur_temp);
	if (type == 1)
	{
		room.setTarTemp(ini_tar_temp);
		room.setCurTemp(cur_temp);

		//�趨��ʼ���¡�����Ϊ�ӿض˹ػ�ʱ������ʾ��ʼ��������
		GLOBAL.ini_cur_temp = cur_temp;
	}
	else if (type == 0)
	{
		AfxMessageBox("���ض��ѹػ���");
	}
//���ݳ�ʼ���¶ȱȽϽ�����趨����ģʽ,���蹤��״̬Ϊ����
	if (ini_tar_temp < cur_temp)
		room.setMode(COLD);
	else if (ini_tar_temp > cur_temp)
		room.setMode(WARM);
	else
		room.setMode(STANDBY);
	room.setState(WAITING);

//���½�����ʾ
	m_tar_temp_text.Format("%.1lf",room.getTarTemp());
	m_cur_temp_text.Format("%.1lf",room.getCurTemp());
	//����ģʽ��ʾ
	if (room.getMode() == COLD)
		m_mode_text.Format("����");
	else if (room.getMode() == WARM)
		m_mode_text.Format("����");
	else
		m_mode_text.Format("����");
	//����״̬��ʾ
	m_state_text.Format("����");

	UpdateData(false);

	m_state_ctrl.ShowWindow(false);
	m_state_ctrl.ShowWindow(true);

	m_mode_ctrl.ShowWindow(false);
	m_mode_ctrl.ShowWindow(true);

	m_tar_temp_ctrl.ShowWindow(false);
	m_tar_temp_ctrl.ShowWindow(true);

	m_cur_temp_ctrl.ShowWindow(false);
	m_cur_temp_ctrl.ShowWindow(true);

//����ȫ�ּ���������Ϊ�����ض˵�ͬ��ʱ��
	SetTimer(GTimer,1000,NULL);

//��ʱ�ػ���ť������Ŀ���¶ȡ����ڷ��ٵȾ�����,������ť������
	m_open.EnableWindow(false);
	m_close.EnableWindow(true);
	m_tar_ctrl.EnableWindow(true);
	m_speed_ctrl.EnableWindow(true);
}


void CSACDlg::OnCloseClicked() 
{
	// TODO: Add your control notification handler code here
	char packet[11] = "";
	//�����ض˷��͹ػ��ź�
	make_send_packet(packet,3,0,0,0);
	slave_socket.Send(packet,10,0);

	//�趨�ӿػ�����״̬Ϊ�ػ�
	room.setState(CLOSED);
	change_state = true;

	//�������趨�س�ʼ����
	room.setCurTemp(GLOBAL.ini_cur_temp);
	m_cur_temp_text.Format("%.1lf",room.getCurTemp());
	UpdateData(false);
	m_cur_temp_ctrl.ShowWindow(false);
	m_cur_temp_ctrl.ShowWindow(true);
	
	//������ť���ã����ڷ��١�Ŀ���¶���ת�ؼ����ػ�������
	m_open.EnableWindow(true);
	m_speed_ctrl.EnableWindow(false);
	m_tar_ctrl.EnableWindow(false);
	m_close.EnableWindow(false);

	//�ر�ȫ�ּ�����
	KillTimer(GTimer);
}


void CSACDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	char packet[11] = "";
	switch(nIDEvent)
	{
		case GTimer://ȫ�ּ���������
			//���ݴӿض�״̬��������ͬ����
			switch(room.getState())
			{
				case WAITING://�ӿض˴��ڴ���״̬����ʱ�ɴӿض�������µļ��㣬�����͸����ض�
					//����ӿض˵�ǰ����
					if (room.getMode() == WARM) room.setCurTemp(room.getCurTemp() - 0.1);//��֮ǰ�ӿش�������״̬�������������ÿ�뽵��0.1��
					else if (room.getMode() == COLD) room.setCurTemp(room.getCurTemp() + 0.1);//��֮ǰ�ӿش�������״̬�������������ÿ������0.1��
					
					//������ʱ���µ���Ŀ���¶�1���������ʱ���¸���Ŀ���¶�1�棬�����¿������
					if ( (room.getMode() == WARM && (room.getCurTemp() < room.getTarTemp() - 1)) || 
						 (room.getMode() == COLD && (room.getCurTemp() > room.getTarTemp() + 1)) )
					{
						make_send_packet(packet,1,room.getTarTemp(),room.getCurTemp(),room.getSpeed());
						slave_socket.Send(packet,10,0);
					}
					else if(change_speed || change_tar_temp)//���з��ٻ���Ŀ���¶��¿����������¿������
					{
					    make_send_packet(packet,1,room.getTarTemp(),room.getCurTemp(),room.getSpeed());
						slave_socket.Send(packet,10,0);
						if (change_speed) change_speed = false;//��ԭ���ٸı��־
						if (change_tar_temp) change_tar_temp = false;//��ԭĿ���¶ȸı��־
					}
					else//���򣬷����������ݰ�
					{
						make_send_packet(packet,2,room.getTarTemp(),room.getCurTemp(),room.getSpeed());
						slave_socket.Send(packet,10,0);
					}
					break;

				case WORKING://�ӿض˴��ڹ���״̬����ʱ�����ض�������¼��㣬�ӿض˸�����ա��ӿض�ֻ�����¿����󣬲��ж��Ƿ�ﵽĿ���¶ȡ����ﵽĿ���¶ȣ����ʹ��������
					
					//�������յ��ﵽĿ���¶ȣ���ӿض˴���
					if ((room.getMode() == COLD && room.getCurTemp() < room.getTarTemp()) || 
						(room.getMode() == WARM && room.getCurTemp() > room.getTarTemp()))
					{
						//���ʹ�������
						make_send_packet(packet,2,room.getTarTemp(),room.getCurTemp(),room.getSpeed());
						slave_socket.Send(packet,10,0);
						room.setState(WAITING);
						change_state = true;
					}

					//���з��ٻ���Ŀ���¶��¿����������¿������
					if(change_speed || change_tar_temp)
					{
					    make_send_packet(packet,1,room.getTarTemp(),room.getCurTemp(),room.getSpeed());
						slave_socket.Send(packet,10,0);
						if (change_speed) change_speed = false;//��ԭ���ٸı��־
						if (change_tar_temp) change_tar_temp = false;//��ԭĿ���¶ȸı��־
					}
					break;

				case CLOSED://�ӿض˹ػ�
					//���ͱ�ʾ�ػ������ݰ�
					make_send_packet(packet,3,room.getTarTemp(),room.getCurTemp(),room.getSpeed());
					slave_socket.Send(packet,10,0);
					break;
			}

			//������״̬�����ı䣬��ı���ʾֵ
			if (change_state)
			{
				if (room.getState() == WORKING)
					m_state_text.Format("����");
				else if (room.getState() == WAITING)
					m_state_text.Format("����");
				else 
					m_state_text.Format("�ػ�");
			}
			
			//������ʾ�ĵ�ǰ����	
			m_cur_temp_text.Format("%.1lf",room.getCurTemp());
			UpdateData(false);
			m_cur_temp_ctrl.ShowWindow(false);
			m_cur_temp_ctrl.ShowWindow(true);		

			//���¹���״̬
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
	//���������͹ػ��ź�
	make_send_packet(packet,3,0,0,0);
	slave_socket.Send(packet,10,0);
	slave_socket.Close();
	CDialog::OnClose();
}
