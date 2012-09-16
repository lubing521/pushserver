// Loader.cpp: implementation of the CLoader class.
// 加载类
// 1. 从数据表加载数据：信息表，注册表，注销表，发送状态表
// 2. 间隔1分钟加载一次
// 3. 数据库连接，断开自动重连
// 
// author:张世光 2012.7   87895224@QQ.com
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Loader.h"
#include "db.h"
#include "Manager.h"
//////////////////////////////////////////////////////////////////////
static void CLoader::run( LPVOID lpParam );

extern  CFG g_cfg;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction  mEvent(0),hthread(0),
//////////////////////////////////////////////////////////////////////

CLoader::CLoader():pManager(NULL)
{
}

CLoader::~CLoader()
{
	stop();
}

 void CLoader::init(CFG* cfg,CManager* mg)
{
 
	pManager  = mg;
#ifdef _DEBUG
	char buf[400];
	sprintf(buf,"%s,%s,%s,%s,%d\n",cfg->db_ip.c_str(),cfg->db_user.c_str(),cfg->db_psw.c_str(),cfg->db_name.c_str(),cfg->db_port);
	writelogimmediatly(buf);

#endif
	DataBaseIni(cfg->db_ip.c_str(),cfg->db_user.c_str(),cfg->db_psw.c_str(),
				cfg->db_name.c_str(),cfg->db_port);

	setManager(pManager);


}

void CLoader::start()
{
 
	if (INVALID_HANDLE_VALUE == mEvent)
	{
		creatwork(CLoader::run);
	}
	writelogimmediatly("[log][CLoader]start ok.\n");
}

void CLoader::stop()
{
	if(INVALID_HANDLE_VALUE != mEvent)
	{
		SetEvent(mEvent);
		WaitForSingleObject( hthread ,3000);
		CloseHandle(mEvent);
		mEvent =INVALID_HANDLE_VALUE;

		BBT_DisConn();
		writelogimmediatly("[log][CLoader]stop.\n");
	}
}
//load data from database low frequency
void CLoader::run( LPVOID lpParam )
{
	DWORD dwResult = 0 ;
	CLoader* ploader = (CLoader*) lpParam ;

	_set_se_translator(SeTranslator);
	try
	{
		{	
			CAutoLock Lock(ploader->pManager->get_worker_loader_CS());
			loaddb(ploader->pManager->get_p_minfo(),ploader->pManager->get_p_regDeviceMap()
				#ifdef UNREG_MAN
				   ,ploader->pManager->get_p_unregDeviceMap()
				#endif
				#ifdef REMEMBER_STATUS
				   ,ploader->pManager->get_p_SendStatus()
				#endif
				   );
		
		}

		while(!allExitFlag )
		{
			dwResult = WaitForSingleObject(ploader->mEvent, g_cfg.loaddb_interval_minutes*60*1000);//60*1000
			if (!allExitFlag )
			{
				if(WAIT_OBJECT_0 == dwResult)//to exit
				{
					CloseHandle(ploader->mEvent);
					break;
				}
				else if (WAIT_TIMEOUT == dwResult)//to work
				{
					// db to  mapImeiId mapinfo
					CAutoLock Lock(ploader->pManager->get_worker_loader_CS());
					
					loaddb(ploader->pManager->get_p_minfo(),ploader->pManager->get_p_regDeviceMap()
						#ifdef UNREG_MAN
							,ploader->pManager->get_p_unregDeviceMap()
						#endif
						#ifdef REMEMBER_STATUS
							,ploader->pManager->get_p_SendStatus()
						#endif
							);
					
				}
			}
			else
			{
				CloseHandle(ploader->mEvent);
				break;
			}
		}

	}
	catch(CSeException *e)
	{
		writelogimmediatly("[exception][Loader]!\n");
		exceptiontolog(e);
		setallthreadexitflag();
		
	}
	 
	writelogimmediatly("[log][CLoader]run exit\n");

}





