// Server.cpp: implementation of the CServer class.
// iterative server 迭代服务器  concurrent server并发服务器
// 监听类
// 1.监听客户端连接请求
// 2.把接收到的客户端连接给完成端口处理
// 3.创建完成端口I/O事件处理线程
// 4.
//
// author：张世光 2012.7
//////////////////////////////////////////////////////////////////////
#ifdef LINUX
#include <unp.h>
#include <unpthread.h>
#endif
#include "stdafx.h"

#include "ClientManager.h"

#include "Server.h"

#include <IOSTREAM>
using namespace std;

extern Clog	g_log;
extern CFG	g_cfg;

//////////////////////////////////////////////////////////////////////

static void CServer::run( LPVOID lpParam );
void CloseAllIOProcessThread(CServer *Server);
void ServerThread( LPVOID lpParam );
bool CreatProcessThread(CServer* Server);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CServer::CServer():port(65500),clients_max_count(100000),works_max_count(1)
{
	WSADATA   wsaData;   
	DWORD   Ret;   
	
	if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)   
	{   
		LogExt(DEBUG_ONLY_LEVEL,"WSAStartup error with codes: %d\n", WSAGetLastError());
	} 
}

void CServer::setPort(int p )
{
	port = p;
}

void CServer::setMaxClient(int max_clients)
{
	clients_max_count = max_clients;
}

void CServer::setMaxWorker(int max_work)
{
	works_max_count	= max_work;
}

CServer::~CServer()
{
#ifdef LINUX
	shutdown(_fd，SD_RDWR);
#else
	shutdown(_fd ,SD_BOTH );
	closesocket(_fd);
	WSACleanup();
#endif
}

void CServer::init(CFG * cfg,CClientManager* pcmanager)
{
	pClientManager = pcmanager;
	setPort( cfg->local_port);
	setMaxClient(cfg->max_clients_num);
}

