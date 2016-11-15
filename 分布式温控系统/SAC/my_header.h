//�����Զ������ͷ�ļ�====================================
#include "TransParentButton.h"
#include "SlaveSocket.h"

//���ų���================================================

//��ɫ
#define DLG_BG_COLOR RGB(153,204,255)//�Ի��򱳾���ɫ
#define DLG_TEXT_COLOR RGB(0,0,0)//�Ի���������ɫ
#define EDIT_BG_COLOR RGB(153,255,255)//�༭�򱳾���ɫ
#define EDIT_TEXT_COLOR RGB(0,0,255)//�༭��������ɫ

//����ģʽ���ų���
#define COLD 0
#define WARM 1
#define STANDBY 2

//����״̬���ų���
#define WAITING 0
#define WORKING 1
#define CLOSED 2

//�¶ȷ�Χ���ų���
#define COLD_MAX 25.0
#define COLD_MIN 18.0
#define WARM_MAX 30.0
#define WARM_MIN 25.0

//���ٷ��ų���
#define SLOW 0
#define MEDIUM 1
#define FAST 2
#define NONE 3

//��ͬ���ٲ��������±仯����
#define LOW 0.1
#define MED 0.2
#define HIGH 0.3

//���������
#define GTimer 1//ȫ�ּ�����

//����ȫ�����ĺ�
#define GLOBAL (*(CSACApp*)AfxGetApp())

typedef struct virtualtime//ϵͳʱ��ṹ
{
    int year,month,day,hour,min,sec;
} VIRTUALTIME;

//Room��
class Room
{
  protected:
    int no;//�����
	int count;//���ش���
	double cur_temp,tar_temp;//��ǰ���¡�Ŀ���¶�
	double amount;//�ͷ���
	int cost;//����
	int speed,state;//���١�����״̬
	int mode;//����ģʽ
	CString ip;//�ӿض�IP��ַ
	int port;//�ӿض����������ض˵Ķ˿�

  public:
	
	//��ȡ��Ϣ�ӿ�
	int getRoomNo(void){return no;}//��ȡ�����	
	double getCurTemp(void){return cur_temp;}//��ȡ��ǰ����	
	double getTarTemp(void){return tar_temp;}//��ȡĿ���¶�	
	int getSpeed(void){return speed;}//��ȡ����
	int getState(void){return state;}//��ȡ��ǰ����״̬
	double getAmount(void){return amount;}//��ȡ�����ܵ��ͷ���
	int getCost(void){return cost;}//��ȡ�����ܵķ���
	int getCount(void){return count;}//��ȡ�����ܵĿյ����ش���
	CString getIP(void){return ip;}//��ȡ�����Ӧ�Ĵӿض˵�IP
	int getPort(void){return port;}//��ȡ�ӿض˶˿�
	int getMode(void){return mode;}//��ȡ����ģʽ

	//�趨��Ϣ�ӿ�
	void setRoomNo(int n){no = n;}//�趨�����	
	void setCurTemp(double n){cur_temp = n;}//�趨��ǰ����
	void setTarTemp(double n){tar_temp = n;}//�趨Ŀ���¶�	
	void setSpeed(int n){speed = n;}//�趨����	
	void setState(int n){state = n;}//�趨����״̬
	void setAmount(double n){amount = n;}//��ȡ�����ܵ��ͷ���
	void setCost(int n){cost = n;}//�趨�����ܵķ���
	void setCount(int n){count = n;}//�趨�����ܵĿյ����ش���
	void setIP(CString n){ip = n;}//�趨�����Ӧ�ӿض˵�IP
	void setPort(int n){port = n;}//�趨�ӿض˶˿�
	void setMode(int n){mode = n;}//�趨����ģʽ
};
extern char pack[20];//���հ�����
extern Room room;//������Ϣ
extern CSlaveSocket slave_socket;//�������ض˵��׽���

extern bool change_speed;//���ٱ����ĵ�״̬��־������ͬ�����ͷ��ٸ�������
extern bool change_tar_temp;//Ŀ���¶ȱ����ĵ�״̬��־������ͬ������Ŀ���¶�����
extern bool change_state;//����״̬�ı��־

