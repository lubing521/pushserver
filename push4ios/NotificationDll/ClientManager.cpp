// ClientManager.cpp: implementation of the CClientManager class.
// 客户端管理类
// 1.每20秒去遍历一边是否有超时的“僵尸”连接
// 2.添加新的连接到队列
// 3.删除需要关闭的连接
// 4.
// author：张世光 87895224@QQ.com
//////////////////////////////////////////////////////////////////////
///log format:[type][class]info\n
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "client.h"

#include "Worker.h"

#include "ClientManager.h"

#include "api.h" 
#include "Server.h"
#include "Loader.h"
#include "Manager.h"
#include "db.h"

#include <my_global.h>
#include <mysql.h>
#include <errmsg.h>

using namespace  std;

extern CFG g_cfg;
extern MYSQL *conn;

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
//
//为了避免发送过程长导致此处挂起，不再执行“添加注册信息到注册映射表”.
//
void CClientManager::AddToQueue(string stoken)
{	
	LogExt(LOG_LOG_LEVEL, "[log][CClientManager]get %s\n",stoken.c_str());

	CRegDevice* p = NULL;
	string sql("");

	{
		//CAutoLock Lock(p_manger->get_regdevmap_CS());
		REGDEVICE_MAP::iterator it = p_manger->get_p_regDeviceMap()->find(stoken);
		if (it == p_manger->get_p_regDeviceMap()->end())		
		{
			//p= new CRegDevice(stoken.c_str(),0);
			//if (NULL!=p)
			//{
			//	p_manger->get_p_regDeviceMap()->insert(pair<string,CRegDevice*>(stoken,p));
				sql = "insert into hly.table_relation_pushmsg_mobile_ios (device_token,reg_time_t,is_need_send,sended_id) values('";			
				sql.append(stoken);
				sql.append("',current_timestamp(),'1','000000000000') \
					ON DUPLICATE KEY UPDATE reg_time_t=current_timestamp(),is_need_send='true';");			
				
			//}
			//else
			//{
			//	writelogimmediatly("[exception]new CRegDevice\n");
			//	throw exception("new error");
			//}
			
		}
	
	}
	if (!sql.empty())
	{
		if(BBT_DOSQL(sql.c_str()))
		{
// 			MYSQL_ROW row;
// 			//int num_fields;
// 			sql="SELECT id FROM  hly.Table_Relation_PushMsg_Mobile_IOS WHERE device_token='";
// 			sql.append(stoken);
// 			sql.append("';");
// 			
// 			switch(	mysql_query(conn, sql.c_str()))
// 			{
// 			case CR_COMMANDS_OUT_OF_SYNC:
// 				DEBUGOUT("CR_COMMANDS_OUT_OF_SYNC");
// 				break;
// 			case CR_SERVER_GONE_ERROR:
// 				DEBUGOUT("CR_SERVER_GONE_ERROR");
// 				break;
// 			case CR_SERVER_LOST:
// 				DEBUGOUT("CR_SERVER_LOST");
// 				break;
// 			case CR_UNKNOWN_ERROR:
// 				DEBUGOUT("CR_SERVER_LOST");
// 				break;
// 			default:
// 				break;
// 			}
// 			MYSQL_RES *result = mysql_store_result(conn);
// 			if(NULL!=result)
// 			{
// 				//num_fields = mysql_num_fields(result);
// 								
// 				if ((row = mysql_fetch_row(result)))
// 				{
// 					p->m_id =atol(row[0]);
// 				}
// 			}
// 			mysql_free_result(result);	
		}
	}

	
}

//
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
		writelogimmediatly("[exception][CClientManager]CanGetNewClient!\n");
		exceptiontolog(e);
		setallthreadexitflag();
	}
	
	return false;

}

CCLient* CClientManager::GetClient()
{
	CCLient *temp= NULL;
	CAutoLock Lock(&cs);
	 
	if( !idleList.empty() )
	{        
		temp = idleList.front();
		idleList.pop_front();
		activeList.push_back(temp);			
	}

	return temp;
	
}

void CClientManager::PushNewIn(CCLient * temp)
{

	CAutoLock Lock(&cs);
	activeList.push_back(temp);
		 
}
//连接被关闭或出错调用 //
void CClientManager::KillClient(CCLient * temp)
{

	
	_set_se_translator(SeTranslator);
	try
	{

		if(temp==NULL) return;

#ifdef _DEBUG
		LogExt(LOG_LOG_LEVEL,"[log][CClientManager]KillClient(%x,%d)\n",temp,temp->_fd);
#endif
		
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
		writelogimmediatly("[exception][CClientManager]KillClient!\n");
		exceptiontolog(e);
		setallthreadexitflag();		
	}
	
}


void CClientManager::start()
{
	if (INVALID_HANDLE_VALUE == this->mEvent)
	{
		this->creatwork( CClientManager::run );
	}
	writelogimmediatly("[log][CClientManager]start ok.\n");
}

void CClientManager::stop()
{	
	if (INVALID_HANDLE_VALUE !=mEvent)
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
	
	int ret=0;
	DWORD op;
	int oplen =sizeof(DWORD);
	std::list<CCLient *>::iterator it;
	{	
		CAutoLock Lock(&cs);

		it =activeList.begin(); 
		while (it != activeList.end())
		{
			ret = getsockopt((*it)->_fd,SOL_SOCKET,SO_CONNECT_TIME,(char*)&op,&oplen);
			if (0==ret)
			{
				if (op > g_cfg.outtime || (time(NULL) - (*it)->delay_time > g_cfg.outtime) )  //秒
				{
				#ifdef _DEBUG
					LogExt(LOG_LOG_LEVEL,"[log][CClientManager]remove socket[%d]>%d\n",(*it)->_fd);
				#endif
					idleList.push_back(*it);
					activeList.remove(*it);					

					it =activeList.begin(); 
					continue;
				}
			}
			++it;
		}
	}	
		
}

void CClientManager::run( LPVOID lpParam )
{

//当保证注册过程不挂起，这里还用20秒
#define  INTERVAL_TIME   20*1000

	DWORD dwResult = 0 ;
	CClientManager* p = (CClientManager*) lpParam ;

	while(!allExitFlag )
	{
		dwResult = WaitForSingleObject(p->mEvent, INTERVAL_TIME);//过滤一遍僵尸连接()
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

	writelogimmediatly("[CClientManager]run exit\n");
}

void CClientManager::setManager(CManager *pmg)
{
	this->p_manger = pmg;
}