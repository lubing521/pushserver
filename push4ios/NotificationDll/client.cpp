/******************************************************************************
** 客户端类 
** 1. 处理接收到的数据
** 2. 回复
** 3. 重用
**
** author：张世光 2012.7
**  87895224@QQ.com
******************************************************************************/

#include "stdafx.h"
#include "client.h"
#include "api.h"
#include "log.h"
#include "ClientManager.h"
#pragma warning (disable:4786)
#pragma warning (disable:4089)
extern  Clog g_log;
extern  CFG g_cfg;

void ini(CCLient * client,int fd, sockaddr_in sinaddr)
{
	try
	{
		memset(&(client->IoData),0,sizeof(PER_IO_DATA ));
		client->offset =0;
		client->_fd =fd;

		int err;
		u_long data=1;
		/* attempt to set some bogus socket to non-blocking */
		
		err = ioctlsocket( fd, FIONBIO, &data );
		if( err != 0 )
		{
			writelogimmediatly("[error][ini]ioctlsocket call succeeded without initializing winsock\n");
		}
	}
	catch(...)
	{
		g_log.log(TEXT("[exception][ini]!\n"),CRITICAL_LEVEL);
	}
	
}


CCLient::CCLient(SOCKET fd, struct sockaddr_in sinaddr,CClientManager* cman)
{
	m_cman =cman;
	ini(this,fd,sinaddr);
	
}

void CCLient::ReInit(SOCKET fd, struct sockaddr_in sinaddr)
{
	ini(this,fd,sinaddr);
}

void CCLient::Close()
{
	shutdown(_fd ,SD_BOTH );
	closesocket(_fd);
	_fd = INVALID_SOCKET;
}

CCLient::~CCLient()
{
	Close();
}

void CCLient::resetbuf(WSABUF * buf)
{
	buf->buf = IoData.buf+offset; 
    buf->len = PER_IO_BUFFER_SIZE - offset; 
}
//
//http://www.domain.com/api.php?TK=[64ascii]\r\n
//

bool CCLient::parse(unsigned char *recvbuf,int ulen)
{
	
	int err = WSAGetLastError();
	if( ulen == -1 && err != WSAEWOULDBLOCK ) 
	{
		if( err != WSAECONNRESET )
		{
			g_log.log("[log][CCLient]parse.peer reset the connection\n",DEBUG_ONLY_LEVEL);
		}
		
	}
	else if( ulen == 0 ) 
	{
		
	}
	else if( ulen > 0 )
	{
		int len= ulen+offset;
		
		recvbuf[len] =0;
		char *p= (char *) recvbuf;


		int i=0,j=0;
		//
		while (i<len)
		{
			if (('T'==p[i] || 't'==p[i]) && ('o'==p[i+1] || 'O'==p[i+1])
				&& ('K'==p[i+2] || 'k'==p[i+2])&& ('e'==p[i+3] || 'E'==p[i+3])
				&& ('N'==p[i+4] || 'n'==p[i+4]))
			{
				j =i+6; //j=> first #
				if (j + DEVICETOKEN_LEN > len)///有<1个devicetoken 
				{						
					offset = len-i;
					memcpy(p,p+i,offset);
					p[offset]=0;
					break;
				}
				else  //enough one   //tk=[64*[char]] 
				{						
					//get one;
					string token("");	
					token.append((p+j),DEVICETOKEN_LEN);
					
					this->m_cman->AddToQueue(token);
					
					sendback("{\"code\":\"1\"}",strlen("{\"code\":\"1\"}"));
					break;
				}
				
			}
			else
			{
				++i;				
			}
		}//while
		
	}
	
	return true;
}

int CCLient::sendback( const char* data,int len)
{
	try
	{
		char temp[8]={0};
		int ret = send(_fd, (char*)data, len, 0);

		string log("[log][CCLient]toIOS[");
		//log.append(this->imei);
		log.append("[ret");
		log.append(itoa(ret,temp ,10));
		log.append("]");
		log.append(data);
		g_log.log(log.c_str(),LOG_LOG_LEVEL);
	
		return ret;
	}
	catch(...)
	{	
	}
	return 0;
}