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

//�Զ��庯��=================================================================

void decode_packet(char* packet,int *type,double* tar_temp,double* cur_temp,int *speed)//���
{
	(*        type) = packet[0] - '0';
	(*    tar_temp) = (packet[1] - '0') * 10 + (packet[2] - '0')  + (packet[4] - '0') / 10.0;
	(*    cur_temp) = (packet[5] - '0') * 10 + (packet[6] - '0')  + (packet[8] - '0') / 10.0;
	(*       speed) = packet[9] - '0';
	return;
}

void make_send_packet(char* temp, int type, double ini_tar_temp, double cur_temp)//���ɷ������ݰ�
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
	temp[9] = '\0';

	return ;
}

void setTime(void)//����ϵͳʱ��
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

void IamClosing(void)//���ض˹ػ�ʱ���ô˺���,�����дӿض˷��͹ػ��źţ����Ͽ������׽���
{
    int i;
	char packet[10] = "";

	for (i = 0; i <= ROOM_AMOUNT - 1; i ++)
	{
	    if (rooms[i].getPort() != 0)
		{
			//���͹ػ��ź�
			make_send_packet(packet,0,0,0);
		    slave_list[i]->Send(packet,9,0);
			//�Ͽ������׽���
			slave_list[i]->Close();
			delete slave_list[i];
			//�ͷ����ӣ���ʾ��
			rooms[i].setIP("255.255.255.255");
			rooms[i].setPort(0);
		}
	}
	central_socket.Close();
}

int theOneToWait(void)//���Ⱥ�����������3���ӿض����¿�����ʱ��ʵ�ָ��ؾ��⡣�����ֻ��㷨
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
	    //����ǿ�ƴ�����
		make_send_packet(packet,3,0,0);
		slave_list[GLOBAL.room_to_wait]->Send(packet,9,0);
	}
    return GLOBAL.room_to_wait;
}

void CCACDlg::acceptConnection(void)//�������Դӿض˵���������
{
	CString addr;
	UINT port;
	int i;
	char packet[9]="";
	CSlaveSocket *tempSocket = new CSlaveSocket();//��ʱ�Ľ����׽���
	central_socket.Accept(*tempSocket);//��ʱ����������
	tempSocket->GetPeerName(addr, port);

	//���������Ƿ񱻷��䷿��
	for (i = 0; i <= ROOM_AMOUNT - 1; i ++)
	{
	    if (rooms[i].getIP() == addr)
			break;
	}
	if ( i <= ROOM_AMOUNT - 1)
	{
	    AfxMessageBox("һ���Ѿ����ӵĴӿض���ͼ�ٴ����ӡ������ӱ��ܾ���");
		make_send_packet(packet,0,0,0);//�������عػ��źţ���ʾ�ܾ������ӣ�
		tempSocket->Send(packet,9,0);
		tempSocket->Close();//�ر���ʱ������
		delete tempSocket;//ɾ����ʱ������
		return;
	}
	//����һ�����õķ��䣬���߸������ѱ����䷿��
	for (i = 0; i <= ROOM_AMOUNT - 1; i ++)
	{
	    if (rooms[i].getIP() == "255.255.255.255")
			break;
	}
	if (i <= ROOM_AMOUNT - 1)
	{
		//���ܸ�����
		slave_list[i] = tempSocket;
		slave_list[i]->dlgp = this;						//�����׽��ֶ�Ӧ�ĶԻ���
		rooms[i].setIP(addr);
		rooms[i].setPort(port);
		AfxMessageBox("����һ���ӿض˵���������");
	}
	else//��λ���������ٽ���������
	{	
		make_send_packet(packet,0,0,0);//�������عػ��źţ���ʾ�ܾ������ӣ�
		tempSocket->Send(packet,9,0);
		tempSocket->Close();//�ر���ʱ������
		delete tempSocket;//ɾ����ʱ������
		AfxMessageBox("һ���ӿض˳������ӣ����Ѵﵽ���������(4)�����ٽ��ܸ�����");
		return;
	}
}

