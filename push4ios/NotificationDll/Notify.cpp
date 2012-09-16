// Notify.cpp : Implementation of CNotify
#include "stdafx.h"
#include "NotificationDll.h"
#include "Notify.h"


#include "client.h"
#include "ClientManager.h"
#include "Server.h"
#include "Loader.h"
#include "Worker.h"
#include "Manager.h"
/////////////////////////////////////////////////////////////////////////////
// CNotify
CManager   gmanager;


STDMETHODIMP CNotify::start()
{
	gmanager.start();

	return S_OK;
}

STDMETHODIMP CNotify::stop()
{
	gmanager.stop();

	return S_OK;
}

STDMETHODIMP CNotify::set_cb(long *pcb)
{
	gmanager.cbfun = (CBSTOPFUNC)pcb ;

	return S_OK;
}
