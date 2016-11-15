// stdafx.cpp : source file that includes just the standard includes
//	CAC.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "CACDlg.h"

//全局变量================================================

Room rooms[ROOM_AMOUNT];//房间信息
Central central;//中央空调

CCentralSocket central_socket;			//主控端监听连接的套接字 
CSlaveSocket* slave_list[ROOM_AMOUNT];       //从控端套接字列表
//========================================================

