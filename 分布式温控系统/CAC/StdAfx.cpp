// stdafx.cpp : source file that includes just the standard includes
//	CAC.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "CACDlg.h"

//ȫ�ֱ���================================================

Room rooms[ROOM_AMOUNT];//������Ϣ
Central central;//����յ�

CCentralSocket central_socket;			//���ض˼������ӵ��׽��� 
CSlaveSocket* slave_list[ROOM_AMOUNT];       //�ӿض��׽����б�
//========================================================

