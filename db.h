#ifndef _DATABASE__TOOLS_H_
#define _DATABASE__TOOLS_H_

//////////////////////////////////////////////////////////////////////////
/// @file  db.h
/// 
/// @brief
///
/// @version 1.0
///
///	@details
///		mysql c connector lib .
//////////////////////////////////////////////////////////////////////////

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>
#include <my_global.h>
#include <mysql.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>

#include "api.h" 

#define MAXNAMELEN 64
//数据库连接参数结构体
typedef struct
{
	char cUserName[MAXNAMELEN];  //数据库登录用户名
	char cPwd[MAXNAMELEN];       //数据库登录密码
	char cDatabaseName[MAXNAMELEN];//数据库名称
	char cServername[MAXNAMELEN];//数据库服务器名称
}DATABASE_PARMER;


bool DataBaseIni(const char *m_strServerName, const char *m_strUserName,const char *m_strPassword,const char *m_strDBName,unsigned int port);

void loaddb(INFO_MAP * mapinfo,IMEIID_MAP* mapimei);
bool BBT_DOSQL(const char *psql);
void BBT_DisConn();

#endif //_DATABASE_TOOLS_H_



