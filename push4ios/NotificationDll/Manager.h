// Manager.h: interface for the CManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MANAGER_H__08BD67B5_6E2E_4877_BFB2_BFCA1AC2317C__INCLUDED_)
#define AFX_MANAGER_H__08BD67B5_6E2E_4877_BFB2_BFCA1AC2317C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CServer;
class CClientManager;
class CWorker;
class CLoader;

typedef void (*CBSTOPFUNC)();

class CManager  
{
public:
	CManager();
	virtual ~CManager();

	void stopFrommyInter();

	//
	void start();
	void stop();

	CBSTOPFUNC cbfun;

	//
	CRITICAL_SECTION* get_worker_loader_CS(){return &m_gcs_worker_loader;}
	CRITICAL_SECTION* get_regdevmap_CS(){return &m_regDevMap_cs;}
	//void EnterCriticalSection_infoMap();
	//void LeaveCriticalSection_infoMap();
	void EnterCriticalSection_regDevMap();
	void LeaveCriticalSection_regDevMap();
#ifdef UNREG_MAN
	void EnterCriticalSection_unregDevMap();
	void LeaveCriticalSection_unregDevMap();
	CRITICAL_SECTION* get_unregdevmap_CS(){return &m_unregDevMap_cs;}
#endif

#ifdef REMEMBER_STATUS
	void EnterCriticalSection_sendStatus();
	void LeaveCriticalSection_sendStatus();
	CRITICAL_SECTION* get_sendStatus_CS(){return &m_sendStatus_cs;}
#endif

	void EnterCriticalSection_workerloader();
	void LeaveCriticalSection_workerloader();

public:	
#ifdef REMEMBER_STATUS
	CSendStatus      * get_p_SendStatus(){return &m_gSendStatus; }
#endif
	REGDEVICE_MAP    *get_p_regDeviceMap(){return &m_regDeviceMap;}
#ifdef UNREG_MAN
	UNREGDEVICE_MAP  *get_p_unregDeviceMap(){return &m_unregDeviceMap;}
#endif
	INFO_MAP		 *get_p_minfo(){return &m_minfo;}	


private:
	CServer			m_server;
	CClientManager	m_clientmanager;
	CWorker			m_worker;
	CLoader			m_loader;

#ifdef REMEMBER_STATUS
	CSendStatus      m_gSendStatus; //发送状态
#endif
	REGDEVICE_MAP    m_regDeviceMap;//注册设备列表
#ifdef UNREG_MAN
	UNREGDEVICE_MAP  m_unregDeviceMap;//注销设备列表
#endif
	INFO_MAP		 m_minfo;	//信息映射表


#ifdef REMEMBER_STATUS	
	CRITICAL_SECTION m_sendStatus_cs;
#endif
	CRITICAL_SECTION m_regDevMap_cs;
#ifdef UNREG_MAN
	CRITICAL_SECTION m_unregDevMap_cs;
#endif
	//CRITICAL_SECTION m_g_cs;//info map

	CRITICAL_SECTION m_gcs_worker_loader;//加载和发送互斥//infomap&regmap &status

};

#endif // !defined(AFX_MANAGER_H__08BD67B5_6E2E_4877_BFB2_BFCA1AC2317C__INCLUDED_)
