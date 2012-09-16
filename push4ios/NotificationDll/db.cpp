// db.cpp: .
// MySql数据库操作
// 1.连接
// 2.读取数据
// 3.关闭连接
// 4.执行SQL
// 2012.8 
// author：张世光 87895224@QQ.com
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include <my_global.h>
#include <mysql.h>
#include <errmsg.h>

#include <time.h>

#include "DB.h"
#include "log.h"




extern Clog  g_log;
extern CFG g_cfg;


#pragma warning (disable:4244)
#pragma warning (disable:4786)
#pragma warning (disable:4800)
///全局数据库连接指针
class CManager;

MYSQL *conn= NULL;
CManager *db_Manager= NULL;
void setManager(CManager *pManager)
{
	db_Manager = pManager;
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
		//int reconnect = 1;
		//mysql_options(conn, MYSQL_OPT_RECONNECT, (int *)&reconnect);
		mysql_real_connect(conn, m_strServerName, m_strUserName, m_strPassword, m_strDBName, port, NULL, 0);
		mysql_set_character_set(conn, "utf8"); //// 本程序是以utf8字符集连接到MYSQL数据库,前提是数据库utf8编码
		conn->reconnect=1;
	}

	return true;

}

//unix_timestamp()，返回自1970-1-1 0:00:01开始到当前系统时间为止的秒数。
//from_unixtime(unixtime)
//time_t
//It is almost universally expected to be an integral value representing 
//the number of seconds elapsed since 00:00 hours, Jan 1, 1970 UTC. 
//This is due to historical reasons, since it corresponds to a unix timestamp,
// but is widely implemented in C libraries across all platforms.
////////////////////////


