// ClientManager.cpp: implementation of the CClientManager class.
// 客户端管理类
// 1.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "client.h"
#include "Worker.h"
#include "ClientManager.h"
#include "client.h"

using namespace  std;

extern CFG g_cfg;
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
	LogExt(LOG_LOG_LEVEL, "[IMEI]:get %s",imei.c_str());

	const CLIENT_MAP::iterator it = clientqueue.find(imei);
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
	const CLIENT_MAP::iterator it = clientqueue.find(imei);
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
	EnterCriticalSection(&cs);
	activeList.remove(temp);
    idleList.push_back(temp);
	LeaveCriticalSection(&cs);
	temp->Close();
	
}

CLIENT_MAP* CClientManager::getClientMap()
{
	return &clientqueue;
}

void CClientManager::setworker(CWorker* p)
{
	mpworker = p;
}
