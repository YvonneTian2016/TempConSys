// ADO.cpp: implementation of the ADO class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CAC.h"
#include "ADO.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ADO::ADO()
{
}

ADO::~ADO()
{
}

//**************************************************//
//�������ܣ��������ݿ�								//
//**************************************************//
void ADO::OnInitADOConn()
{
	::CoInitialize(NULL);    //��������
	try
	{
       m_pConnection.CreateInstance("ADODB.Connection");	//�������Ӷ���ʵ��
	   _bstr_t strConnect="DRIVER={Microsoft Access Driver (*.mdb)};\
			uid=;pwd=;DBQ=log.mdb;";				//���ӵ�AirConditioneGLOBAL.r.mdb
	   m_pConnection->Open(strConnect,"","",adModeUnknown); //�����ݿ�
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description()); //����������
	}
}

//**************************************************//
//�������ܣ��򿪼�¼��								//
//**************************************************//
_RecordsetPtr& ADO::OpenRecordset(CString sql)
{
	ASSERT(!sql.IsEmpty());									//SQL��䲻��Ϊ��
	try
	{
		m_pRecordset.CreateInstance(__uuidof(Recordset));	//������¼������ʵ��
		m_pRecordset->Open(_bstr_t(sql), m_pConnection.GetInterfacePtr(),
			adOpenDynamic, adLockOptimistic, adCmdText); 	//ִ��SQL�õ���¼��
	}
	catch(_com_error e)										//������ܵ��쳣
	{
		AfxMessageBox(e.Description());
	}
	return m_pRecordset;
}

//**************************************************//
//�������ܣ��رռ�¼��								//
//**************************************************//
void ADO::CloseRecordset()
{
	if(m_pRecordset->GetState() == adStateOpen)				//�жϵ�ǰ�ļ�¼��״̬
		m_pRecordset->Close();								//�رռ�¼��
}

//**************************************************//
//�������ܣ��ر����ݿ�����							//
//**************************************************//
void ADO::CloseConn()
{
	m_pConnection->Close();									//�ر����ݿ�����
	::CoUninitialize();										//�ͷ�COM����
}


void ADO::addlogr()
{
    ADO m_Ado;								//ADO����󣬽���Ϣд�����ݿ�
    CString sql;
    m_Ado.OnInitADOConn();					//�������ݿ�
    switch(GLOBAL.r.roomnum)
	{
	case 1:sql.Format("insert into room1 values(%d,%s,%d,%d,%d)",GLOBAL.r.turnsum,GLOBAL.r.begtime,GLOBAL.r.starttem,GLOBAL.r.endtem,GLOBAL.r.airspeed);
           break;
	case 2:sql.Format("insert into room2 values(%d,%s,%d,%d,%d)",GLOBAL.r.turnsum,GLOBAL.r.begtime,GLOBAL.r.starttem,GLOBAL.r.endtem,GLOBAL.r.airspeed);
           break;
	case 3:sql.Format("insert into room3 values(%d,%s,%d,%d,%d)",GLOBAL.r.turnsum,GLOBAL.r.begtime,GLOBAL.r.starttem,GLOBAL.r.endtem,GLOBAL.r.airspeed);
           break;
	case 4:sql.Format("insert into room4 values(%d,%s,%d,%d,%d)",GLOBAL.r.turnsum,GLOBAL.r.begtime,GLOBAL.r.starttem,GLOBAL.r.endtem,GLOBAL.r.airspeed);
		   break;
	case 5:sql="select * from room1";
		   break;
	}

	m_Ado.m_pRecordset = m_Ado.OpenRecordset(sql);	//�򿪼�¼��

    m_Ado.CloseConn();
}
