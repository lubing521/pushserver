// Manager.cpp: implementation of the CManager class.
//svn://192.168.10.3/HUANLEYOU/SourceCode/trunk/Server/PushSubsystem
//svn://192.168.10.3/HUANLEYOU/SourceCode/trunk/Server/TransactionSubsystem
//
//  推送管理类
//
// 1.启动
// 2.停止
// author：张世光 2012.7 87895224@QQ.com
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "api.h" 
#include "client.h"
#include "ClientManager.h"
#include "Loader.h"
#include "Worker.h"
#include "Server.h"


#include "Manager.h"
//////////////////////////////////////////////////////////////////////
bool volatile allExitFlag	 = false;     //exception exit

Clog	g_log;
CFG		g_cfg;

 

extern CManager gmanager;
//////////////////////////////////////////////////////////////////////////


void readcfg()
{
	string filepath;
	string path = getExePath();
	filepath = path;
	filepath.append(string("\\SysConfig.ini"));
#define BUF_LEN 60
	char str[BUF_LEN+2];
	memset(str,0,sizeof(str));
	//本地IP
	GetPrivateProfileString("CGISERVER", "IP", "127.0.0.1",str,BUF_LEN, filepath.c_str());
	g_cfg.local_ip = str;
	
	g_cfg.local_port = GetPrivateProfileInt("CGISERVER", "PORT", 8080, filepath.c_str());
	
	g_cfg.max_works_num = GetPrivateProfileInt("CGISERVER", "workers", 3, filepath.c_str());
	
	g_cfg.max_clients_num = GetPrivateProfileInt("CGISERVER", "max_client", 100000, filepath.c_str());
	
	//
	g_cfg.loaddb_interval_minutes = GetPrivateProfileInt("LOADDB", "interval_minutes", 1, filepath.c_str());
	////DB 
	GetPrivateProfileString("DBSERVER", "dbname", "hly",str,BUF_LEN, filepath.c_str());
	g_cfg.db_name = str;
	GetPrivateProfileString("DBSERVER", "user", "root",str,BUF_LEN, filepath.c_str());
	g_cfg.db_user = str;
	GetPrivateProfileString("DBSERVER", "psw", "123456",str,BUF_LEN, filepath.c_str());
	g_cfg.db_psw  = str;
	GetPrivateProfileString("DBSERVER", "IP", "127.0.0.1",str,BUF_LEN, filepath.c_str());
	g_cfg.db_ip=str;
	g_cfg.db_port = GetPrivateProfileInt("DBSERVER", "PORT", 3306, filepath.c_str());
	//“恶意”连接多久关闭，单位秒
	g_cfg.outtime = GetPrivateProfileInt("LINK", "outtime", 10, filepath.c_str());
	
	/////feedback.push.apple.com, port 2196;
	//you access the sandbox feedback service via feedback.sandbox.push.apple.com, port 2196
	GetPrivateProfileString("APPLE", "feedbackwww", "feedback.push.apple.com",str,BUF_LEN, filepath.c_str());
	g_cfg.feedback_www = str;
	g_cfg.feedback_port = GetPrivateProfileInt("APPLE", "feedbackport", 2196, filepath.c_str());

	GetPrivateProfileString("APPLE", "feedbacksandboxwww", "feedback.sandbox.push.apple.com",str,BUF_LEN, filepath.c_str());
	g_cfg.feedback_sandbox_www = str;
	g_cfg.feedback_sandbox_port = GetPrivateProfileInt("APPLE", "feedbacksandboxport", 2196, filepath.c_str());

	//gateway.push.apple.com, port 2195
	//gateway.sandbox.push.apple.com, port 2195
	GetPrivateProfileString("APPLE", "APNSwww", "gateway.push.apple.com",str,BUF_LEN, filepath.c_str());
	g_cfg.APNs_www = str;
	g_cfg.APNs_port = GetPrivateProfileInt("APPLE", "APNSport", 2195, filepath.c_str());
	
	GetPrivateProfileString("APPLE", "APNSsandboxwww", "gateway.sandbox.push.apple.com",str,BUF_LEN, filepath.c_str());
	g_cfg.APNs_sandbox_www = str;
	g_cfg.APNs_sandbox_port = GetPrivateProfileInt("APPLE", "APNSsandboxport", 2195, filepath.c_str());

	GetPrivateProfileString("APPLE", "SandboxPEMFile", "apns-ios-development-sanbox.pem",str,BUF_LEN, filepath.c_str());
	g_cfg.sandbox_pem_file = str;

	GetPrivateProfileString("APPLE", "PEMFile", "apns-ios-release.pem",str,BUF_LEN, filepath.c_str());
	g_cfg.pem_file = str;

	GetPrivateProfileString("APPLE", "PEMPassWord", "",str,BUF_LEN, filepath.c_str());
	g_cfg.pem_psw = str;
	
	g_cfg.sandbox0_or_production1 = GetPrivateProfileInt("APPLE", "sandbox0_or_production1", 0, filepath.c_str());

	writelogimmediatly("[log][readcfg]ok.\n");
}

