//各个自定义类的头文件====================================
#include "TransParentButton.h"
#include "SlaveSocket.h"

//符号常量================================================

//颜色
#define DLG_BG_COLOR RGB(153,204,255)//对话框背景颜色
#define DLG_TEXT_COLOR RGB(0,0,0)//对话框文字颜色
#define EDIT_BG_COLOR RGB(153,255,255)//编辑框背景颜色
#define EDIT_TEXT_COLOR RGB(0,0,255)//编辑框文字颜色

//工作模式符号常量
#define COLD 0
#define WARM 1
#define STANDBY 2

//工作状态符号常量
#define WAITING 0
#define WORKING 1
#define CLOSED 2

//温度范围符号常量
#define COLD_MAX 25.0
#define COLD_MIN 18.0
#define WARM_MAX 30.0
#define WARM_MIN 25.0

//风速符号常量
#define SLOW 0
#define MEDIUM 1
#define FAST 2
#define NONE 3

//不同风速产生的室温变化常量
#define LOW 0.1
#define MED 0.2
#define HIGH 0.3

//计数器编号
#define GTimer 1//全局计数器

//访问全局区的宏
#define GLOBAL (*(CSACApp*)AfxGetApp())

typedef struct virtualtime//系统时间结构
{
    int year,month,day,hour,min,sec;
} VIRTUALTIME;

//Room类
class Room
{
  protected:
    int no;//房间号
	int count;//开关次数
	double cur_temp,tar_temp;//当前室温、目标温度
	double amount;//送风量
	int cost;//费用
	int speed,state;//风速、工作状态
	int mode;//工作模式
	CString ip;//从控端IP地址
	int port;//从控端连接至主控端的端口

  public:
	
	//获取信息接口
	int getRoomNo(void){return no;}//获取房间号	
	double getCurTemp(void){return cur_temp;}//获取当前室温	
	double getTarTemp(void){return tar_temp;}//获取目标温度	
	int getSpeed(void){return speed;}//获取风速
	int getState(void){return state;}//获取当前工作状态
	double getAmount(void){return amount;}//获取房间总的送风量
	int getCost(void){return cost;}//获取房间总的费用
	int getCount(void){return count;}//获取房间总的空调开关次数
	CString getIP(void){return ip;}//获取房间对应的从控端的IP
	int getPort(void){return port;}//获取从控端端口
	int getMode(void){return mode;}//获取工作模式

	//设定信息接口
	void setRoomNo(int n){no = n;}//设定房间号	
	void setCurTemp(double n){cur_temp = n;}//设定当前室温
	void setTarTemp(double n){tar_temp = n;}//设定目标温度	
	void setSpeed(int n){speed = n;}//设定风速	
	void setState(int n){state = n;}//设定工作状态
	void setAmount(double n){amount = n;}//获取房间总的送风量
	void setCost(int n){cost = n;}//设定房间总的费用
	void setCount(int n){count = n;}//设定房间总的空调开关次数
	void setIP(CString n){ip = n;}//设定房间对应从控端的IP
	void setPort(int n){port = n;}//设定从控端端口
	void setMode(int n){mode = n;}//设定工作模式
};
extern char pack[20];//接收包缓冲
extern Room room;//房间信息
extern CSlaveSocket slave_socket;//连接主控端的套接字

extern bool change_speed;//风速被更改的状态标志，用以同步发送风速更改请求
extern bool change_tar_temp;//目标温度被更改的状态标志，用以同步发送目标温度请求
extern bool change_state;//工作状态改变标志

