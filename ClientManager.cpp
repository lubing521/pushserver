// ClientManager.cpp: implementation of the CClientManager class.
// 客户端管理类
// 1.每2秒去遍历一边是否有超时的“僵尸”连接
// 2.添加新的连接到队列
// 3.删除需要关闭的连接
// 4.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "client.h"
#include "Worker.h"
#include "ClientManager.h"
 

using namespace  std;

extern CFG g_cfg;

static void CClientManager::run( LPVOID lpParam );
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClientManager::CClientManager()
{
	InitializeCriticalSection(&cs);
}

CClientManager::~CClientManager()
{

	clientqueue.clear();  
	for( std::list<CCLient *> :: iterator i = idleList.begin();  i != idleList.end(); ++i )
    {
		delete *i;   
	} 
    idleList.clear();  
	for( std::list<CCLient *> :: iterator j = activeList.begin();  j != activeList.end(); ++j )
    {
		delete *j;  
	}  
    activeList.clear();  
	DeleteCriticalSection(&cs);
	
}
//when get imei ,add to map.
void CClientManager::AddToQueue(string imei, CCLient* pclient)
{	
	LogExt(LOG_LOG_LEVEL, "[IMEI]:get %s\t",imei.c_str());
	strncpy(pclient->imei,imei.c_str(),IMEI_LEN);
	CLIENT_MAP::iterator it = clientqueue.find(imei);
	if (it != clientqueue.end())
	{
		it->second = pclient;
	}
	else
	{
		clientqueue.insert(pair<string,CCLient*>(imei,pclient));
	}
	
	this->mpworker->ckSetEvent();
}

//
void CClientManager::DeleteFromQueue(string imei)
{	
	CLIENT_MAP::iterator it = clientqueue.find(imei);
	if (it != clientqueue.end())
	{
		it->second = NULL;	
	}
}

long CClientManager::GetActiveSize()
{
	return activeList.size();
}

bool CClientManager::CanGetNewClient()
{
	if (activeList.size() < g_cfg.max_clients_num)
	{
		return true;
	}
	else
	{
		return false;
	}
}

CCLient* CClientManager::GetClient()
{
	CCLient * temp= NULL;
	if( !idleList.empty() )
	{
        EnterCriticalSection(&cs);
		temp = idleList.front();
		idleList.pop_front();
        activeList.push_back(temp);
		LeaveCriticalSection(&cs);
	}
	return temp;
}

void CClientManager::PushNewIn(CCLient * temp)
{

	EnterCriticalSection(&cs);
	activeList.push_back(temp);
	LeaveCriticalSection(&cs);

}
//连接被关闭或出错调用 //
void CClientManager::KillClient(CCLient * temp)
{
	if(temp==NULL) return;
	
	if (strlen(temp->imei)>0)
	{
		DeleteFromQueue(temp->imei);
	}
	memset(temp->imei,0,sizeof(temp->imei));
	temp->Close();

	EnterCriticalSection(&cs);
	activeList.remove(temp);
    idleList.push_back(temp);
	LeaveCriticalSection(&cs);
	
	
}

CLIENT_MAP* CClientManager::getClientMap()
{
	return &clientqueue;
}

void CClientManager::setworker(CWorker* p)
{
	mpworker = p;
}

void CClientManager::start()
{
	if (INVALID_HANDLE_VALUE == this->mEvent)
	{
		this->creatwork( CClientManager::run );
	}
}

void CClientManager::stop()
{	
	SetEvent(this->mEvent);
	WaitForSingleObject( this->hthread ,3000);
	CloseHandle(this->mEvent);
}

void CClientManager::killTimeoutClient()
{
	EnterCriticalSection(&cs);
	CLIENT_MAP::iterator it = clientqueue.begin();
	
	int ret=0;
	DWORD op;
	int oplen =sizeof(DWORD);

	while (it != clientqueue.end())
	{

		if(it->second && 0== strlen(it->second->imei) /*&& t - it->second->createtime > g_cfg.outtime*/ )
		{		
			ret = getsockopt(it->second->_fd,SOL_SOCKET,SO_CONNECT_TIME,(char*)&op,&oplen);
			if (0==ret)
			{
				if (op > 2 )  //秒
				{
					activeList.remove(it->second);
					idleList.push_back(it->second);
					it->second = NULL;
					DEBUGOUT("[log]remove socket\n");

				}
			}
			
		}
		++it;
	}	
	LeaveCriticalSection(&cs);
}

void CClientManager::run( LPVOID lpParam )
{
	DWORD dwResult = 0 ;
	CClientManager* p = (CClientManager*) lpParam ;

	while(!allExitFlag )
	{
		dwResult = WaitForSingleObject(p->mEvent, 2000);
		if (!allExitFlag )
		{
			if(WAIT_OBJECT_0 == dwResult)
			{				
				CloseHandle(p->mEvent);
				break;
			}
			else 
			{
				p->killTimeoutClient();	
			}			
		}
		else
		{
			CloseHandle(p->mEvent);
			break;
		}
	}
}