void CCACDlg::receivePacket(CSocket &slave_socket)//�Ӵӿض˽������ݰ�
{
	char packet[11]="";
	int type,speed,i;
	double tar_temp,cur_temp;
	CString addr;//�յ������׽��ֵ�IP��ַ
	UINT port;//�յ������׽��ֵĶ˿�
    slave_socket.Receive(packet,10,0);
	slave_socket.GetPeerName(addr,port);
	decode_packet(packet,&type,&tar_temp,&cur_temp,&speed);

	//�ҵ������Ӷ�Ӧ�ķ���
	for (i = 0; i <= ROOM_AMOUNT - 1; i++)
	{
		if (rooms[i].getIP() == addr)
		{
			break;
		}
	}
	switch(type)
	{
		case 0://�ӿض˷��������ʼ�������ݰ�

			//��ӿض˷��ͳ�ʼ�����ݰ���������ʼĿ���¶Ⱥͳ�ʼ����
			make_send_packet(packet,1,central.ini_tar_temp,central.ini_cur_temp);
			slave_socket.Send(packet,9,0);

			//�趨���ض���ߵĸ÷�����¿�����б���Ϣ��ʾ
			
			if (i <= ROOM_AMOUNT - 1)//�޸ķ�����Ϣ
			{
				rooms[i].setTarTemp(central.ini_tar_temp);
				rooms[i].setCurTemp(central.ini_cur_temp);
				rooms[i].setSpeed(MEDIUM);
				rooms[i].setState(WAITING);//���ӿط����¿�������ʹ�乤�������������
			}
			break;

		case 1://�ӿض˷����¿��������ݰ�
			if (((tar_temp < cur_temp && central.getMode() == COLD) || 
				(tar_temp > cur_temp && central.getMode() == WARM)) && i != theOneToWait())
			{
				//�����¿�����
				make_send_packet(packet,2,central.ini_tar_temp,central.ini_cur_temp);
				slave_socket.Send(packet,9,0);
				rooms[i].setTarTemp(tar_temp);
				rooms[i].setSpeed(speed);
				rooms[i].setState(WORKING);
			}
			else
			{
			    //�ܾ��¿�����ǿ�ƴӿض˴���

				rooms[i].setTarTemp(tar_temp);
				rooms[i].setSpeed(speed);
				rooms[i].setState(WAITING);
			}

			break;

		case 2://�յ��ӿض˷����ĴﵽĿ���¶��źţ����ﵽĿ���¶Ⱥ󷢳����¿�����

			for (i = 0; i <= ROOM_AMOUNT - 1; i++)//�ҵ���Ӧ�ķ���
			{
			    if (rooms[i].getIP() == addr)
				{
				    break;
				}
			}
			if (i <= ROOM_AMOUNT - 1)
			{
				//�޸ķ�����Ϣ
				rooms[i].setTarTemp(tar_temp);
				rooms[i].setCurTemp(cur_temp);
				rooms[i].setState(WAITING);
			}
			break;

		case 3://�յ��ӿض˷����Ĺػ��ź�
			for (i = 0; i <= ROOM_AMOUNT - 1; i++)//�ҵ���Ӧ�ķ���
			{
			    if (rooms[i].getIP() == addr)
				{
				    break;
				}
			}
			if (i <= ROOM_AMOUNT - 1)//�޸ķ�����Ϣ
			{
				rooms[i].setTarTemp(central.ini_tar_temp);
				rooms[i].setCurTemp(central.ini_cur_temp);
				rooms[i].setState(CLOSED);
				rooms[i].setCount(rooms[i].getCount() + 1);
			}
			break;
	}

}

