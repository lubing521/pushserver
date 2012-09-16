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

#define  LOG_EMERG   "0" //用于紧急消息, 常常是那些崩溃前的消息.
#define  LOG_ALERT   "1" //需要立刻动作的情形
#define  LOG_CRIT    "2" //严重情况, 常常与严重的硬件或者软件失效有关.
#define  LOG_ERR     "3" //用来报告错误情况;
#define  LOG_WARNING "4" //有问题的情况的警告, 这些情况自己不会引起系统的严重问题
#define  LOG_NOTICE  "5" //正常情况, 但是仍然值得注意. 在这个级别一些安全相关的情况会报告.
#define  LOG_INFO    "6" //信息型消息. 在这个级别, 很多驱动在启动时打印它们发现的硬件的信息.
#define  LOG_DEBUG   "7"  //用作调试消息


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

#define  CK_MAX_INFO_LEN 600
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
	 string send_id;            //信息Send_ID
	 time_t starttime;
	 time_t expired; //timestamp 过期时间
	 string cmd; //指令
	 string title;//标题
	 string info;  //内容
	 unsigned int send_count;
	 
 };

 
//终端队列 imei is key
typedef std::map<string, CCLient*> CLIENT_MAP;
//信息列表  send_id is key
typedef std::map<string,Cinfo*> INFO_MAP;
//database imei,send_id map
typedef std::map<string, string> IMEIID_MAP;

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

//
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
	unsigned int	local_port;     //监听端口
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