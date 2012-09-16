/*******************************************************************
 **CClient类维护一个socket
// File:   client.h
// Author: root  , zsg
//
// Created on February 19, 2008, 9:36 AM
// Edit on 2011-07-01
********************************************************************/

#ifndef _CLIENT_H
#define	_CLIENT_H

#ifdef LINUX

#include <sys/socket.h>
#include <sys/errno.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#endif

//#include <winsock2.h>
#include <stdio.h>
#include <string>
/*#include <hash_set>*/
#include <iostream>
#include <time.h>
#include "api.h"




using namespace std;
#define MAXBUF (1024*24) 
#define U8 unsigned char

class CClientManager;
class CCLient
{
public:
    enum {BUFFERSIZE = 24*1024};
    CCLient(SOCKET fd, struct sockaddr_in sinaddr, CClientManager* cman);
    ~CCLient();

	void ReInit(SOCKET fd, struct sockaddr_in sinaddr);
	void Close();

	int sendback( const char* data,int len);
	bool parse(U8 *recvbuf,int ulen);
	void resetbuf(WSABUF * buf);


	SOCKET _fd;

	int offset;			///buffer offset
	char imei[IMEI_LEN+1];

	PER_IO_DATA   IoData;        
    
	CClientManager* m_cman; 
	
	time_t delay_time;//delay for kill
	
private:
	sockaddr_in m_sinaddr;
    U8 *recvbuf;
	
	
 
	

};


#endif	/* _CLIENT_H */

