// stdafx.cpp : source file that includes just the standard includes
//	SAC.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"


//全局变量========================================================
Room room;

CSlaveSocket slave_socket;//连接主控端的套接字

bool change_speed;//风速被更改的状态标志，用以同步发送风速更改请求
bool change_tar_temp;//目标温度被更改的状态标志，用以同步发送目标温度请求
bool change_state;//工作状态改变标志