void CCACDlg::sendPacket(CSocket &slave_socket,int i)//��ӿض˷������ݰ�
{
    CString addr;
	UINT port;
	char packet[10] = "";
	slave_socket.GetPeerName(addr,port);

	if (i <= ROOM_AMOUNT - 1)
	{
	    switch(rooms[i].getState())//���ݷ���յ�����״̬��ͬ�����Ͳ�ͬ�����ݰ�
		{
			case WORKING://����յ����ڹ���״̬
				//���͵�ǰ����
				make_send_packet(packet,2,rooms[i].getTarTemp(),rooms[i].getCurTemp());
				slave_socket.Send(packet,9,0);
				break;
		}
	}
}

void CCACDlg::initiation(void)//��ʼ������
{
	int i;
	CString temp;

    for (i = 0 ; i <= ROOM_AMOUNT - 1; i ++)
    {
	     //��ʼ��ÿ������ķ���š�����״̬����ǰ���¡�Ŀ���¶ȡ����١��ͷ��������á����ش�����
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

		 //�ӿ��׽����б��ʼ��
		 slave_list[i] = NULL;

		 //���ؾ�����ȱ�־��ʼ��(������ĸ��ӿػ���Ҫ�󱻾ܾ�)
		 GLOBAL.room_to_wait = 3;
	}

}

void CCACDlg::setListInfo(void)//���÷����¿�����б���ʾ����Ϣ
{
	int i;
	CString temp;
    for (i = 0; i <= ROOM_AMOUNT - 1; i ++)
	{
		//�趨ÿ������Ĺ���״̬
		switch(rooms[i].getState())
		{
			case WORKING:
				temp.Format("����");
				break;
			case WAITING:
				temp.Format("����");
				break;
			default:
				temp.Format("�ػ�");
				break;
		}
		m_room_list.SetItemText(i,1,temp);

		//�趨ÿ������ĵ�ǰ����
		temp.Format("%.1lf��",rooms[i].getCurTemp());
		m_room_list.SetItemText(i,2,temp);

		//�趨ÿ�������Ŀ���¶�
		temp.Format("%.1lf��",rooms[i].getTarTemp());
		m_room_list.SetItemText(i,3,temp);

		//�趨ÿ������ķ���
		switch(rooms[i].getSpeed())
		{
			case SLOW:
				temp.Format("����");
				break;
			case MEDIUM:
				temp.Format("����");
				break;
			case FAST:
				temp.Format("����");
				break;
			default:
				temp.Format("�޷�");
				break;
		}
		m_room_list.SetItemText(i,4,temp);

		//�趨ÿ��������ͷ���
		temp.Format("%.1lf",rooms[i].getAmount());
		m_room_list.SetItemText(i,5,temp);

		//�趨ÿ������ķ���
		temp.Format("%d",rooms[i].getCost());
		m_room_list.SetItemText(i,6,temp);

		//�趨ÿ�������Ӧ�Ĵӿض˵�IP��ַ
		m_room_list.SetItemText(i,7,rooms[i].getIP());

		//�趨ÿ�������Ӧ�Ĵӿض˵Ķ˿�
		temp.Format("%d",rooms[i].getPort());
		m_room_list.SetItemText(i,8,temp);
	}
}

