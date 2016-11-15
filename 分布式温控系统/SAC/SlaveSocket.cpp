// SlaveSocket.cpp : implementation file
//

#include "stdafx.h"
#include "SAC.h"
#include "SlaveSocket.h"
#include "SACDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSlaveSocket

CSlaveSocket::CSlaveSocket()
{
}

CSlaveSocket::~CSlaveSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSlaveSocket, CSocket)
	//{{AFX_MSG_MAP(CSlaveSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CSlaveSocket member functions

void CSlaveSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	char packet[10]="";
	int type;
	double ini_tar_temp,cur_temp;

	//�������ݰ�
	slave_socket.Receive(packet,9,0);
	decode_packet(packet,&type,&ini_tar_temp,&cur_temp);
	//���ݴӿػ�״̬��ͬ��ִ�в�ͬ����
	switch(room.getState())
	{
		case WAITING://�ӿض˴���ʱ
		
			if (type == 2)//�յ����ط����������¿������ź�
			{
			    room.setState(WORKING);//�ӿض˿�ʼ�������Ӵ�ʱ��ʼ���ӿض˴����ض˽����¶ȵ�����
				change_state = true;//����״̬�ı�
			}
			else if (type == 0)//�յ����ط��������عػ��ź�
			{
				slave_socket.Close();//�ر������ض˵�����
				AfxMessageBox("���ض��ѹػ���");
			}
			break;
		case WORKING://�ӿض˴��ڹ���״̬ʱ
			if (type == 2)//�յ����ط��������µ���Ϣ
			{
			    room.setCurTemp(cur_temp);
			}
			else if (type == 3)//�յ����ط����Ĵ�����Ϣ
			{
			    //����յ�����
				room.setState(WAITING);
				change_state = true;
			}
			else if (type == 0)//�յ����ط��������عػ��ź�
			{
				slave_socket.Close();//�ر������ض˵�����
				AfxMessageBox("���ض��ѹػ���");
			}
			break;
	}
	CSocket::OnReceive(nErrorCode);
}
