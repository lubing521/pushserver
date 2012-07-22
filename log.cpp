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
	
	_set_se_translator(SeTranslator);
	try
	{
		va_list args;
		va_start(args, lpszFormat);

		int nBuf;
		TCHAR szBuffer[512];
		nBuf = _vsntprintf(szBuffer, 512, lpszFormat, args);

		va_end(args);
		
		OutputDebugString(szBuffer);

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
		g_log.log("LogExt exception!",CRITICAL_LEVEL);
		exceptiontolog(e);		
		
	}

}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Clog::Clog():m_log_level(DEBUG_ONLY_LEVEL),initedflag(false),m_port(0)
{
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
}

Clog::~Clog()
{
	close();
	WSACleanup();//和WSAStartup必须配对使用
}
void Clog::close()
{
#ifdef LINUX
    close(_fd);
#else
	shutdown(sockfd ,SD_BOTH );
	closesocket(sockfd);
	
#endif
}

void Clog::setloglevel(int loglevel)
{
	m_log_level=loglevel;
}
bool Clog::log(const char* msg,int loglevel)
{

	_set_se_translator(SeTranslator);
	try
	{
		_set_se_translator(SeTranslator);
		try
		{
 		#ifdef _DEBUG
 			OutputDebugString(msg );
 		#endif
		}
		catch(CSeException *e)
		{
			exceptiontolog(e);
		}
		//return true;
		//writelog(getExePath().c_str(),"log",msg);
		//return true;

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
	}
	catch(CSeException *e)
	{
		exceptiontolog(e);
		
		g_log.log("CClientlog::log except!",CRITICAL_LEVEL);
	}

	return true;

}
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
		
// 		g_log.log("Clog::Connect except!",CRITICAL_LEVEL);
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