// Clientlog.h: interface for the CClientlog class.
//
//////////////////////////////////////////////////////////////////////


#if !defined(AFX_CLIENTLOG_H__59642F50_84BB_421E_BB71_4FCC1A098856__INCLUDED_)
#define AFX_CLIENTLOG_H__59642F50_84BB_421E_BB71_4FCC1A098856__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#ifdef _DEBUG
#define  FILE_CACHE_SIZE 0x00001000
#else
#define  FILE_CACHE_SIZE 0x00001000  /*  4K */ 
#endif
#define  HALF_CACHE_SIZE (FILE_CACHE_SIZE)

class Clog  
{
public:
	Clog();
	virtual ~Clog();

	
	
private:
#ifdef MEMMAP
	CRITICAL_SECTION log_sc;
	HANDLE hMapFile1;
	HANDLE hMapFile2;
	void* pvFile1;
	void* pvFile2;
	unsigned char *pmapbuf;
	unsigned char *pmapbuf_head;
	UINT imemfilelen;
	UINT imemfilelen_c;//当前缓冲区字符长度
	unsigned char *pmapbuf_c;//要写文件的缓存指针
	unsigned char *g_membuf1;//[FILE_CACHE_SIZE];
	unsigned char *g_membuf2;//[FILE_CACHE_SIZE];
	
	void iniMemMapFile();
	void closeMMapFile();
	bool writetoMemMapFile(const char* buf,int len);
	bool writelogfile(unsigned char *mmbuf ,int ilen);
#endif
	int  writelog(const char* path,const char *type,const char *msg);
	

#ifdef LOGTOREMOTE
	int sockfd;
	int m_sendtimeout;
	int m_recvtimeout;
	int m_port;
	char m_ip[20];
	bool initedflag;
#endif
	int m_log_level;
public:
#ifdef LOGTOREMOTE
	void close();
#endif
	bool log(const char* msg,int loglevel);
	void setloglevel(int loglevel);

private:
#ifdef LOGTOREMOTE
	bool Connect();
	bool SetRecvTimeOut(int t);
	bool SetSendTimeOut(int t);
	int  Send(const char *lp , int len );
	int Recv(char*lp, int len);
	bool inicfg();
#endif

};

#endif // !defined(AFX_CLIENTLOG_H__59642F50_84BB_421E_BB71_4FCC1A098856__INCLUDED_)
