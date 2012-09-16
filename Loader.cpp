// Loader.cpp: implementation of the CLoader class.
// 加载类
// 1. 从数据表加载IMEI-ID 队列
// 2. 加载 动态信息队列
// 3. 1分钟加载一次
// 4. 数据库连接，断开自动重连
// 
// author:张世光 2012.7 
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Loader.h"
#include "db.h"

//////////////////////////////////////////////////////////////////////
static void CLoader::run( LPVOID lpParam );
//////////////////////////////////////////////////////////////////////
// Construction/Destruction  mEvent(0),hthread(0),
//////////////////////////////////////////////////////////////////////

CLoader::CLoader():mpMapInfo(NULL) 
{
}

CLoader::~CLoader()
{
	stop();
}

void CLoader::init(CFG* cfg)
{
	mpMapInfo = &minfo;
	
	DataBaseIni(cfg->db_ip.c_str(),cfg->db_user.c_str(),cfg->db_psw.c_str(),cfg->db_name.c_str(),cfg->db_port);
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
	if (INVALID_HANDLE_VALUE !=mEvent)
	{
		SetEvent(mEvent);
		WaitForSingleObject( hthread ,3000);
		CloseHandle(mEvent);
		mEvent = INVALID_HANDLE_VALUE;

		mapImeiId.clear();

		INFO_MAP::iterator it= minfo.begin();
		while(it!= minfo.end())
		{
			delete it->second;
			it = minfo.erase(it);
		}
		minfo.clear();
		
		BBT_DisConn();
		writelogimmediatly("[log][CLoader]stop.\n");
	}
}
//load data from database low frequency
void CLoader::run( LPVOID lpParam )
{
	DWORD dwResult = 0 ;
	CLoader* ploader = static_cast<CLoader*>(lpParam) ;

	_set_se_translator(SeTranslator);
	try
	{
		loaddb(ploader->mpMapInfo,ploader->getImeiIdMap());

		while(!allExitFlag )
		{
			dwResult = WaitForSingleObject(ploader->mEvent, 60*1000);//60*1000
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
					loaddb(ploader->mpMapInfo,ploader->getImeiIdMap());

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
		exceptiontolog(e);
#ifdef _DEBUG
		printexception(DEBUGARGS);
#endif
		setallthreadexitflag();
		g_log.log("[exception][Loader]!\n",CRITICAL_LEVEL);
	}
	 
#ifdef _DEBUG
	DEBUGOUT("[log][CLoader]run exit\n");
	LogExt(WARNNING_LEVEL,"[log][CLoader]run exit ID[0x%0x]\n",GetCurrentThreadId());
#endif
}


IMEIID_MAP* CLoader::getImeiIdMap()
{
	return &mapImeiId;
}