////从内部（异常）退出
void setallthreadexitflag()
{

	allExitFlag = true;
	
	gmanager.stopFrommyInter();
	
}
bool IsSandBox()
{
	return (bool)(0 == g_cfg.sandbox0_or_production1);
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CManager::CManager():cbfun(NULL)
{
#ifdef REMEMBER_STATUS
 InitializeCriticalSection(&m_sendStatus_cs);
#endif
 //InitializeCriticalSection(&m_g_cs);
 InitializeCriticalSection(&m_regDevMap_cs);
 InitializeCriticalSection(&m_gcs_worker_loader);
 #ifdef UNREG_MAN
 InitializeCriticalSection(&m_unregDevMap_cs);
#endif
}

CManager::~CManager()
{
#ifdef REMEMBER_STATUS
	DeleteCriticalSection(&m_sendStatus_cs);
#endif
	//DeleteCriticalSection(&m_g_cs);
	DeleteCriticalSection(&m_regDevMap_cs);
	DeleteCriticalSection(&m_gcs_worker_loader);
#ifdef UNREG_MAN
	DeleteCriticalSection(&m_unregDevMap_cs);
#endif
	writelogimmediatly("[~Manager]程序退出.\n");
}

void CManager::start()
{
	allExitFlag = false;
	
	writelogimmediatly("[log][Manager]程序启动.\n");
	readcfg();
	try
	{
		m_loader.init(&g_cfg,this);
		m_loader.start();
	}
	catch(...)
	{
		writelogimmediatly("[err][loader]启动失败。请检查连接数据服务器的参数是否正常?\n");
		setallthreadexitflag();
		return;
	}
	m_clientmanager.setManager(this);
	m_clientmanager.start();
 	
	m_worker.init(&m_clientmanager,this);
	m_worker.start();
 
	m_server.init(&g_cfg,&m_clientmanager,&m_loader);
	m_server.Listen();
	m_server.start();
	
}

void CManager::stop()
{	

	if (allExitFlag)
	{
		return;
	}
	allExitFlag = true;	

	m_server.stop();
	m_clientmanager.stop();
	m_worker.stop();
	m_loader.stop();
	writelogimmediatly("[log][Manager]程序退出.\n");
}

void CManager::stopFrommyInter()
{
	if (cbfun)
	{
		cbfun();
	}
	
	
}
#ifdef REMEMBER_STATUS
void CManager::EnterCriticalSection_sendStatus()
{
	EnterCriticalSection(& this->m_sendStatus_cs);
}
void CManager::LeaveCriticalSection_sendStatus()
{
	LeaveCriticalSection(& this->m_sendStatus_cs);
}
#endif

// void CManager::EnterCriticalSection_infoMap()
// {
// 	EnterCriticalSection(& this->m_g_cs);
// }
// void CManager::LeaveCriticalSection_infoMap()
// {
// 	LeaveCriticalSection(& this->m_g_cs);
// }

void CManager::EnterCriticalSection_regDevMap()
{
	EnterCriticalSection(& this->m_regDevMap_cs);
}
void CManager::LeaveCriticalSection_regDevMap()
{
	LeaveCriticalSection(& this->m_regDevMap_cs);
}
#ifdef UNREG_MAN
void CManager::EnterCriticalSection_unregDevMap()
{
	EnterCriticalSection(& this->m_unregDevMap_cs);
}
void CManager::LeaveCriticalSection_unregDevMap()
{
	LeaveCriticalSection(& this->m_unregDevMap_cs);
}
#endif

void CManager::EnterCriticalSection_workerloader()
{
	EnterCriticalSection(& this->m_gcs_worker_loader);
}
void CManager::LeaveCriticalSection_workerloader()
{
	LeaveCriticalSection(& this->m_gcs_worker_loader);
}