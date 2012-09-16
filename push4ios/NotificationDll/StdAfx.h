// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__3072A8D2_4B54_4B39_9F88_44F453BB8908__INCLUDED_)
#define AFX_STDAFX_H__3072A8D2_4B54_4B39_9F88_44F453BB8908__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED

#define LOGLOG
 
#define MEMMAP
#define NONEBLOCK_SOCKET
 
//#define USE_SANDBOX



#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

#include <PROCESS.H>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "libmysql.lib")
#pragma comment(lib, "mysqlclient.lib")
#pragma comment(lib, "WS2_32.LIB")
#pragma comment( lib, "libeay32.lib" )
#pragma comment( lib, "ssleay32.lib" )


#include <openssl/ssl.h>

#include "SeException.h"

#include "log.h"
#include "client.h"
#include "api.h"

#include "tools.h"
#include "api.h" 
#include "client.h"
#include "ClientManager.h"
#include "Loader.h"
#include "Worker.h"
#include "Server.h"
#include "Manager.h"
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__3072A8D2_4B54_4B39_9F88_44F453BB8908__INCLUDED)
