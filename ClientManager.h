// ClientManager.h: interface for the CClientManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTMANAGER_H__8E61F038_F3DB_4E22_922D_31BA27A571BB__INCLUDED_)
#define AFX_CLIENTMANAGER_H__8E61F038_F3DB_4E22_922D_31BA27A571BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CCLient;
class CWorker;

class CClientManager  
{
public:
	CClientManager();
	virtual ~CClientManager();


	void AddToQueue(string imei, CCLient* client);
	void DeleteFromQueue(string imei);
	long GetActiveSize();
	bool CanGetNewClient();
	CCLient* GetClient();
	void PushNewIn(CCLient *);
	void KillClient(CCLient *);
	
	CLIENT_MAP* getClientMap();
	void setworker(CWorker*);


private:
	CLIENT_MAP clientqueue;
	CWorker* mpworker;
	
	std::list<CCLient *> activeList;	//活动队列
	std::list<CCLient *> idleList;	//空闲队列
	CRITICAL_SECTION cs;
};

#endif // !defined(AFX_CLIENTMANAGER_H__8E61F038_F3DB_4E22_922D_31BA27A571BB__INCLUDED_)
