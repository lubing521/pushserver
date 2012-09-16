// sender.cpp: implementation of the CCKThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sender.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
// 工作线程类的父类
// 
// author：张世光 2012.7
//////////////////////////////////////////////////////////////////////

CCKThread::CCKThread():mEvent(INVALID_HANDLE_VALUE),hthread(INVALID_HANDLE_VALUE)
{
}
CCKThread::~CCKThread()
{
}
void CCKThread::start()
{
}
void CCKThread::stop()
{
}
void CCKThread::ckSetEvent()
{
	SetEvent(mEvent);
}
bool CCKThread::creatwork(void (__cdecl * run) (void *))
{
	_set_se_translator(SeTranslator);
	try
	{
		this->mEvent = CreateEvent( NULL  ,FALSE , FALSE ,NULL ); 
		this->hthread = (HANDLE) _beginthread(run,0,this);	
		if ( NULL!= this->hthread  )
		{	
#ifdef _DEBUG
			LogExt(DEBUG_ONLY_LEVEL,"[log][CCKThread]creatwork[0x%0x]handle[0x%0x]\n",this,this->hthread);
#endif
		}
		else
		{			
			g_log.log("[error][CCKThread]create works fail\n",ERROR_LEVEL);
			
			allExitFlag =true;
			return false;
		}
		
		return true;
	}
	catch(CSeException *e)
	{
#ifdef _DEBUG
		printexception(DEBUGARGS);
#endif
		exceptiontolog(e);
		setallthreadexitflag();
		g_log.log("[exception][CCKThread]creatwork exception!\n",CRITICAL_LEVEL);
	}
	return false;
	
}