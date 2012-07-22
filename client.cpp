/******************************************************************************
** �ͻ����� 
** 1. ������յ�������
** 2. �ظ�
** 3. ����
**
** author�������� 2012.7
** 
******************************************************************************/

#include "stdafx.h"
#include "client.h"
#include "api.h"
#include "log.h"
#include "ClientManager.h"
#pragma warning (disable:4786)

extern  Clog g_log;

void ini(CCLient * client,int fd, sockaddr_in sinaddr)
{
	try
	{
		memset(client->imei,0,sizeof(client->imei));
		memset(&(client->IoData),0,sizeof(PER_IO_DATA ));
		client->offset =0;
		client->_fd =fd;
		

		int err;
		u_long data=1;
		/* attempt to set some bogus socket to non-blocking */
		
		err = ioctlsocket( fd, FIONBIO, &data );
		if( err != 0 )
		{
#ifdef _DEBUG
			OutputDebugString("ioctlsocket call succeeded without initializing winsock\n");
#endif
		}
	}
	catch(...)
	{
		g_log.log(TEXT("client new exception12!\n"),CRITICAL_LEVEL);
	}
	
}


CCLient::CCLient(SOCKET fd, struct sockaddr_in sinaddr, int timeout,CClientManager* cman)//:m_databuf(MAX_CMD_BUF_LEN)
{
	
	m_cman =cman;
	ini(this,fd,sinaddr);
	m_timeout = timeout;
	
	
}

void CCLient::ReInit(SOCKET fd, struct sockaddr_in sinaddr)
{
	ini(this,fd,sinaddr);
}

void CCLient::Close()
{
	shutdown(_fd ,2 );
	closesocket(_fd);
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

bool CCLient::parse(U8 *recvbuf,int ulen)
{
	
	int err = WSAGetLastError();
	if( ulen == -1 && err != WSAEWOULDBLOCK ) 
	{
		if( err != WSAECONNRESET )
		{
			g_log.log("peer reset the connection\n",DEBUG_ONLY_LEVEL);
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

#ifdef _DEBUG
		OutputDebugString("���յ�:");
		OutputDebugString((const char*)recvbuf);
		// cout << len << "�ֽ�" << endl;
#endif
			
		
		int i=0,j=0;
		//
		while (i<len)
		{
			if (('I'==p[i] || 'i'==p[i]) && ('M'==p[i+1] || 'm'==p[i+1])
				&& ('E'==p[i+2] || 'e'==p[i+2]) && ('I'==p[i+3] ||'i'==p[i+3]))
			{
				j =i+5; //j=> first #
				if (j + 15 > len)///��<1��imei 
				{						
					offset = len-i;
					memcpy(p,p+i,offset);
					p[offset]=0;
					break;
				}
				else  //enough one   //imei=############### 
				{						
					//get one;
					string imei;	
					imei.append((p+j),15);
					
					this->m_cman->AddToQueue(imei,this);
					i= j+16;
					j= i;
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
	g_log.log(data,LOG_LOG_LEVEL);
	
	return send(_fd, (char*)data, len, 0);
}