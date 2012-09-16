// Clientlog.cpp: implementation of the CClientlog class.
// 1.log客户端实现：连接log服务器；并实现log功能接口
// 2.无连接，直接写本地
// 3.默认日志级别 debug
//
//  author:张世光 2011.7
// 
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "log.h"
#include "tools.h"
#include "api.h"
#include <string>
#include <iostream>
#include "direct.h"

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
//#define new DEBUG_NEW
#endif


#define  CFGFILE "\\logconfig.ini"

extern Clog g_log;


void LogExt(int loglevel,const char* lpszFormat,...)
{
#ifdef LOGLOG
	_set_se_translator(SeTranslator);
	try
	{
		va_list args;
		va_start(args, lpszFormat);

		int nBuf;
		TCHAR szBuffer[512];
		nBuf = _vsntprintf(szBuffer, 512, lpszFormat, args);

		va_end(args);
		
		//DEBUGOUT(szBuffer);

		if(DEBUG_ONLY_LEVEL == loglevel)
		{
		#ifdef _DEBUG
			g_log.log(szBuffer,loglevel);
		#endif
		}
		else 
		{
			g_log.log(szBuffer,loglevel);
		}

	}
	catch(CSeException *e)
	{
		g_log.log("[exception][LogExt]!",CRITICAL_LEVEL);
		exceptiontolog(e);		
		
	}

#endif
}

#ifdef MEMMAP


void Clog::iniMemMapFile()
{	
	//创建文件的内存映射文件。
	hMapFile1=CreateFileMapping(
		(HANDLE)0xFFFFFFFF,
		NULL,
		PAGE_READWRITE, //对映射文件进行读写
		(DWORD)(FILE_CACHE_SIZE>>32),
		(DWORD)(FILE_CACHE_SIZE & 0xFFFFFFFF), //这两个参数共64位，所以支持的最大文件长度为16EB
		NULL);
	if(hMapFile1==INVALID_HANDLE_VALUE)
	{		
		OutputDebugStr("CreateFileMapping fail!");
		return;
	}
	
	//把文件数据映射到进程的地址空间
	pvFile1=MapViewOfFile(
		hMapFile1,
		FILE_MAP_READ|FILE_MAP_WRITE,
		0,
		0,
		0);
	//2
	hMapFile2=CreateFileMapping(
		(HANDLE)0xFFFFFFFF,
		NULL,
		PAGE_READWRITE, 
		(DWORD)(FILE_CACHE_SIZE>>32),
		(DWORD)(FILE_CACHE_SIZE & 0xFFFFFFFF), 
		NULL);
	if(hMapFile2==INVALID_HANDLE_VALUE)
	{		
		OutputDebugStr("CreateFileMapping fail!");
		return;
	}
	
	
	pvFile2=MapViewOfFile(
		hMapFile2,
		FILE_MAP_READ|FILE_MAP_WRITE,
		0,
		0,
		0);
	
	g_membuf1 =(unsigned char*)pvFile1;
	g_membuf2 =(unsigned char*)pvFile2;
	
	pmapbuf = g_membuf1;
	pmapbuf_head =  pmapbuf;
	imemfilelen = 0;
}

