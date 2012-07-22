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

class CManager  
{
public:
	CManager();
	virtual ~CManager();


	void start();
	void stop();

private:
	CServer			server;
	CClientManager	clientmanager;
	CWorker			worker;
	CLoader			loader;

	

};

#endif // !defined(AFX_MANAGER_H__08BD67B5_6E2E_4877_BFB2_BFCA1AC2317C__INCLUDED_)
