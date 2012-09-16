// ClientManager.cpp: implementation of the CClientManager class.
// 客户端管理类
// 1.每2秒去遍历一边是否有超时的“僵尸”连接
// 2.添加新的连接到队列
// 3.删除需要关闭的连接
// 4.
//////////////////////////////////////////////////////////////////////
///log format:[type][class]info\n
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "client.h"
#include "Worker.h"
#include "ClientManager.h"
#include "api.h" 

using namespace  std;

extern CFG g_cfg;

static void CClientManager::run( LPVOID lpParam );
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClientManager::CClientManager()
{
	InitializeCriticalSection(&cs);
	InitializeCriticalSection(&queue_cs);
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
	DeleteCriticalSection(&queue_cs);
	
}
//when get imei ,add to map.
void CClientManager::AddToQueue(string imei, CCLient* pclient)
{	
	LogExt(LOG_LOG_LEVEL, "[log][CClientManager]get %s\n",imei.c_str());

	strncpy(pclient->imei,imei.c_str(),IMEI_LEN);

	{//auto lock block
		CAutoLock Lock(&queue_cs);
	
		CLIENT_MAP::iterator it = clientqueue.find(imei);
		if (it != clientqueue.end())
		{
			if(it->second)
			{
				KillClient(it->second);
			}
			it->second = pclient;
		}
		else
		{
			clientqueue.insert(pair<string,CCLient*>(imei,pclient));
		}
	
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

	_set_se_translator(SeTranslator);
	try
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
	catch(CSeException *e)
	{
		exceptiontolog(e);
#ifdef _DEBUG
		printexception(DEBUGARGS);
#endif
		setallthreadexitflag();
		g_log.log("[exception][CClientManager]CanGetNewClient!\n",CRITICAL_LEVEL);
	}
	
	return false;

}

CCLient* CClientManager::GetClient()
{
	CCLient * temp= NULL;
	
	{
		CAutoLock Lock(&cs);
		if( !idleList.empty() )
		{        
			temp = idleList.front();
			idleList.pop_front();
			activeList.push_back(temp);		
		}		
	}
	return temp;
}

void CClientManager::PushNewIn(CCLient * temp)
{

	{
		CAutoLock Lock(&cs);
		activeList.push_back(temp);
	}

}
//连接被关闭或出错调用 //
void CClientManager::KillClient(CCLient * temp)
{

	
	_set_se_translator(SeTranslator);
	try
	{

		if(temp==NULL) return;

#if defined(_DEBUG)
// 		char debuginfo[200]={0};		
//  		sprintf(debuginfo,"[log][CClientManager]KillClient(%s,%d)\n",temp->imei,temp->_fd);
//  		DEBUGOUT(debuginfo); 

		LogExt(DEBUG_ONLY_LEVEL,"[log][CClientManager]KillClient(%x,%s,%d)\n",temp,temp->imei,temp->_fd);
#endif
		if (strlen(temp->imei)>0)
		{
			DeleteFromQueue(temp->imei);
		}
		memset(temp->imei,0,sizeof(temp->imei));
		temp->Close();

		{
			CAutoLock Lock(&cs);

			
			std::list<CCLient *>::reverse_iterator rit = idleList.rbegin() ;
			while(rit != idleList.rend())
			{
				if (*rit != temp)
				{
					++rit;
				}
				else
				{
					break;
				}
			}
			if (rit == idleList.rend())
			{
				idleList.push_back(temp);
			}		
			activeList.remove(temp);
		}
	}
	catch(CSeException *e)
	{		
		exceptiontolog(e);
#ifdef _DEBUG
		printexception(DEBUGARGS);
#endif
		setallthreadexitflag();
		g_log.log("[exception][CClientManager]KillClient!\n",CRITICAL_LEVEL);
	}
	
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
	writelogimmediatly("[log][CClientManager]start.\n");
}

void CClientManager::stop()
{	
	if (INVALID_HANDLE_VALUE != mEvent)
	{
		SetEvent(this->mEvent);
		WaitForSingleObject( this->hthread ,3000);
		CloseHandle(this->mEvent);
		mEvent = INVALID_HANDLE_VALUE;

		writelogimmediatly("[log][CClientManager]stop.\n");
	}
}

void CClientManager::killTimeoutClient()
{

	CAutoLock Lock(&cs);

	CLIENT_MAP::iterator it = clientqueue.begin();
	
	int ret=0;
	DWORD op;
	int oplen =sizeof(DWORD);

	while (it != clientqueue.end())
	{
		
		if(it->second && 0 == strlen(it->second->imei) )
		{	
			
			ret = getsockopt(it->second->_fd,SOL_SOCKET,SO_CONNECT_TIME,reinterpret_cast<char*>(&op),&oplen);
			if (0==ret)
			{
				if (op > g_cfg.outtime || (time(NULL) - it->second->delay_time > g_cfg.outtime) )  //秒
				{
		#ifdef _DEBUG
					DEBUGOUT("[log][CClientManager]remove socket\n");
					LogExt(DEBUG_ONLY_LEVEL,"[log][CClientManager]remove socket[%s]>%d\n",it->second->imei,g_cfg.outtime);
		#endif
					
					idleList.push_back(it->second);
					activeList.remove(it->second);
					it->second = NULL;
				}
			}
		}
		++it;
	}	
	
}

void CClientManager::run( LPVOID lpParam )
{
	DWORD dwResult = 0 ;
	CClientManager* p = static_cast <CClientManager*>(lpParam) ;

	while(!allExitFlag )
	{
		dwResult = WaitForSingleObject(p->mEvent, 20000);//每20秒过滤一遍僵尸连接(100*20<=2000)
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