void Clog::closeMMapFile()
{
	writelogfile(pmapbuf_head,imemfilelen);
	UnmapViewOfFile(pvFile1);
	UnmapViewOfFile(pvFile2);
	CloseHandle(hMapFile1);
	CloseHandle(hMapFile2);
}
///内存映射文件满才写一次磁盘
bool Clog::writelogfile(unsigned char *mmbuf ,int ilen)
{
#ifdef LOGLOG
	
 #ifdef WIN32
   #define MAXTIMELEN 23
 #else
   #define MAXTIMELEN 19
 #endif
	static bool doingflg =false;
	if (!doingflg)
	{
		doingflg = true;
	}
	else
	{
		return true;
	}
	
	if (0==ilen || 0==mmbuf)
	{
		doingflg = false;
		return false;
	}
	mmbuf[ilen] ='\0';
	
    char sfile[256];
	char ndate[24];
	memset(ndate,0,sizeof(ndate));
	memset(sfile,0,sizeof(sfile));
	strcpy(sfile,getExePath().c_str());
	strcat(sfile,"\\");
	/*取时间*/
	getnowdate(ndate);	
	left(ndate,0,10,sfile+strlen(sfile));
	mkdir(sfile);
	strcat(sfile,"\\");
	left(ndate,11,2,sfile+strlen(sfile));
	//strcat(sfile,getnowdate(ndate));
	strcat(sfile,".log");
	
	FILE *fp;
	fp = fopen(sfile,"a+");
	if(fp == NULL)
	{
    #ifdef _DEBUG
		char gtext[40];
		sprintf(gtext,"fail to fopen(%s,\"a+\")!",sfile);
		OutputDebugStr(gtext);
    #endif	
		doingflg = false;
		return false;
	}
	
	fprintf(fp,"%s\t%s\n",ndate,mmbuf);
	
	fclose(fp);
	
	doingflg = false;
	
#endif
	
	return true;
	
}

bool Clog::writetoMemMapFile(const char* buf,int len)
{	
#if 0
	try
	{
#endif
		{
			CAutoLock Lock(&log_sc);

			imemfilelen += len;
			
			if (NULL!= pmapbuf && imemfilelen < HALF_CACHE_SIZE)
			{		
				memcpy(pmapbuf, buf,len);
				pmapbuf += len;
			}
			else
			{
				if (pmapbuf_head == this->g_membuf1) //1 满
				{
					pmapbuf_head = g_membuf2;
					pmapbuf_c = g_membuf1;
				} 
				else
				{
					pmapbuf_head = g_membuf1;
					pmapbuf_c = g_membuf2;
				}
				
				pmapbuf    = pmapbuf_head;	
				imemfilelen_c = imemfilelen - len;
				imemfilelen = len;
				
				if (NULL!= pmapbuf && imemfilelen < HALF_CACHE_SIZE)
				{		
					memcpy(pmapbuf, buf,len);				
					pmapbuf += len;
				}
				
				writelogfile(pmapbuf_c,imemfilelen_c);
			}

		}
#if 0
	}
	catch(...)
	{	
#ifdef _DEBUG
		printexception(DEBUGARGS);
#endif
	//	setallthreadexitflag();

	}
#endif	


	return true;
}
#endif




/*写日志文件*/
int Clog::writelog(const char* path,const char *type,const char *msg)
{
#ifdef LOGLOG

	#ifdef MEMMAP
			
		writetoMemMapFile(msg,strlen(msg));
		
	#else	
		////////////////////////////////
		writelogimmediatly(msg);
	#endif
#endif

	return 1;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Clog::Clog():m_log_level(CRITICAL_LEVEL)
#ifdef LOGTOREMOTE
	,initedflag(false),m_port(0)
#endif
{
#ifdef MEMMAP
	hMapFile1 = INVALID_HANDLE_VALUE;
	hMapFile2 = INVALID_HANDLE_VALUE;
	pvFile1   = 0;
	pvFile2   = 0;
	imemfilelen  =0 ;
	pmapbuf_head = NULL;
	pmapbuf      = NULL;
	iniMemMapFile();
	InitializeCriticalSection(&log_sc);
#endif
#ifdef LOGTOREMOTE
	strcpy(m_ip,"127.0.0.1");

	WSADATA   wsaData; 
	int   err; 
	
	err= WSAStartup( MAKEWORD( 2, 2 ), &wsaData); 
    
	sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); 
	if(INVALID_SOCKET ==sockfd)
	{  
#ifdef _DEBUG
		DEBUGOUT("create socket error!\n");
#endif
		writelog(getExePath().c_str(),"log","Clog::Connect socket error!");
	}
#endif
}