bool CServer::Listen()
{
	_set_se_translator(SeTranslator);
	try
	{				
#ifdef LINUX
    #ifdef IPV6
		struct sockaddr_in6 sin;
	#else
		struct sockaddr_in sin;
	#endif	
		bzero(&sin,sizeof(sin));
		
		sin.sin_family = AF_INET; //AF_INET6
		sin.sin_addr.s_addr = htonl(INADDR_ANY);    
		sin.sin_port = htons(port);
		_fd = socket( AF_INET, SOCK_STREAM, 0 );
		
		int optval = 1;   
		setsockopt( _fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&optval, sizeof( sockaddr_in ) );
		
		if( bind( _fd, (struct sockaddr *)&sin, sizeof( sin ) ) == -1 ) 
		{
			LogExt("CServer::Listen() bind error\n");
			return false;
		}
#else
		
		
		
		if ((_fd =WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)   
		{ 
			LogExt(DEBUG_ONLY_LEVEL,"WSASocket() error with codes: %d\n", WSAGetLastError());  
		}
		//_fd = socket( AF_INET, SOCK_STREAM, 0 );
		int optval = 1;   
		setsockopt( _fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&optval, sizeof( sockaddr_in ) );
		
		int err;
		struct  sockaddr_in mySockaddr;
		mySockaddr.sin_family      = AF_INET;
		mySockaddr.sin_port        = htons(port);
		mySockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
		memset( &(mySockaddr.sin_zero), 0, 8);
		
		err = bind( _fd,(struct sockaddr *)&mySockaddr,sizeof(struct sockaddr) );
		if(err == SOCKET_ERROR)
		{
			LogExt(DEBUG_ONLY_LEVEL,"CServer::Listen() bind error\n");
			return false;
		}
#endif
		// listen, queue length 8  
		if( listen( _fd, 8 ) == -1 ) 
		{			
			LogExt(DEBUG_ONLY_LEVEL,"CServer::Listen() listen error\n");			
			return false;
		}
		LogExt(DEBUG_ONLY_LEVEL,"CServer::Listen %d ok\n",port);
		
	}
	catch(CSeException *e)
	{
		g_log.log("CServer::Listen except!\n",CRITICAL_LEVEL);
		exceptiontolog(e);
		setallthreadexitflag();
		
	}
	
	return true;
	
}

void CServer::start()
{
	if (INVALID_HANDLE_VALUE == mEvent)
	{
		creatwork(CServer::run);
	}
}

void CServer::stop()
{
	SetEvent(mEvent);
	WaitForSingleObject( hthread ,3000);
	CloseHandle(mEvent);
}

void CServer::run( LPVOID lpParam )
{
	_set_se_translator(SeTranslator);
	try
	{
		
		CServer *Server =(CServer*)lpParam;
		
		// 创建完成端口对象 
		HANDLE hIocp = ::CreateIoCompletionPort( INVALID_HANDLE_VALUE, 0, 0, 0 );
		if (NULL== hIocp)
		{
			throw exception( "[Ohmygod]");
		}
		Server->hiocp =hIocp;
		
		//
		if(!CreatProcessThread(Server))
		{
			throw exception( "[Ohmygod]");			
		}
		//
		DWORD  result =0;
		
		fd_set fdSet;
        
		struct timeval tv;
        
		// block for ?ms depends OS cpu  thread switch time          
		tv.tv_sec = 0;
		tv.tv_usec = 100000; //tv_usec则是微秒(10E-6 second)
		
		
		while(!allExitFlag && !stopServiceFlag) 
		{	
			if((allExitFlag) /*|| (result==WAIT_OBJECT_0) */)
			{
				//if (!stopServiceFlag)///非停止服务，而是内部原因出错，
				//{
				//	 ; //通知工作线程//或者在主线程退出时stop
				//}
				break ;
			}
			
			if( Server->pClientManager->CanGetNewClient() ) 
			{
				FD_ZERO( &fdSet );				//将指定的文件描述符集清空
				FD_SET( Server->_fd, &fdSet );	//在文件描述符集合中增加一个新的文件描述符
				//LogExt(DEBUG_ONLY_LEVEL,"select(0x%0x)\n",&fdSet);
				if( select( NULL, &fdSet, NULL, NULL, &tv ) == -1 ) 
				{
					Sleep( 100 );
					OutputDebugString("select -1\n");
				}
				else
				{
					
					if( FD_ISSET( Server->_fd, &fdSet ) ) //测试指定的文件描述符是否在该集合中
					{
						OutputDebugString(" FD_ISSET ok ");
						FD_CLR( Server->_fd, &fdSet );	//在文件描述符集合中删除一个文件描述符
						
						struct sockaddr_in adrFrom;
						
						int iAddrLen = sizeof( adrFrom );
						SOCKET sckClient;
						
						if( ( sckClient = accept( Server->_fd, (struct sockaddr *)&adrFrom, (int *)&iAddrLen ) ) == -1 ) 
						{
							OutputDebugString(" error ");
							//LogExt(DEBUG_ONLY_LEVEL,"accept error [%d]\n",sckClient);
						}
						else
						{
							OutputDebugString(" accept OK ");
							//LogExt(DEBUG_ONLY_LEVEL,"accept OK [%d]\n",sckClient);
							CCLient* client = Server->pClientManager->GetClient();
							if (!client)
							{
#ifdef _DEBUG
								LogExt(DEBUG_ONLY_LEVEL,"clients comesnew\n");
#endif
								client = new CCLient( sckClient, adrFrom, 0, Server->pClientManager);
								if (client)
								{
									Server->pClientManager->PushNewIn( client );
								}
								else
								{
									LogExt(CRITICAL_LEVEL,"clients new exception\n");
								}								
							}
							else
							{
#ifdef _DEBUG
								LogExt(DEBUG_ONLY_LEVEL,"clients comes newreuse\n");
#endif
								client->ReInit(sckClient, adrFrom );						
								
							}
							if (client)
							{
								//把sock绑定到完成端口//client* 用作key
								::CreateIoCompletionPort( ( HANDLE)sckClient, hIocp, (DWORD)client, 0 );
								client->IoData.nOperationType = OP_READ; 
								
								WSABUF buf; 
								
								client->resetbuf(&buf);
								
								DWORD dwRecv = 0; 
								DWORD dwFlags = 0;
								//This function receives data from a connected socket
								if (::WSARecv( sckClient, &buf, 1, &dwRecv, &dwFlags, &(client->IoData.ol), NULL )== -1)
								{
									if (WSAGetLastError() != ERROR_IO_PENDING)
									{	
										g_log.log("WSARecv Return ERROR_IO_PENDING Error!\n",CRITICAL_LEVEL);
										//setallthreadexitflag();
									}
								}
							}
						}
					}
					else
					{
						//DEBUGOUT(" FD_ISSET none\n ");
					}
				}//else
				
			}
			else
			{				
				LogExt(LOG_LOG_LEVEL,"[log]达到客户端接入数[%d]的最大限制[%d]",Server->pClientManager->GetActiveSize(),Server->clients_max_count);
			}
			
		}
		CloseAllIOProcessThread(Server );
		
		
	}
	catch(CSeException *e)
	{
		exceptiontolog(e);
		setallthreadexitflag();
		g_log.log("ServerMainThread::tcpbegin exception!\n",CRITICAL_LEVEL);
	}
#ifdef _DEBUG
	LogExt(WARNNING_LEVEL,"ServerMainThread::tcpbegin Thread exit ID[0x%0x]\n",GetCurrentThreadId());
#endif
}


//关闭所有IO线程。
void CloseAllIOProcessThread(CServer *Server)
{
	for (int i = 0; i < Server->works_max_count; ++i)
	{
		PostQueuedCompletionStatus(Server->hiocp, 0, 0, (OVERLAPPED*) (/*(__int64)*/ -1) );
    }
}


/****************************************************************** 
* 函数介绍：处理完成端口对象事件的线程 ；解析处理接收到的数据
* 输入参数： 
* 输出参数： 
* 返回值 ： 
*******************************************************************/ 
void ServerThread( LPVOID lpParam ) 
{ 
	CServer* Server=(CServer*)lpParam;	 
	HANDLE hIocp = Server->hiocp; 
    if( hIocp == NULL ) 
    { 
        return ; 
    }
	OutputDebugString( "ServerThread");//
	
    DWORD dwTrans = 0; 
    CCLient* lpCompletionKey; 
    PPER_IO_DATA     pPerIo; 
	
    while( TRUE ) 
    { 
        // 在关联到此完成端口的所有套接字上等待I/O完成 
        BOOL bRet = ::GetQueuedCompletionStatus( Server->hiocp, &dwTrans, (LPDWORD)&lpCompletionKey, (LPOVERLAPPED*)&pPerIo, WSA_INFINITE ); 
        if( !bRet )     
        { 
            lpCompletionKey->m_cman->KillClient(lpCompletionKey);
            //OutputDebugString( "error" ); 
            continue; 
        }
		//cout << "dwTrans" << dwTrans<< " pPerIo->nOperationType="<<pPerIo->nOperationType <<endl; 
        // 套接字被对方关闭 
        if( dwTrans == 0 && ( pPerIo->nOperationType == OP_READ || pPerIo->nOperationType == OP_WRITE ) ) 
        { 
            lpCompletionKey->m_cman->KillClient(lpCompletionKey);
			
            OutputDebugString( "client closed." ); 
            continue; 
        }
		
        switch ( pPerIo->nOperationType ) 
        { 
        case OP_READ:       
            { 				
				lpCompletionKey->parse((U8*)(lpCompletionKey->IoData.buf) ,dwTrans);
				
                // 继续投递接受操作 
                WSABUF buf; 
                
				lpCompletionKey->resetbuf(&buf);
                lpCompletionKey->IoData.nOperationType = OP_READ; 
				
                DWORD dwRecv = 0; 
                DWORD dwFlags = 0; 
				
               	if (::WSARecv( lpCompletionKey->_fd, &buf, 1, &dwRecv, &dwFlags, &(lpCompletionKey->IoData.ol), NULL )== -1)
				{
					if (WSAGetLastError() != ERROR_IO_PENDING)
					{	
						g_log.log("WSARecv Return ERROR_IO_PENDING Error!\n",CRITICAL_LEVEL);
						//setallthreadexitflag();
					}
				}
            } 
            break; 
        case OP_WRITE: 
        case OP_ACCEPT: 
            break;
			
        }
		
    }
	
    return ; 
}

//创建工作线程（其解析处理接收到的数据）
bool CreatProcessThread(CServer* Server)
{
	_set_se_translator(SeTranslator);
	try
	{
		HANDLE h =NULL;
		
		for(int i = 0; i <Server->works_max_count; ++i)
		{
			if( NULL != (h =(HANDLE) ::_beginthread(ServerThread, 0, (LPVOID)Server)))
			{
				Server->threadset.push_back( h );
			}
			else
			{			
				g_log.log("create works fail\n",ERROR_LEVEL);		 		
				break;
			}		 
		}
		
		
		if( NULL == h) 
		{
			allExitFlag =true;
			CloseAllIOProcessThread(Server);
			
			return false;
		}
		else
		{
			return true;
		}
	}
	catch(CSeException *e)
	{
		exceptiontolog(e);
		setallthreadexitflag();
		g_log.log("CreatProcessThread exception!\n",CRITICAL_LEVEL);
	}
	return false;
}