// Manager.cpp: implementation of the CManager class.
//svn://192.168.10.3/HUANLEYOU/SourceCode/trunk/Server/PushSubsystem
//svn://192.168.10.3/HUANLEYOU/SourceCode/trunk/Server/TransactionSubsystem
//
//  ���͹�����
//
// 1.����
// 2.ֹͣ
// author�������� 2012.7
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"


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

CRITICAL_SECTION g_cs;//info map 

extern CManager gmanager;
//////////////////////////////////////////////////////////////////////////


void readcfg()
{
	string filepath;
	string path = getExePath();
	filepath = path;
	filepath.append(string("\\SysConfig.ini"));
	
	char str[20];
	memset(str,0,sizeof(str));
	//����IP
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
	g_cfg.db_ip="";
	g_cfg.db_ip.append(str);
	g_cfg.db_port = GetPrivateProfileInt("DBSERVER", "PORT", 3306, filepath.c_str());
	//�����⡱���Ӷ�ùرգ���λ��
	g_cfg.outtime = GetPrivateProfileInt("LINK", "outtime", 10, filepath.c_str());
	
	writelogimmediatly("[log][readcfg]ok.\n");
}

////���ڲ����쳣���˳�
void setallthreadexitflag()
{
	DEBUGOUT("[setallthreadexitflag]\n\n");
	allExitFlag = true;
	
	gmanager.stopFrommyInter();
	
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CManager::CManager():cbfun(NULL)
{
 InitializeCriticalSection(&g_cs);
}

CManager::~CManager()
{
	DeleteCriticalSection(&g_cs);
	DEBUGOUT("[Manager]�����˳�.\n");
}

void CManager::start()
{
	allExitFlag = false;
	
	writelogimmediatly("[log][Manager]��������.\n");
	readcfg();

	try
	{
		loader.init(&g_cfg);
		loader.start();
	}
	catch (...)
	{
		writelogimmediatly("[err][loader]���ݿ�����ʧ�ܣ��������ú����ݿ�������Ƿ�����.\n");
		setallthreadexitflag();
		return;
	}
	

	clientmanager.setworker(&worker); //for setevent to worker
	clientmanager.start();
	
	worker.init(&clientmanager,&loader);
	worker.start();

	server.init(&g_cfg,&clientmanager,&loader);	
	server.start();
	
}

void CManager::stop()
{	

	if (allExitFlag)
	{
		return;
	}
	allExitFlag = true;	

	server.stop();
	clientmanager.stop();
	worker.stop();
	loader.stop();
	writelogimmediatly("[log][Manager]�����˳�.\n");
}

void CManager::stopFrommyInter()
{
	if (cbfun)
	{
		cbfun();
	}
	
	
}