bool deleteOuttimeInfoItem(INFO_MAP * mapinfo)
{
	//db_Manager->EnterCriticalSection_infoMap();
	
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
	//db_Manager->LeaveCriticalSection_infoMap();

	return true;
}
////////////////////////
MYSQL_RES * getResult(MYSQL *conn,const char* sqlstr,bool *boolresult)
{

	switch(	mysql_query(conn, sqlstr))
	{
	case CR_COMMANDS_OUT_OF_SYNC:
		DEBUGOUT("CR_COMMANDS_OUT_OF_SYNC");
		//break;
	case CR_SERVER_GONE_ERROR:
		DEBUGOUT("CR_SERVER_GONE_ERROR");
		//break;
	case CR_SERVER_LOST:
		DEBUGOUT("CR_SERVER_LOST");
		//break;
	case CR_UNKNOWN_ERROR:
		DEBUGOUT("CR_SERVER_LOST");
		*boolresult=false;
		break;
	default:
		break;
	}

	return mysql_store_result(conn);

}
///////////////////////////////////////////////////////unix_timestamp is time_t
bool updateInfoMap(INFO_MAP * mapinfo,MYSQL_RES *sql_res)
{
	MYSQL_ROW row;
	Cinfo * info=NULL;
	INFO_MAP::iterator it=NULL;

	string stitle("0");
	string sinfo("0");
	string scmd("0");
	string ssendid("000000000000");
	string ssendcount("0");

	while ((row = mysql_fetch_row(sql_res)))
	{
		if (NULL!=row[1])
		{
			stitle =row[1];
		}
		else
		{
			stitle ="null";
		}
		if (NULL!=row[2])
		{
			sinfo = row[2];
		}
		else
		{
			sinfo = "null";
		}
		if (NULL!=row[3])
		{
			scmd = row[3];
		}
		else
		{
			scmd = "null";
		}
		if (NULL!=row[6])
		{
			ssendcount = row[6];
		}
		else
		{
			ssendcount ="0";
		}

		ssendid  = trim_BLANK(row[0]);  
		//db_Manager->EnterCriticalSection_infoMap();
		it= mapinfo->find(ssendid); 
		if (it == mapinfo->end() )
		{
			info=NULL;
#ifdef _DEBUG		
			char debuginfo[500];
			memset(debuginfo,0,sizeof(debuginfo));
			sprintf(debuginfo,"[log][loaddb]send_id=%s,cmd=%s,title=%s\n",ssendid.c_str(),scmd.c_str(),stitle.c_str());
			writelogimmediatly(debuginfo);
#endif
			//Cinfo(char* mtitle,char* minfo,char* mcmd,time_t start,time_t stop,char* sendid,UINT sendcount)
			info=new Cinfo(stitle.c_str(),sinfo.c_str(),scmd.c_str(), (time_t)atoi(row[4]), (time_t)atoi(row[5]),ssendid.c_str(),atoi(ssendcount.c_str())); 
			if (info)
			{
                //从数据库中查询到的数据始终应该比内存中的新
				mapinfo->insert(pair<string, Cinfo*>(ssendid,info));	//<id,info>	//必须有序	
				
			}
			else
			{				
				string errstr("[exception][loaddb]mysql err[");
				errstr+=mysql_error(conn);	
				errstr+="]\n";
				writelogimmediatly(errstr.c_str());
				throw exception("[newerror]");
			}		
		}		
		else
		{
			it->second->cmd        = scmd;
			it->second->expired    = (time_t)atoi(row[5]);
			it->second->info       = sinfo;
			it->second->send_count = atoi(ssendcount.c_str());
			it->second->send_id    = ssendid;
			it->second->starttime  = (time_t)atoi(row[4]);
			it->second->title      = stitle;
		}
		//db_Manager->LeaveCriticalSection_infoMap();
		
	}
	
	mysql_free_result(sql_res);

	return true;
}
///////////////////////////////////////////////////////////////////////////
bool updateRegDeviceMap(REGDEVICE_MAP *pregdev,MYSQL_RES *sql_res)
{

	MYSQL_ROW row;   //device_token, UNIX_TIMESTAMP(reg_time_t),id ,sended_id
	CRegDevice *p=NULL;
	
	REGDEVICE_MAP::iterator it=NULL;

	string stoken("0");
	string timet("0");
	string suid("0");
	string sendedid("0");

	while ((row = mysql_fetch_row(sql_res)))
	{
		if (NULL!=row[0])
		{
			stoken = row[0];
		}
		else
		{
			stoken="null";
		}
		if (NULL!=row[1])
		{
			timet = row[1];
		}
		else
		{
			timet ="0";
		}
		if (NULL!=row[2])
		{
			suid = row[2];
		}
		else
		{
			suid ="0";
		}
		if (NULL!=row[3])
		{
			sendedid = row[3];
		}
		else
		{
			sendedid ="000000000000";
		}
		{

		  CAutoLock Lock(db_Manager->get_regdevmap_CS());
		
			it = pregdev->find(stoken);
			if (it == pregdev->end())
			{
				p=NULL;
#ifdef _DEBUG		
				char debuginfo[500];
				memset(debuginfo,0,sizeof(debuginfo));
				sprintf(debuginfo,"[log][loaddb]stoken=%s,suid=%s,sendedid=%s,timet=%s\n",stoken.c_str(),suid.c_str(),sendedid.c_str(),timet.c_str());
				writelogimmediatly(debuginfo);
#endif
				//CRegDevice(char* stoken,UINT uid, time_t reg_timestamp,const char* sended_id)
				p= new CRegDevice(stoken.c_str(),(UINT)atol(suid.c_str()),(time_t)atol(timet.c_str()),sendedid.c_str());
				if (NULL!=p)
				{				
					pregdev->insert(pair<string,CRegDevice*>(stoken,p));//	
				}
			}
			
		}
		++it;
	}
	mysql_free_result(sql_res);

	return true;
}
///////////////////////////////////////////////////////////////////////////
#ifdef UNREG_MAN
bool updateUnRegDeviceMap(UNREGDEVICE_MAP *punregdev,MYSQL_RES *sql_res)
{
	MYSQL_ROW row;
	CDevice *p=NULL;
	UNREGDEVICE_MAP::iterator it = NULL;

	while ((row = mysql_fetch_row(sql_res)))//device_token,UNIX_TIMESTAMP(times)
	{
		if (row[0] && row[1])
		{
			CAutoLock Lock(db_Manager->get_unregdevmap_CS())
			
			it = punregdev->find(string(row[0]));
			if (it == punregdev->end())
			{
				p=NULL;
				//CDevice(const char*stoken, time_t st)
				p= new CDevice(row[0],(time_t)atol(row[1]));
				if (NULL!=p)
				{				
					punregdev->insert(pair<string,CDevice*>(row[0],p));//	
				}
			}
			
			
		}
	}
	mysql_free_result(sql_res);

	return true;
}
#endif
#ifdef REMEMBER_STATUS  
///////////////////////////////////////////////////////////////////////
///发送状态只有一条记录
bool  updateSendStatus(CSendStatus *pstatus,MYSQL_RES *sql_res)
{
	MYSQL_ROW row;
	if ((row = mysql_fetch_row(sql_res)))//push_msg_id, relation_id
	{
		if (row[0] && row[1])
		{
		
			UINT devid = (UINT)atol(row[1]);
			string infoid= row[0];
			CAutoLock Lock(db_Manager->get_sendStatus_CS()); 
		 
			if (pstatus->info_id.compare(infoid)==0 )
			{
				if (pstatus->device_id < devid)
				{
					pstatus->device_id = devid;
				}
			}
			else if (pstatus->info_id.compare(infoid)<0 )
			{
				pstatus->info_id   = infoid;
				pstatus->device_id = 0;
			}
			 
		}
	}
	mysql_free_result(sql_res);

	return true;
}
#endif

