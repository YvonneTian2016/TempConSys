// stdafx.cpp : source file that includes just the standard includes
//	SAC.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"


//ȫ�ֱ���========================================================
Room room;

CSlaveSocket slave_socket;//�������ض˵��׽���

bool change_speed;//���ٱ����ĵ�״̬��־������ͬ�����ͷ��ٸ�������
bool change_tar_temp;//Ŀ���¶ȱ����ĵ�״̬��־������ͬ������Ŀ���¶�����
bool change_state;//����״̬�ı��־