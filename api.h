#ifndef API_HH
#define API_HH

//#include "client.h"
class CCLient;
// buffer to int
#define CK_BUF2INT(p)		(((p)[3]<<24)+((p)[2]<<16)+((p)[1]<<8)+(p)[0])
#define CK_BUF2ULONG(p)	((((unsigned char*)p)[3]<<24)+(((unsigned char*)p)[2]<<16)+(((unsigned char*)p)[1]<<8)+((unsigned char*)p)[0])
// int to buffer
#define CK_INT2BUF(n,p)	{(p)[0]=((n)>>24)&0xff;(p)[1]=((n)>>16)&0xff;(p)[2]=((n)>>8)&0xff;(p)[3]=n&0xff;}
#define CK_ULONG2BUF(n,p)	{(p)[3]=(unsigned char)(((unsigned long)n)>>24)&0xff;(p)[2]=(unsigned char)(((unsigned long)n)>>16)&0xff;(p)[1]=(unsigned char)(((unsigned long)n)>>8)&0xff;(p)[0]=(unsigned char)(unsigned long)n&0xff;}
// buffer to short
#define CK_BUF2SHT(p)		(((p)[1]<<8)+(p)[0])
// short to buffer
#define CK_SHT2BUF(n,p)	{(p)[1]=((n)>>8)&0xff;(p)[0]=(n)&0xff;}

typedef enum
{
	THREAD_STATUS_INIT,			///��ʼ��״̬
	THREAD_STATUS_OPEN,			///����״̬
	THREAD_STATUS_CLOSE,		///�ر�״̬
	THREAD_STATUS_STOP,			///ֹͣ״̬
	THREAD_STATUS_SLEEP,		///����
	THREAD_STATIS_ACTIVE,		///����״̬

}THREAD_STATUS;

typedef enum 
{
	DEBUG_ONLY_LEVEL,
	LOG_LOG_LEVEL,
	WARNNING_LEVEL, ///����
	ERROR_LEVEL,    ///�д���Ӱ�������ȷ����
	CRITICAL_LEVEL,   ///��Ҫ������Ǵ�������Ҫ�����������������������Ҫ��Ϣ
}LOG_LEVEL;

#define  LOG_EMERG   "0" //���ڽ�����Ϣ, ��������Щ����ǰ����Ϣ.
#define  LOG_ALERT   "1" //��Ҫ���̶���������
#define  LOG_CRIT    "2" //�������, ���������ص�Ӳ���������ʧЧ�й�.
#define  LOG_ERR     "3" //��������������;
#define  LOG_WARNING "4" //�����������ľ���, ��Щ����Լ���������ϵͳ����������
#define  LOG_NOTICE  "5" //�������, ������Ȼֵ��ע��. ���������һЩ��ȫ��ص�����ᱨ��.
#define  LOG_INFO    "6" //��Ϣ����Ϣ. ���������, �ܶ�����������ʱ��ӡ���Ƿ��ֵ�Ӳ������Ϣ.
#define  LOG_DEBUG   "7"  //����������Ϣ


#define CKMIN(a,b) ((a)>(b)?(b):(a))
#define CKERROR (-1)

// �ָ��ַ�
#define SEPARATE_COMMA		0x2C	// (',')
#define SEPARATE_SEMICOLON	0x3B	// (';')


#include <list>
#include <map>
#include <vector>
#include <string>
using namespace std;

#define IMEI_LEN     15
#define	MAX_REQ_BUF_LEN	80     //��������ִ�<80

#define  CK_MAX_INFO_LEN 600
#define  CK_MAX_TITLE_LEN 100
#define  CK_CMD_MAX_LEN 4
//��̬��Ϣ��
 class Cinfo 
 {
 public:
	 Cinfo();
	 Cinfo(const char* mtitle,const char* minfo,const char* mcmd,time_t start,time_t stop,const char* sendid,unsigned int sendcount){
		 title=mtitle;
		 info=minfo;
		 cmd=mcmd;
		 expired = stop;
		 starttime = start;
		 send_id = sendid;
		 send_count=sendcount;
	 }
	 string send_id;            //��ϢSend_ID
	 time_t starttime;
	 time_t expired; //timestamp ����ʱ��
	 string cmd; //ָ��
	 string title;//����
	 string info;  //����
	 unsigned int send_count;
	 
 };

 
//�ն˶��� imei is key
typedef std::map<string, CCLient*> CLIENT_MAP;
//��Ϣ�б�  send_id is key
typedef std::map<string,Cinfo*> INFO_MAP;
//database imei,send_id map
typedef std::map<string, string> IMEIID_MAP;

//
typedef vector< HANDLE > HL;  //�߳̾������
typedef HL::iterator HLI;     //�߳̾��ָ��
// 
////autolock �Զ���
class CAutoLock
{
public:
	CAutoLock(CRITICAL_SECTION *pcs):m_pcs(pcs)
	{
		EnterCriticalSection(m_pcs);
	}
	~CAutoLock(){
		LeaveCriticalSection(m_pcs);
	}

private:
	CRITICAL_SECTION * m_pcs;
};

//
/****************************************************************** 
* per_io ���� 
*******************************************************************/ 
#define PER_IO_BUFFER_SIZE 255
typedef struct _PER_IO_DATA 
{ 
    OVERLAPPED  ol;                 // �ص��ṹ 
    char        buf[PER_IO_BUFFER_SIZE];   // ���ݻ����� 
    int         nOperationType;     // ��������

#define OP_READ   1 
#define OP_WRITE 2 
#define OP_ACCEPT 3
	
}PER_IO_DATA, *PPER_IO_DATA;


/////////////////////////////////////////

///���ڡ�ʱ����������
typedef struct
{
	BYTE year; 			///��
	BYTE month;			///��
	BYTE day;			///��
	BYTE hour; 			///ʱ
	BYTE min;			///��
	BYTE sec;			///��
}GC_Time_Struct;


extern void LogExt(int loglevel,const char* lpszFormat,...);

///////////
char *getYYYYMMDD(char *nowdate);
void stopFrommyInter();
void setallthreadexitflag();
void exceptiontolog (CSeException *e);
extern bool volatile allExitFlag;

extern Clog	g_log;
extern CRITICAL_SECTION g_cs;


#ifdef _DEBUG
	#define DEBUGOUT  OutputDebugString
#else
	#define DEBUGOUT
#endif

class CFG{
public:
	// local
	unsigned int	local_port;     //�����˿�
	unsigned int max_works_num;  //�����̸߳���
	unsigned int max_clients_num;
	//out time
	unsigned int outtime;//client ���Ӻ��ñ��뷢��GET����
	string local_ip;     
	//mysql 
	string db_ip; 
	unsigned int db_port;
	string db_user;
	string db_psw;
	string db_name;

	
};
struct tcp_keepalive_in
{
    ULONG onoff;
    ULONG keepalivetime;
    ULONG keepaliveinterval;
};
#ifndef SIO_KEEPALIVE_VALS
#define SIO_KEEPALIVE_VALS    _WSAIOW(IOC_VENDOR, 4)
#endif

int writelogimmediatly(const char *msg);
#endif 