// Worker.h: interface for the CWorker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORKER_H__4ED66344_F6A8_44FE_B348_9DE1C3104C57__INCLUDED_)
#define AFX_WORKER_H__4ED66344_F6A8_44FE_B348_9DE1C3104C57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "sender.h"
class CLoader;


class CWorker  : public CCKThread
{
public:
	CWorker();
	virtual ~CWorker();

	void init(CClientManager* pclm , CLoader * loader);
	void start();
	void stop();


	CClientManager* mpclm;
	INFO_MAP * mpinfoqueue;
	CLoader * mploader;

	static void run( LPVOID lpParam );
	
	bool	in_exit_flag;
private:

};

#endif // !defined(AFX_WORKER_H__4ED66344_F6A8_44FE_B348_9DE1C3104C57__INCLUDED_)
