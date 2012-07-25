

#include "stdafx.h"

#include <my_global.h>
#include <mysql.h>
#include <errmsg.h>

#include <time.h>

#include "DB.h"
#include "log.h"
//#include "config.h"



extern Clog  g_log;
extern CFG g_cfg;


#pragma warning (disable:4244)
#pragma warning (disable:4786)
#pragma warning (disable:4800)
///全局数据库连接指针

MYSQL *conn= NULL;


 
#define _FIELD_COPY(d,s) memcpy((d),LPCTSTR(s),(s).GetLength()>sizeof(d)?sizeof(d):(s).GetLength());

#define _DBT_TRY try{

#define _DBT_CATCH(x) }catch(...){\
                 LogExt(ERROR_LEVEL,"函数%s异常，请检查网络连接或数据库\n",(x));\
				}



bool DataBaseIni(const char *m_strServerName, const char *m_strUserName,const char *m_strPassword,const char *m_strDBName,
				 unsigned int port)
{

	if (conn)
	{
		//mysql_close(conn);
	}
	else
	{
		conn = mysql_init(NULL);
		//mysql_options(conn, MYSQL_SET_CHARSET_NAME, "utf8");
		mysql_real_connect(conn, m_strServerName, m_strUserName, m_strPassword, m_strDBName, port, NULL, 0);
		mysql_set_character_set(conn, "utf8"); //// 向你的程序说明，是以utf8字符集连接到MYSQL数据库,前提是数据库utf8编码
		conn->reconnect=1;
	}
	return true;

}
// mysql> SELECT UNIX_TIMESTAMP('2005-03-27 03:00:00');
// +---------------------------------------+
// | UNIX_TIMESTAMP('2005-03-27 03:00:00') |
// +---------------------------------------+
// |                            1111885200 |
// +---------------------------------------+
// mysql> SELECT UNIX_TIMESTAMP('2005-03-27 02:00:00');
// +---------------------------------------+
// | UNIX_TIMESTAMP('2005-03-27 02:00:00') |
// +---------------------------------------+
// |                            1111885200 |
// +---------------------------------------+
// mysql> SELECT FROM_UNIXTIME(1111885200);
// +---------------------------+
// | FROM_UNIXTIME(1111885200) |
// +---------------------------+
// | 2005-03-27 03:00:00       |
// +---------------------------+
// 
// create table Table_BaseInfo_PushMsg
// (
//  id                   int not null,
//  title                varchar(64),
//  body                 varchar(128),
//  link_page_id         int,
//  start_time           timestamp,  //TIMESTAMP WITHOUT TIME ZONE
//  stop_time            timestamp,  //TimestampTz WITH TIME ZONE
//  send_count           int,
//  primary key (id)
//  );
// 
// alter table Table_BaseInfo_PushMsg comment '推送消息';

