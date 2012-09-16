// ClientManager.h: interface for the CClientManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTMANAGER_H__8E61F038_F3DB_4E22_922D_31BA27A571BB__INCLUDED_)
#define AFX_CLIENTMANAGER_H__8E61F038_F3DB_4E22_922D_31BA27A571BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "sender.h"

class CCLient;
class CWorker;


class CClientManager : public CCKThread
{
public:
	CClientManager();
	virtual ~CClientManager();


	void AddToQueue(string imei, CCLient* client);
	
	long GetActiveSize();
	bool CanGetNewClient();
	CCLient* GetClient();
	void PushNewIn(CCLient *);
	void KillClient(CCLient *);
		
	CLIENT_MAP* getClientMap();
	void setworker(CWorker*);

	void start();
	void stop();
	void killTimeoutClient();

private:
	void DeleteFromQueue(string imei);

	CLIENT_MAP clientqueue;
	CWorker* mpworker;
	
	std::list<CCLient *> activeList;	//活动队列
	std::list<CCLient *> idleList;	//空闲队列
	CRITICAL_SECTION cs;
	CRITICAL_SECTION queue_cs;

	static void run( LPVOID lpParam );
};

#endif // !defined(AFX_CLIENTMANAGER_H__8E61F038_F3DB_4E22_922D_31BA27A571BB__INCLUDED_)
