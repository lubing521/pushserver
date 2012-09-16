// ClientManager.h: interface for the CClientManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTMANAGER_H__8E61F038_F3DB_4E22_922D_31BA27A571BB__INCLUDED_)
#define AFX_CLIENTMANAGER_H__8E61F038_F3DB_4E22_922D_31BA27A571BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "sender.h"
#include <list>

class CCLient;
class CWorker;
class CManager;

class CClientManager : public CCKThread
{
public:
	CClientManager();
	virtual ~CClientManager();


	void AddToQueue(string stoken);
	
	long GetActiveSize();
	bool CanGetNewClient();
	CCLient* GetClient();
	void PushNewIn(CCLient *);
	void KillClient(CCLient *);

	void start();
	void stop();
	void killTimeoutClient();

	void setManager(CManager *pmg);
private:
	void DeleteFromQueue(string imei);

	 
	CManager    *p_manger;
	
	std::list<CCLient *> activeList;	//活动队列
	std::list<CCLient *> idleList;	//空闲队列
	CRITICAL_SECTION cs;
	

	static void run( LPVOID lpParam );
};

#endif // !defined(AFX_CLIENTMANAGER_H__8E61F038_F3DB_4E22_922D_31BA27A571BB__INCLUDED_)