Clog::~Clog()
{
#ifdef MEMMAP
	closeMMapFile();
	DeleteCriticalSection(&log_sc);
#endif
#ifdef LOGTOREMOTE
	close();
	WSACleanup();//和WSAStartup必须配对使用
#endif
}
#ifdef LOGTOREMOTE
void Clog::close()
{
	
	#ifdef LINUX
		close(_fd);
	#else
		shutdown(sockfd ,SD_BOTH );
		closesocket(sockfd);
		sockfd = INVALID_SOCKET;
	#endif
	
}
#endif

void Clog::setloglevel(int loglevel)
{
	m_log_level=loglevel;
}

bool Clog::log(const char* msg,int loglevel)
{
#ifdef LOGLOG
	_set_se_translator(SeTranslator);
	try
	{
		#ifdef _DEBUG
		
		if (strlen(msg)<=510)
		{
			DEBUGOUT(msg );
		}
		
		#endif
	
		writelog(getExePath().c_str(),"log",msg);
		return true;

#ifdef LOGTOREMOTE
		if (!initedflag)
		{
			inicfg();
			if(!Connect()) 
			{		
				initedflag=false;
				writelog(getExePath().c_str(),"log",msg);
				return false;
			}
		}
		if (m_log_level<=loglevel)
		{	
			int len=strlen(msg);
			if (len>0)
			{ 
				if(SOCKET_ERROR==this->Send( msg ,len) )
				{
					writelog(getExePath().c_str(),"log",msg);
					initedflag=false;
					return false;
				}
			}
		}
#endif
	}
	catch(CSeException *e)
	{
		exceptiontolog(e);
		
		g_log.log("CClientlog::log except!",CRITICAL_LEVEL);
	}
#else
	DEBUGOUT(msg);
#endif

	return true;

}

#ifdef LOGTOREMOTE

bool Clog::Connect()
{
	_set_se_translator(SeTranslator);
	try
	{
		if (!initedflag)
		{
		#ifdef _DEBUG
			DEBUGOUT("Need init clientlog!\n");
		#endif
			writelog(getExePath().c_str(),"log","Need init clientlog!");
			return false;
		}
	

		
		struct sockaddr_in servaddr;

		memset(&servaddr, 0, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_addr.s_addr =inet_addr( m_ip );// htons( "127.0.0.1");
		servaddr.sin_port = htons( m_port );

		int ret = connect( sockfd , (struct sockaddr*)&servaddr , sizeof(servaddr) );
		
		if(ret ==-1 )
		{
			return false;
		}

	}
	catch(CSeException *e)
	{
		exceptiontolog(e);
		

	}
	
	return true;
}

bool Clog::SetRecvTimeOut(int t)
{
	int timeout = t; //ms
	int res = setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,sizeof(timeout));
	if(res == 0) return true;
	return false;
}

bool Clog::SetSendTimeOut(int t)
{
	int timeout = t; //ms
	int res = setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,sizeof(timeout));
	if(res == 0) return true;
	return false;
}

int  Clog::Send(const char *lp , int len )
{
	return send(sockfd, (char*)lp, len, 0);
}

int Clog::Recv(char*lp, int len)
{	
	int ret = recv(sockfd, (char*)lp , len, 0);
	if(ret ==  SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAETIMEDOUT) 
		{ 
				ret = 0 ;
		}	
	}
	return ret;
}
bool Clog::inicfg()
{
	string filepath;
	string path=getExePath();
	filepath=path;
	filepath.append(string(CFGFILE));

	
	memset(m_ip,0,sizeof(m_ip));
	GetPrivateProfileString("LOGSERVER","IP","127.0.0.1",m_ip,19,filepath.c_str());
	m_port = GetPrivateProfileInt("LOGSERVER","PORT",20000,filepath.c_str());

	initedflag = true;

	return true;
}

#endif