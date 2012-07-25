// Server.cpp: implementation of the CServer class.
// ������
// 1.�����ͻ�����������
// 2.�ѽ��յ��Ŀͻ������Ӹ���ɶ˿ڴ���
// 3.������ɶ˿�I/O�¼������߳�
// 4.����ֻ���Ӳ�����GET����Ľ�ʬ����===�ܾ����񹥻�
//
// author�������� 2012.7
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WinError.h"
#include "ClientManager.h"
#include "Loader.h"
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
CServer::CServer():port(8080),clients_max_count(100000),works_max_count(1)
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
	stop();
	shutdown(_fd ,SD_BOTH );
	closesocket(_fd);
	
	CloseHandle(this->hiocp);
	
	WSACleanup();
}

void CServer::init(CFG * cfg,CClientManager* pcmanager,CLoader * pL)
{
	pClientManager = pcmanager;
	pLoader        = pL;
	setPort( cfg->local_port);
	setMaxClient(cfg->max_clients_num);
}

bool CServer::Listen()
{
	_set_se_translator(SeTranslator);
	try
	{				
#ifdef LINUX
		struct sockaddr_in sin;
		
		memset( &sin, 0, sizeof( sin ) );
		
		sin.sin_family = AF_INET;
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
	SetEvent(this->mEvent);
	WaitForSingleObject( this->hthread ,3000);
	CloseHandle(this->mEvent);
	
}

void CServer::run( LPVOID lpParam )
{
	CServer *Server =(CServer*)lpParam;
	
	_set_se_translator(SeTranslator);
	try
	{		
		
		// ������ɶ˿ڶ��� 
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
		
		// 		fd_set fdServer;
        
		// 		struct timeval tv;
		//         
		// 		// block for ?ms depends OS cpu  thread switch time          
		// 		tv.tv_sec = 0;
		// 		tv.tv_usec = 100000; //tv_usec����΢��(10E-6 second)
		
		char debuginfo[255]={0};
		
		while(!allExitFlag ) 
		{	
			
			
			if( Server->pClientManager->CanGetNewClient() ) 
			{
				// 				FD_ZERO( &fdServer );				//��ָ�����ļ������������
				// 				FD_SET( Server->_fd, &fdServer );	//���ļ�����������������һ���µ��ļ�������
				// 				
				// 				if( select( NULL, &fdServer, NULL, NULL, &tv ) == -1 ) 
				// 				{
				// 					Sleep( 100 );
				// 					DEBUGOUT("select -1\n");
				// 				}
				// 				else
				// 				{
				// 					
				// 					if( FD_ISSET( Server->_fd, &fdServer ) ) //����ָ�����ļ��������Ƿ��ڸü�����
				// 					{
				// 						DEBUGOUT(" FD_ISSET ok ");
				// 						FD_CLR( Server->_fd, &fdServer );	//���ļ�������������ɾ��һ���ļ�������
				
				struct sockaddr_in adrFrom;
				
				int iAddrLen = sizeof( adrFrom );
				SOCKET sckClient;
				
				if( ( sckClient = accept( Server->_fd, (struct sockaddr *)&adrFrom, (int *)&iAddrLen ) ) == -1 ) 
				{
					g_log.log("[err]accept error \n",LOG_LOG_LEVEL);					
					
				}
				else
				{						
					
					CCLient* client = Server->pClientManager->GetClient();
					if (!client)
					{
						
						//DEBUGOUT("clients comesnew\n");
						
						client = new CCLient( sckClient, adrFrom, Server->pClientManager);
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
						
						client->ReInit(sckClient, adrFrom );						
						
					}
					if (client)
					{
						//��sock�󶨵���ɶ˿�//client* ����key
						::CreateIoCompletionPort( ( HANDLE)sckClient, hIocp, (DWORD)client, 0 );
						client->IoData.nOperationType = OP_READ; 
						
						WSABUF buf; 
						
						client->resetbuf(&buf);
						
						DWORD dwRecv = 0; 
						DWORD dwFlags = 0;
						//This function receives data from a connected socket
						if (::WSARecv( sckClient, &buf, 1, &dwRecv, &dwFlags, &(client->IoData.ol), NULL )== -1)
						{
							int err =WSAGetLastError();
							if ( err != ERROR_IO_PENDING)
							{								
								//DEBUGOUT("[Error][CServer::run]WSARecv Return !ERROR_IO_PENDING Error!\n");
								Server->pClientManager->KillClient(client);
								
							}
							else
							{
#ifdef DEBUG
								memset(debuginfo,0,sizeof(debuginfo));
								sprintf(debuginfo,"[warnning][WSARecv][%d]\n",err);
								DEBUGOUT(debuginfo);
#endif
							}
						}
					}
				}
				// 					}
				// 					else
				// 					{
				// 						DEBUGOUT(" FD_ISSET none\n ");
				// 						
				// 					}
				// 				}//else
				
			}
			else
			{				
				LogExt(LOG_LOG_LEVEL,"[log]�ﵽ�ͻ��˽�����[%d]���������[%d]",Server->pClientManager->GetActiveSize(),Server->clients_max_count);
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
	
	if((allExitFlag))
	{
		Server->pLoader->ckSetEvent();		
	}
	
#ifdef _DEBUG
	LogExt(WARNNING_LEVEL,"ServerMainThread::tcpbegin Thread exit ID[0x%0x]\n",GetCurrentThreadId());
#endif
}


void CloseAllIOProcessThread(CServer *Server)
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	for (int i = 0; i <sysInfo.dwNumberOfProcessors ; ++i)//Server->works_max_count
	{
		PostQueuedCompletionStatus(Server->hiocp, 0, 0, (OVERLAPPED*) (/*(__int64)*/ -1) );
    }
}


/****************************************************************** 
* �������ܣ�������ɶ˿ڶ����¼����߳� ������������յ�������
* ���������//  
*******************************************************************/ 
void ServerThread( LPVOID lpParam ) 
{ 
	CServer* Server=(CServer*)lpParam;	 
	HANDLE hIocp = Server->hiocp; 
    if( hIocp == NULL ) 
    { 
        return ; 
    }

	char outstr[200];

	try
	{
			
		DWORD dwTrans = 0; 
		DWORD dwErr =0;
		CCLient* lpCompletionKey=NULL; 
		PPER_IO_DATA     pPerIo=NULL; 
		
		while( !allExitFlag ) 
		{ 
			lpCompletionKey = NULL; 
			pPerIo          = NULL;
			// �ڹ���������ɶ˿ڵ������׽����ϵȴ�I/O��� 
			BOOL bRet = ::GetQueuedCompletionStatus( Server->hiocp, &dwTrans, (LPDWORD)&lpCompletionKey, (LPOVERLAPPED*)&pPerIo, WSA_INFINITE ); 
			dwErr = GetLastError();
#ifdef DEBUG
			memset(outstr,0,sizeof(outstr));
			sprintf(outstr,"[GetQueuedCompletionStatus][dwErr%d][key%x][pio%x][ret%d]\n",dwErr,lpCompletionKey,pPerIo,bRet);
			DEBUGOUT( outstr ); 
#endif
			
			// 		if( 10053 ==dwErr || 10054 ==dwErr )  //WSAECONNRESET (10054): Connection reset by peer.// 10053 //- remote closed the connect
			// 		{
			// 				if (pPerIo && lpCompletionKey)
			// 				{
			// 					lpCompletionKey->m_cman->KillClient(lpCompletionKey);
			// 				}
			// 				continue;
			// 		}
			// 		else if(995 ==dwErr ) //�Ѿ�����I/O//WSA_OPERATION_ABORTED (995): Overlapped operation aborted.
			// 		{
			// 
			// 		}
			// 		else if(997 ==dwErr) //ERROR_IO_PENDING
			// 		{
			// 		}
			// 		else if (64 ==dwErr)//ERROR_NETNAME_DELETED
			// 		{
			// 		}
			// 		else if(10038 == dwErr)//WSAENOTSOCK (10038): Socket operation on nonsocket. closed.��Ҫ��Ͷ��
			// 		{
			// 		}
			// 		else if( 10061== dwErr)//WSAECONNREFUSED (10061): Connection refused.
			// 		{
			// 		}
			// 		else if( 10055 == dwErr) //WSAENOBUFS (10055): No buffer space available.//Ͷ��̫�ദ�����������
			// 			{
			// 			
			// 			}
			// 		else if( 10058 == dwErr)// - ������ǰ�Ĺرյ��ã��׽������Ǹ������Ѿ��رգ����ͻ�������ݵ�����û�б�����
			// 			{
			// 
			// 			}
			// 		else if( 183 == dwErr) ///ERROR_ALREADY_EXISTS
			// 			{
			// 
			// 			}
			// 		else if( 735 == dwErr)/* ERROR_ABANDONED_WAIT_0  */
			// 		{
			// 
			// 		}
			// 		else if (1450 == dwErr)// 1450 - ϵͳ��Դ���㣬�޷��������ķ���
			// 		{
			// 
			// 		}
			
			
			if( !bRet )     
			{ 			
				if (pPerIo && lpCompletionKey)
				{
					lpCompletionKey->m_cman->KillClient(lpCompletionKey);
				}
				continue;
			}
			else
			{
				// �׽��ֱ��Է��ر� 
				if( 0 == dwTrans  && ( OP_READ == pPerIo->nOperationType || OP_WRITE == pPerIo->nOperationType ) ) 
				{ 
					if (lpCompletionKey)
					{	
						LogExt(LOG_LOG_LEVEL,"�ն�%s�Ͽ�����\n",lpCompletionKey->imei);
						lpCompletionKey->m_cman->KillClient(lpCompletionKey);
					}
				
					continue; 
				}
				
				switch ( pPerIo->nOperationType ) 
				{ 
				case OP_READ:       
					{ 				
						lpCompletionKey->parse((U8*)(lpCompletionKey->IoData.buf) ,dwTrans);
						
						// ����Ͷ�ݽ��ղ��� �������Ѿ��ر�
						WSABUF buf; 
						
						lpCompletionKey->resetbuf(&buf);
						lpCompletionKey->IoData.nOperationType = OP_READ; 
						
						DWORD dwRecv = 0; 
						DWORD dwFlags = 0; 
						
						if (::WSARecv( lpCompletionKey->_fd, &buf, 1, &dwRecv, &dwFlags, &(lpCompletionKey->IoData.ol), NULL )== -1)
						{
							int err =WSAGetLastError();
#ifdef DEBUG
							memset(outstr,0,sizeof(outstr));
							sprintf(outstr,"[log][WSARecv][%d][fd%d][dwRecv%d][dwFlags%d]\n",err,lpCompletionKey->_fd,dwRecv,dwFlags);
							DEBUGOUT(outstr);
#endif					
							if ( err != ERROR_IO_PENDING)
							{	
								DEBUGOUT("[Error]WSARecv Return ERROR_IO_PENDING Error!\n");
								lpCompletionKey->m_cman->KillClient(lpCompletionKey);
								
							}
							else
							{//997 ERROR_IO_PENDING								
							}
						}
					} 
					break; 
				case OP_WRITE: 
				case OP_ACCEPT: 
					break;					
				}
			}
		}
	
	}
	catch(...)
	{
		if(!allExitFlag)
        {
             
            g_log.log("ServerThread:�����쳣��1����Զ����¿�ʼ\n",ERROR_LEVEL);
            Sleep(1000);
            HANDLE hwnd=NULL;
            unsigned int tid=0;
			for (int i=0;i<Server->threadset.size();++i)
			{
				if ( GetCurrentThread() == Server->threadset[i])
				{
					Server->threadset.erase(Server->threadset.begin() + i);
				}
			}			     
            
            HANDLE h=(HANDLE)_beginthread(ServerThread,0,(LPVOID)Server);
            if (NULL!=h)
            {
				Server->threadset.push_back( h );
            }
			else
			{			
				g_log.log("create works fail\n",ERROR_LEVEL);		 					
			}
        }        	
	}
	
    return ; 
}

//���������߳�
bool CreatProcessThread(CServer* Server)
{
	_set_se_translator(SeTranslator);
	try
	{
		HANDLE h =NULL;
		SYSTEM_INFO sysInfo;
		GetSystemInfo(&sysInfo);
		for(int i = 0; i <sysInfo.dwNumberOfProcessors; ++i) //Server->works_max_count
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