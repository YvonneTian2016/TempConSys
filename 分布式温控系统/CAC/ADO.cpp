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
//函数功能：连接数据库								//
//**************************************************//
void ADO::OnInitADOConn()
{
	::CoInitialize(NULL);    //建立环境
	try
	{
       m_pConnection.CreateInstance("ADODB.Connection");	//创建连接对象实例
	   _bstr_t strConnect="DRIVER={Microsoft Access Driver (*.mdb)};\
			uid=;pwd=;DBQ=log.mdb;";				//连接到AirConditioneGLOBAL.r.mdb
	   m_pConnection->Open(strConnect,"","",adModeUnknown); //打开数据库
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description()); //弹出错误处理
	}
}

//**************************************************//
//函数功能：打开记录集								//
//**************************************************//
_RecordsetPtr& ADO::OpenRecordset(CString sql)
{
	ASSERT(!sql.IsEmpty());									//SQL语句不能为空
	try
	{
		m_pRecordset.CreateInstance(__uuidof(Recordset));	//创建记录集对象实例
		m_pRecordset->Open(_bstr_t(sql), m_pConnection.GetInterfacePtr(),
			adOpenDynamic, adLockOptimistic, adCmdText); 	//执行SQL得到记录集
	}
	catch(_com_error e)										//捕获可能的异常
	{
		AfxMessageBox(e.Description());
	}
	return m_pRecordset;
}

//**************************************************//
//函数功能：关闭记录集								//
//**************************************************//
void ADO::CloseRecordset()
{
	if(m_pRecordset->GetState() == adStateOpen)				//判断当前的记录集状态
		m_pRecordset->Close();								//关闭记录集
}

//**************************************************//
//函数功能：关闭数据库连接							//
//**************************************************//
void ADO::CloseConn()
{
	m_pConnection->Close();									//关闭数据库连接
	::CoUninitialize();										//释放COM环境
}


void ADO::addlogr()
{
    ADO m_Ado;								//ADO类对象，将信息写入数据库
    CString sql;
    m_Ado.OnInitADOConn();					//连接数据库
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

	m_Ado.m_pRecordset = m_Ado.OpenRecordset(sql);	//打开记录集

    m_Ado.CloseConn();
}
