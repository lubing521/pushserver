// Manager.cpp: implementation of the CManager class.
//svn://192.168.10.3/HUANLEYOU/SourceCode/trunk/Server/PushSubsystem
//svn://192.168.10.3/HUANLEYOU/SourceCode/trunk/Server/TransactionSubsystem
//
//  推送管理类
//
// 1.启动
// 2.停止
// author：张世光 2012.7
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"


#include "client.h"
#include "ClientManager.h"
#include "Loader.h"
#include "Worker.h"
#include "Server.h"


#include "Manager.h"
//////////////////////////////////////////////////////////////////////
bool allExitFlag	 = false;     //exception exit
bool stopServiceFlag = false;//stop service
Clog	g_log;
CFG		g_cfg;

CRITICAL_SECTION g_cs;//info map 
//////////////////////////////////////////////////////////////////////////


void readcfg()
{
	string filepath;
	string path = getExePath();
	filepath = path;
	filepath.append(string("\\SysConfig.ini"));
	
	char str[20];
	memset(str,0,sizeof(str));
	//本地IP
	GetPrivateProfileString("CGISERVER", "IP", "127.0.0.1",str,19, filepath.c_str());
	g_cfg.local_ip = "";
	g_cfg.local_ip.append(str);
	
	g_cfg.local_port = GetPrivateProfileInt("CGISERVER", "PORT", 8080, filepath.c_str());
	
	g_cfg.max_works_num = GetPrivateProfileInt("CGISERVER", "workers", 3, filepath.c_str());
	
	g_cfg.max_clients_num = GetPrivateProfileInt("CGISERVER", "max_client", 100000, filepath.c_str());
	
	////DB 
	GetPrivateProfileString("DBSERVER", "dbname", "test",str,19, filepath.c_str());
	g_cfg.db_name = str;
	GetPrivateProfileString("DBSERVER", "user", "root",str,19, filepath.c_str());
	g_cfg.db_user = str;
	GetPrivateProfileString("DBSERVER", "psw", "123456",str,19, filepath.c_str());
	g_cfg.db_psw  = str;
	GetPrivateProfileString("DBSERVER", "IP", "127.0.0.1",str,19, filepath.c_str());
	g_cfg.db_ip.empty();
	g_cfg.db_ip.append(str);
	g_cfg.db_port = GetPrivateProfileInt("DBSERVER", "PORT", 3306, filepath.c_str());
	
	
	
}

////从内部（异常）退出
void setallthreadexitflag()
{
	allExitFlag = true;
	
	g_log.log("setallthreadexitflag !!!",ERROR_LEVEL);
	stopFrommyInter();
	
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CManager::CManager()
{
 InitializeCriticalSection(&g_cs);
}

CManager::~CManager()
{

	DeleteCriticalSection(&g_cs);
	g_log.log("[Manager]程序退出.",LOG_LOG_LEVEL);
}

void CManager::start()
{
	g_log.log("[Manager]程序启动.",LOG_LOG_LEVEL);
	readcfg();

	loader.init(&g_cfg);
	loader.start();

	clientmanager.setworker(&worker); //for setevent to worker
	worker.init(&clientmanager,&loader);
	worker.start();

	server.init(&g_cfg,&clientmanager);
	server.Listen();
	server.start();
	
}

void CManager::stop()
{	
	allExitFlag = true;
	worker.stop();
	loader.stop();
}

