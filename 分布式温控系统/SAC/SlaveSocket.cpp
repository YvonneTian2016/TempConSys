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

	//接收数据包
	slave_socket.Receive(packet,9,0);
	decode_packet(packet,&type,&ini_tar_temp,&cur_temp);
	//根据从控机状态不同，执行不同动作
	switch(room.getState())
	{
		case WAITING://从控端待机时
		
			if (type == 2)//收到主控发来的允许温控请求信号
			{
			    room.setState(WORKING);//从控端开始工作。从此时开始，从控端从主控端接受温度等数据
				change_state = true;//工作状态改变
			}
			else if (type == 0)//收到主控发来的主控关机信号
			{
				slave_socket.Close();//关闭与主控端的连接
				AfxMessageBox("主控端已关机。");
			}
			break;
		case WORKING://从控端处于工作状态时
			if (type == 2)//收到主控发来的室温等信息
			{
			    room.setCurTemp(cur_temp);
			}
			else if (type == 3)//收到主控发来的待机信息
			{
			    //房间空调待机
				room.setState(WAITING);
				change_state = true;
			}
			else if (type == 0)//收到主控发来的主控关机信号
			{
				slave_socket.Close();//关闭与主控端的连接
				AfxMessageBox("主控端已关机。");
			}
			break;
	}
	CSocket::OnReceive(nErrorCode);
}
