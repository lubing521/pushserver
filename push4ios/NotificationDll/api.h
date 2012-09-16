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
	THREAD_STATUS_INIT,			///初始化状态
	THREAD_STATUS_OPEN,			///开启状态
	THREAD_STATUS_CLOSE,		///关闭状态
	THREAD_STATUS_STOP,			///停止状态
	THREAD_STATUS_SLEEP,		///挂启
	THREAD_STATIS_ACTIVE,		///激活状态

}THREAD_STATUS;

typedef enum 
{
	DEBUG_ONLY_LEVEL,
	LOG_LOG_LEVEL,
	WARNNING_LEVEL, ///警告
	ERROR_LEVEL,    ///有错，不影响后续正确运行
	CRITICAL_LEVEL,   ///重要：如果是错误则需要重启，如果是正常，则是重要信息
}LOG_LEVEL;


#define CKMIN(a,b) ((a)>(b)?(b):(a))
#define CKERROR (-1)

// 分隔字符
#define SEPARATE_COMMA		0x2C	// (',')
#define SEPARATE_SEMICOLON	0x3B	// (';')


#include <list>
#include <map>
#include <vector>
#include <string>
using namespace std;

#define IMEI_LEN     15
#define	MAX_REQ_BUF_LEN	80     //最大请求字串<80

#define  CK_MAX_INFO_LEN 256
#define  CK_MAX_TITLE_LEN 100
#define  CK_CMD_MAX_LEN 4
//动态信息点
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
	 string send_id;            //信息ID
	 time_t starttime;
	 time_t expired; //timestamp 过期时间
	 string cmd; //指令
	 string title;//标题
	 string info;  //内容
	 unsigned int send_count;
 };

 class CDevice
 {
 public:
	 CDevice(){}
	CDevice(const char*stoken, time_t st)
	{
		m_token = stoken;
		m_createtime = st;
	}

public:
	string m_token;
	time_t m_createtime;
 };
  //注册设备
 class CRegDevice : public CDevice
 {
 public:	 
	 CRegDevice(const char* stoken,UINT uid)
	 {
		m_id    = uid;
		m_token = stoken;
		m_createtime =time(NULL);
	 }
	 CRegDevice(const char* stoken,UINT uid, time_t reg_timestamp,const char* sended_id)
	 {
		 m_id = uid;
		 m_token = stoken;
		 m_createtime = reg_timestamp;
		 m_sended_id = sended_id;
	 }

 public:
	 UINT m_id; ///id in database table;设备id序号 唯一
	 string m_sended_id;
	 
 };

 #ifdef REMEMBER_STATUS
 class CSendStatus
 {
 public:
	 CSendStatus():info_id(""),device_id(0),device_token(""){}
	 CSendStatus(string infoid,UINT deviceid){
		 info_id =infoid;
		 device_id =deviceid;
	 }

	 string info_id;//msg信息id即 send_id :char(12)
	 UINT device_id;//设备id即ios注册表中relation_id 
	 string device_token;//
 };
#endif
//registed 终端队列   token is key
typedef std::map<string,CRegDevice*> REGDEVICE_MAP;
//信息列表  send_id is key
typedef std::map<string,Cinfo*> INFO_MAP;

//unregisted 终端队列  token is key
typedef std::map<string,CDevice*> UNREGDEVICE_MAP;// unregDeviceMap;
//
typedef vector< HANDLE > HL;  //线程句柄集合
typedef HL::iterator HLI;     //线程句柄指针
// 

////autolock 自动锁
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

/****************************************************************** 
* per_io 数据 
*******************************************************************/ 
#define PER_IO_BUFFER_SIZE 255
typedef struct _PER_IO_DATA 
{ 
    OVERLAPPED  ol;                 // 重叠结构 
    char        buf[PER_IO_BUFFER_SIZE];   // 数据缓冲区 
    int         nOperationType;     // 操作类型

#define OP_READ   1 
#define OP_WRITE 2 
#define OP_ACCEPT 3
	
}PER_IO_DATA, *PPER_IO_DATA;


/////////////////////////////////////////

///日期、时间数据类型
typedef struct
{
	BYTE year; 			///年
	BYTE month;			///月
	BYTE day;			///日
	BYTE hour; 			///时
	BYTE min;			///分
	BYTE sec;			///秒
}GC_Time_Struct;


extern void LogExt(int loglevel,const char* lpszFormat,...);

///////////
char *getYYYYMMDD(char *nowdate);
void stopFrommyInter();
void setallthreadexitflag();
void exceptiontolog (CSeException *e);
extern volatile bool allExitFlag;
//extern bool stopServiceFlag;

extern Clog	g_log;


#ifdef _DEBUG
	#define DEBUGOUT  OutputDebugString
#else
	#define DEBUGOUT
#endif

class CFG{
public:
	// local
	unsigned int local_port;     //监听端口
	unsigned int max_works_num;  //工作线程个数
	unsigned int max_clients_num;
	//out time
	unsigned int outtime;//client 连接后多久必须发送GET请求
	string local_ip;     
	//mysql 
	string db_ip; 
	unsigned int db_port;
	string db_user;
	string db_psw;
	string db_name;
	//apple
	string feedback_www;
	unsigned int feedback_port;
    string feedback_sandbox_www;
	unsigned int feedback_sandbox_port;
    
	string APNs_www;
	unsigned int APNs_port;
	string APNs_sandbox_www;
	unsigned int APNs_sandbox_port;

	string sandbox_pem_file;
	string pem_file;
	string pem_psw;  /*Password for the key file*/

	////load db 
	unsigned int loaddb_interval_minutes;

	//sandbox or production
	int sandbox0_or_production1;
	
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
string GetIPbyHostName(const char* hostname);

#endif 