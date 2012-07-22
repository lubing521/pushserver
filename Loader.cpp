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
}

void CLoader::stop()
{
	SetEvent(mEvent);
	WaitForSingleObject( hthread ,3000);
	CloseHandle(mEvent);
	mapImeiId.clear();
	minfo.clear();
	
	BBT_DisConn();

}
//load data from database low frequency
void CLoader::run( LPVOID lpParam )
{
	DWORD dwResult = 0 ;
	CLoader* ploader = (CLoader*) lpParam ;

	_set_se_translator(SeTranslator);
	try
	{
	//
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
		setallthreadexitflag();
		g_log.log("Loader exception!\n",CRITICAL_LEVEL);
	}
}


IMEIID_MAP* CLoader::getImeiIdMap()
{
	return &mapImeiId;
}