// create table Table_Relation_PushMsg_Mobile
// (
//  id                   int not null,
//  push_msg_id          int,
//  imei                 varchar(15),
//  primary key (id)
// );
//unix_timestamp()，返回自1970-1-1 0:00:01开始到当前系统时间为止的秒数。
//from_unixtime(unixtime)
//time_t
//It is almost universally expected to be an integral value representing 
//the number of seconds elapsed since 00:00 hours, Jan 1, 1970 UTC. 
//This is due to historical reasons, since it corresponds to a unix timestamp,
// but is widely implemented in C libraries across all platforms.
////////////////////////
/// 
void loaddb(INFO_MAP * mapinfo,IMEIID_MAP* mapimei)
{


	try
	{
			// 信息表
			// *表    Table_BaseInfo_PushMsg
			//  主键  id        //int 序号
			//  字段  title      //varchar 标题
			//  字段  body		  //varchar 内容
			//  字段  link_page_id    //int //跳转指令
			//  字段  stop_time //timestamp //过期时间  
			//
			
		string strQry;
		string strVal;
		 
		//delete outtime info
		EnterCriticalSection(&g_cs);
		INFO_MAP::iterator it  = mapinfo->begin();
		INFO_MAP::iterator it2 = it;
		while (it != mapinfo->end()) 
		{
			if (time(NULL) > it->second->expired)
			{
				delete it->second ;
				it2 = it;
				++it2;
				mapinfo->erase(it);
				it= it2;
			}
			else
			{
				++it;
			}
		}
		LeaveCriticalSection(&g_cs);
		//
        ///get info list
		//: 确认查询语句字段名等正确
		switch(	mysql_query(conn, "SELECT id,title,body,link_page_id,UNIX_TIMESTAMP(stop_time) FROM Table_BaseInfo_PushMsg where CURRENT_TIMESTAMP() < stop_time order by id ;"))
		{
		case CR_COMMANDS_OUT_OF_SYNC:
			DEBUGOUT("CR_COMMANDS_OUT_OF_SYNC");
			break;
		case CR_SERVER_GONE_ERROR:
			DEBUGOUT("CR_SERVER_GONE_ERROR");
			break;
		case CR_SERVER_LOST:
			DEBUGOUT("CR_SERVER_LOST");
			break;
		case CR_UNKNOWN_ERROR:
			DEBUGOUT("CR_SERVER_LOST");
			break;
		default:
			break;
		}
		MYSQL_RES *result = mysql_store_result(conn);
		assert(NULL!=result);
		MYSQL_ROW row;
		int num_fields;
		UINT idd=0;

		num_fields = mysql_num_fields(result);
		
		while ((row = mysql_fetch_row(result)))
		{
		 
			idd  = atol(row[0]);  
			it= mapinfo->find(idd); 
			if (it == mapinfo->end() )
			{
				//UTF8  //unix_timestamp is time_t
				Cinfo * info=new Cinfo(row[1],row[2],row[3], (time_t)row[4], idd); 
				if (info)
				{
					EnterCriticalSection(&g_cs);		
					mapinfo->end();                              //从数据库中查询到的数据始终应该比内存中的新
					mapinfo->insert(pair<UINT, Cinfo*>(idd,info));	//<id,info>	//必须有序	
					LeaveCriticalSection(&g_cs);
				}
				else
				{
					LogExt(ERROR_LEVEL,"mysql error[%s]", mysql_error(conn));
					throw exception("[newerror]");
				}		
			}
			
		}
		
		mysql_free_result(result);

		// : get imei -id   list
		//TODO: 确认查询语句字段名等正确
		switch(	mysql_query(conn, "SELECT imei,push_msg_id FROM  Table_Relation_PushMsg_Mobile ;"))
		{
		case CR_COMMANDS_OUT_OF_SYNC:
			DEBUGOUT("CR_COMMANDS_OUT_OF_SYNC");
			break;
		case CR_SERVER_GONE_ERROR:
			DEBUGOUT("CR_SERVER_GONE_ERROR");
			break;
		case CR_SERVER_LOST:
			DEBUGOUT("CR_SERVER_LOST");
			break;
		case CR_UNKNOWN_ERROR:
			DEBUGOUT("CR_SERVER_LOST");
			break;
		default:
			break;
		}
		result = mysql_store_result(conn);
		assert(NULL!=result);
		
		num_fields = mysql_num_fields(result);
		
		while ((row = mysql_fetch_row(result)))
		{
			
			mapimei->insert(pair<string, UINT>(row[0], atol(row[1])));	//<imei,id>	//无序	
		}
		mysql_free_result(result);
	
	 
			
	}
	catch(...)
	{
		LogExt(CRITICAL_LEVEL,TEXT("[exception]loaddb exception13!\n"));
	}
	return ;
	
	
}
         
bool BBT_DOSQL(const char *psql)
{
	if(0!= mysql_query(conn, psql))	
	{
		LogExt(ERROR_LEVEL,"[EXEC SQL]err:%s", mysql_error(conn));
		return false;
	}
	else
	{
		g_log.log("[EXEC SQL]ok",LOG_LOG_LEVEL);
		return true;
	}
}

void BBT_DisConn()
{
	g_log.log("[SQL]mysql close connect.",LOG_LOG_LEVEL);
	mysql_close(conn);
}
