// Server.h: interface for the CServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVER_H__B519D0FF_87DF_46BA_866E_98D6122B09BD__INCLUDED_)
#define AFX_SERVER_H__B519D0FF_87DF_46BA_866E_98D6122B09BD__INCLUDED_

#include "sender.h"
using namespace std;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CServer : public CCKThread 
{
public:
	CServer();
	virtual ~CServer();

	void init(CFG * cfg,CClientManager* pclientmanager);
	bool Listen();  
	bool sendback(const char* data ,int len);
	void setPort(int p = 65500);
	void setMaxClient(int max_clients = 100000);
	void setMaxWorker(int max_work = 1);

	void start();
	void stop();

public:
	SOCKET _fd;

	int works_max_count;
	int clients_max_count;
	int port;

	HL threadset;
	HANDLE hiocp;
	CClientManager* pClientManager;
private:
	static void run( LPVOID lpParam );

};

#endif // !defined(AFX_SERVER_H__B519D0FF_87DF_46BA_866E_98D6122B09BD__INCLUDED_)