/// 
void loaddb(INFO_MAP * mapinfo,REGDEVICE_MAP *pregdev
	#ifdef UNREG_MAN
			,UNREGDEVICE_MAP *punregdev
	#endif
	#ifdef REMEMBER_STATUS 
			,CSendStatus *pstatus
	#endif
			)
{
	try
	{
		//delete outtime info
		deleteOuttimeInfoItem(mapinfo);
        
		if(0 != mysql_ping(conn))
		{			
			string pstr("[error][SQL]");
			pstr+= mysql_error(conn);
			pstr+="\n";
			g_log.log(pstr.c_str(),ERROR_LEVEL);
			return;
		}
		//1//////////////////////////////////////////////////////////////
        ///get info list//开始时间<now && 结束时间>now order by send_id
		
		bool retn;
		char* sqlstr = "SELECT send_id,title,body,link_page_id,UNIX_TIMESTAMP(start_time), \
						 UNIX_TIMESTAMP(stop_time),send_count \
						 FROM hly.Table_BaseInfo_PushMsg \
						 where stop_time>Now() and Now()>start_time \
						 order by send_id;";
#ifdef _DEBUG
		LogExt(ERROR_LEVEL,"[log][loaddb]mysql[%s]\n", sqlstr);
#endif
		MYSQL_RES *sql_res = getResult(conn,sqlstr,&retn);
		
		if(NULL==sql_res)
		{
			g_log.log("[log][SQL]error \n",LOG_LOG_LEVEL);
			return;
		}
		else
		{
			updateInfoMap(mapinfo,sql_res);			
		}
		/////////////////////////////////////////////////////////////////
		//2 : get REGDEVICE_MAP * pregdev//注册设备表

		sqlstr ="SELECT device_token, UNIX_TIMESTAMP(reg_time_t),id,sended_id \
				  FROM  hly.Table_Relation_PushMsg_Mobile_IOS \
				  WHERE is_need_send=TRUE  \
				  order by id;";
#ifdef _DEBUG
		LogExt(ERROR_LEVEL,"[log][loaddb]mysql[%s]\n", sqlstr);
#endif
		sql_res = getResult(conn,sqlstr,&retn);
		
		if(NULL==sql_res)
		{
		}
		else
		{
			updateRegDeviceMap(pregdev,sql_res);			
		}
		/////////////////////////////////////////////////////////////////
		//3//UNREGDEVICE_MAP *punregdev //注销设备表
#ifdef UNREG_MAN
		sqlstr =  "SELECT device_token,UNIX_TIMESTAMP(times) \
					FROM  hly.table_baseinfo_ios_feedback_service ;";
		 
		sql_res = getResult(conn,sqlstr,&retn);
		if(NULL==sql_res)
		{
		}
		else
		{ 
			updateUnRegDeviceMap(punregdev,sql_res);
		}
#endif	
#ifdef REMEMBER_STATUS
		/////////////////////////////////////////////////////////////////
		//4 //get CSendStatus *pstatus、//发送状态
		// push_msg_id:当前发送消息，指向消息表的send_id
		// id ：当前发送id,指向给注册表中的设备id
		sqlstr =  "SELECT push_msg_id, relation_id \
					FROM  hly.table_relation_pushmsg_status;";
		
		sql_res = getResult(conn,sqlstr,&retn);
		if(NULL==sql_res)
		{
		}
		else
		{ 
			updateSendStatus(pstatus,sql_res);
		}
#endif
	}
	catch(...)
	{
		writelogimmediatly("[exception][loaddb]!\n");
	}
	return ;
	
	
}
         
bool BBT_DOSQL(const char *psql)
{
	
	if(0!= mysql_query(conn, psql))	
	{
		char buf[16];
		memset(buf,0,sizeof(buf));
		
		string pstr("[error][SQL][");
		pstr+=itoa(time(NULL),buf,10);
		pstr+="][";
		pstr+=psql;
		pstr+="]\n";
		g_log.log(pstr.c_str(),ERROR_LEVEL);

		string errstr("[error][EXEC SQL]err:");
		errstr+=mysql_error(conn);	
		errstr+="\n";
		writelogimmediatly(errstr.c_str());
		return false;
	}
	else
	{
#ifdef _DEBUG
		g_log.log("[log][EXEC SQL]ok\n",LOG_LOG_LEVEL);
#endif
		return true;
	}
}

void BBT_DisConn()
{
#ifdef _DEBUG
	g_log.log("[SQL]mysql close connect.\n",LOG_LOG_LEVEL);
#endif
	if (conn)
	{
		mysql_close(conn);
		conn =NULL;
	}
	
}