void calculate(void)//���㷿���������
{
    int i;
	char packet[10] = "";
	for (i = 0; i <= ROOM_AMOUNT - 1; i ++)
	{
	    if (rooms[i].getState() != CLOSED)//������յ�û�ػ����򷿼��¿����ݻᷢ���仯
		{
		    switch(rooms[i].getState())
			{
				case WORKING://����յ����ڹ���״̬

					switch(rooms[i].getSpeed())//���ݷ��ٲ�ͬ�����ݱ仯��ͬ
					{
						case SLOW://����
							//��������
							if (central.getMode() == COLD)
							    rooms[i].setCurTemp(rooms[i].getCurTemp() - LOW);
							else if (central.getMode() == WARM)
							    rooms[i].setCurTemp(rooms[i].getCurTemp() + LOW);
							//�����ͷ���
							rooms[i].setAmount(rooms[i].getAmount() + 0.8);
							break;

						case MEDIUM://����
							//��������
							if (central.getMode() == COLD)
							    rooms[i].setCurTemp(rooms[i].getCurTemp() - MED);
							else if (central.getMode() == WARM)
							    rooms[i].setCurTemp(rooms[i].getCurTemp() + MED);
							//�����ͷ���
							rooms[i].setAmount(rooms[i].getAmount() + 1);
							break;

						case FAST://����
							//��������
							if (central.getMode() == COLD)
							    rooms[i].setCurTemp(rooms[i].getCurTemp() - HIGH);
							else if (central.getMode() == WARM)
							    rooms[i].setCurTemp(rooms[i].getCurTemp() + HIGH);
							//�����ͷ���
							rooms[i].setAmount(rooms[i].getAmount() + 1.3);
							break;

						default:
							AfxMessageBox("No wind.");
							break;
					}
					//���·���
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

	//��ʼ������
	initiation();

	HICON m_hIcon_open = AfxGetApp()->LoadIcon(IDI_ICON_OPEN);//���ؿ�����ť��ͼ��
    HICON m_hIcon_close = AfxGetApp()->LoadIcon(IDI_ICON_CLOSE);//���عػ���ť��ͼ��
	HICON m_hIcon_update_rate = AfxGetApp()->LoadIcon(IDI_ICON_UPDATE_RATE);//�����趨����״���б��ˢ��Ƶ�ʰ�ť��ͼ��

    m_editbrush.CreateSolidBrush(EDIT_BG_COLOR); //�������ñ༭����ɫ��ˢ��

	m_open.SetIcon(m_hIcon_open,m_hIcon_open);//���ÿ�����ť��ͼ��
	m_close.SetIcon(m_hIcon_close,m_hIcon_close);//���ùػ���ť��ͼ��
	m_update_rate.SetIcon(m_hIcon_update_rate,m_hIcon_update_rate);//���ùػ���ť��ͼ��

	m_close.EnableWindow (FALSE);//�ػ���ť��ʼʱ������

	m_mode_select.SetCheck(TRUE);//ģʽѡ��Ĭ��Ϊ����

//��������յ���Ϣ��ʾ
	switch(central.getMode())
	{
		case COLD:
			m_mode_text.Format("����");
			break;
		case WARM:
			m_mode_text.Format("����");
			break;
		default:
			m_mode_text.Format("����");
	}
	m_state_text.Format("�ر�");
	UpdateData(false);
	m_mode_ctrl.EnableWindow(false);
	m_state_ctrl.EnableWindow(false);
	m_time_ctrl.EnableWindow(false);
	


//���÷���յ�״���б����ʽ�ͱ�ͷ��Ϣ
	m_room_list.ModifyStyle (LVS_EDITLABELS, 0);
	m_room_list.SetExtendedStyle (LVS_EX_HEADERDRAGDROP | LVS_EX_GRIDLINES);
	m_room_list.InsertColumn (0, "�����", LVCFMT_LEFT, 60, 0);
	m_room_list.InsertColumn (1, "����״̬", LVCFMT_LEFT, 80, 1);
	m_room_list.InsertColumn (2, "��ǰ����", LVCFMT_LEFT, 80, 2);
	m_room_list.InsertColumn (3, "Ŀ���¶�", LVCFMT_LEFT, 80, 3);
	m_room_list.InsertColumn (4, "����", LVCFMT_LEFT, 45, 4);
	m_room_list.InsertColumn (5, "����", LVCFMT_LEFT, 45, 5);
	m_room_list.InsertColumn (6, "����", LVCFMT_LEFT, 45, 6);
	m_room_list.InsertColumn (7, "IP��ַ", LVCFMT_LEFT, 135, 7);
	m_room_list.InsertColumn (8, "�˿�", LVCFMT_LEFT, 60, 8);

	//���б�ؼ������4�������
	m_room_list.InsertItem(0, "101");
	m_room_list.InsertItem(1, "102");
	m_room_list.InsertItem(2, "103");
	m_room_list.InsertItem(3, "104");

	//�趨Ĭ��ˢ��Ƶ�ʣ�Ĭ��1��һ�Σ�
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

void CCACDlg::OnOpen() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	//��������յ���������
    central.setState(WAITING);
	m_state_text.Format("����");
	m_state_ctrl.ShowWindow(false);
	m_state_ctrl.ShowWindow(true);
	central.setMode((m_mode_select.GetCheck()) ? COLD : WARM);
	central.ini_cur_temp = m_ini_cur_temp;
	central.ini_tar_temp = m_ini_tar_temp;
	
	//�ж�����ĸ�������Ƿ�Ϸ�,���Ϸ���������յ�˳�����������������������
	switch(central.getMode())
	{
		case COLD:
			if (central.ini_cur_temp <= COLD_MAX)
			{
				AfxMessageBox("��ʼ���� �����������ģʽ�£������� ����25.0 �ĸ�������");
			    return;
			}
			if (central.ini_tar_temp < COLD_MIN || central.ini_tar_temp > COLD_MAX)
			{
				AfxMessageBox("��ʼĿ���¶� �����������ģʽ�£������� 18.0 �� 25.0 �ĸ�������");
			    return;
			}
			m_mode_text.Format("����");
			UpdateData(false);
			m_mode_ctrl.ShowWindow(false);
			m_mode_ctrl.ShowWindow(true);
			break;
		case WARM:
			if (central.ini_cur_temp >= WARM_MIN)
			{
				AfxMessageBox("��ʼ���� �����������ģʽ�£������� С��25.0 �ĸ�������");
			    return;
			}
			if (central.ini_tar_temp < WARM_MIN || central.ini_tar_temp > WARM_MAX)
			{
				AfxMessageBox("��ʼĿ���¶� �����������ģʽ�£������� 25.0 �� 30.0 �ĸ�������");
			    return;
			}
			m_mode_text.Format("����");
			UpdateData(false);
			m_mode_ctrl.ShowWindow(false);
			m_mode_ctrl.ShowWindow(true);
			break;
		default:
			break;
	}

	//�����󣬿�����ť��ģʽѡ�񡢳�ʼ���ºͳ�ʼĿ���¶ȵ����þ������ã�������ť��Ϊ���ã�ϵͳʱ�估���������ʾ�б��Ϊ����    
	m_open.EnableWindow(FALSE);
	m_mode_select.EnableWindow(FALSE);
	((CButton *)GetDlgItem(IDC_RADIO_WARM))->EnableWindow(FALSE);
	m_ini_cur_temp_ctrl.EnableWindow(FALSE);
	m_ini_tar_temp_ctrl.EnableWindow(FALSE);
	m_close.EnableWindow(TRUE);
	m_time_ctrl.ShowWindow(TRUE);
	m_room_list.EnableWindow(TRUE);

	//�����󣬳�ʼʱû�дӿض˵��¿������������յ�����
	central.setState(WAITING);

	//Ϊ��ʱ��ʾ���ü�����������ȡϵͳʱ��
	setTime();
    SetTimer(1,1000,NULL); 

	//Ϊ�����¿�����б��ˢ�����ü�����
	SetTimer(2,GLOBAL.refresh_freq,NULL);

	//���÷����¿��б��������з���ĳ�ʼ���¡���ʼĿ���¶�
	int i;
	for (i = 0; i <= ROOM_AMOUNT - 1; i++)
	{
		rooms[i].setCurTemp(central.ini_cur_temp);
		rooms[i].setTarTemp(central.ini_tar_temp);
	}
	setListInfo();

//����ͨ�����============================================================

	//ʹ��SOCKETǰ�����SOCKET�İ�װ���
    WORD Version;
    WSADATA wsaData;
    Version=MAKEWORD(1,1);
	PHOSTENT hostinfo;//����host��Ϣ
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

	//�������ض��׽��֣����ڿ�ʼ���Խ��ܴӿض���������
	central_socket.dlgp = this;	

	//��ȡ����IP
	CString hostip;
	char name[20]="";
	if((hostinfo = gethostbyname(name)) != NULL)
	    hostip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
	m_host_ip_text = hostip;

	central_socket.Create(5005,SOCK_STREAM,hostip);	//�����׽���
	BOOL ret = central_socket.Listen();				//���׽������ڼ���ģʽ
	
	if (ret)
	{
	    AfxMessageBox("�����������ɹ���");
	}
	else
	{
	    AfxMessageBox("����������ʧ�ܡ�");
	}
}

void CCACDlg::OnCloseClicked() 
{
	// TODO: Add your control notification handler code here
	
	//�ػ��󣬹ػ���ť�����ã�ϵͳʱ�估���������ʾ�б����ã�������ť��ģʽѡ�񡢳�ʼ���ºͳ�ʼĿ���¶ȵ����þ���Ϊ����    
	m_open.EnableWindow(TRUE);
	m_mode_select.EnableWindow(TRUE);
	((CButton *)GetDlgItem(IDC_RADIO_WARM))->EnableWindow(TRUE);
	m_ini_cur_temp_ctrl.EnableWindow(TRUE);
	m_ini_tar_temp_ctrl.EnableWindow(TRUE);
	m_close.EnableWindow(FALSE);
	m_time_ctrl.ShowWindow(FALSE);
	m_room_list.EnableWindow(FALSE);

	//�ػ�������յ��ر�
	central.setState(CLOSED);
	central.setMode(STANDBY);
	m_state_text.Format("�ر�");
	m_mode_text.Format("����");
	UpdateData(false);
	m_state_ctrl.ShowWindow(false);
	m_mode_ctrl.ShowWindow(false);
	m_state_ctrl.ShowWindow(true);
	m_mode_ctrl.ShowWindow(true);

	//�ر�ϵͳʱ������������´ο���ʱ������	
	KillTimer(1);

	//�ر��б�ˢ�¼����������´ο���ʱ������	
	KillTimer(2);

	//�����з��䷢�����عػ��ź�
	IamClosing();

	//��ʼ��ϵͳ��Ϣ
	initiation();

	//���ķ����¿�����б���ʾ����Ϣ
	setListInfo();

}

void CCACDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	int i;
	switch(nIDEvent)
	{
		case 1:
			//����ϵͳʱ����ʾ
			setTime();
			m_time_text.Format( "%4d��%2d��%2d��%2d��%2d��%2d��", 
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

			//���㷿�����¡��ͷ��������õ���Ϣ
			calculate();

			//������䷢�����ݰ�
			for (i = 0 ; i <= ROOM_AMOUNT - 1; i ++)
			{
			    if (rooms[i].getPort() != 0)
				{
					sendPacket((*slave_list[i]),i);
				}

			}

			//�趨����յ��Ĺ���״̬����û�з������¿������������������
			central.setState(WORKING);
			for (i = 0 ; i <= ROOM_AMOUNT - 1 ; i ++)
			{
			    if (rooms[i].getState() == WORKING)
				{
					m_state_text.Format("����");
					break;
				}
			}
			if ( i == ROOM_AMOUNT)
			{
				central.setState(WAITING);
				m_state_text.Format("����");
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
	//�����з��䷢�����عػ��ź�
	IamClosing();
	CDialog::OnClose();
}

void CCACDlg::OnCheckLog() 
{
	// TODO: Add your control notification handler code here
	CLOGDlg dlg;
	dlg.DoModal();
}
