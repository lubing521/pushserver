

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

MYSQL *conn= NULL;

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
////////////////////////
/// 
void loaddb(INFO_MAP * mapinfo,IMEIID_MAP* mapimei)
{
	try
	{
		
		INFO_MAP::iterator it=NULL; 

		if(0 != mysql_ping(conn))
		{			
			string pstr("[error][SQL]");
			pstr+= mysql_error(conn);
			pstr+="\n";
			g_log.log(pstr.c_str(),ERROR_LEVEL);
			return;
		}


        ///get info list//开始时间《now && 结束时间>now order by send_id
		 
		switch(	mysql_query(conn, "SELECT send_id,title,body,link_page_id,UNIX_TIMESTAMP(start_time), \
			                        UNIX_TIMESTAMP(stop_time),send_count FROM hly.Table_BaseInfo_PushMsg \
									where stop_time>Now() and Now()>start_time \
									order by send_id;"))
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
		if(NULL==result)
		{
			return;
		}

		MYSQL_ROW row;
		//int num_fields;
				
		string stitle("0");
		string sinfo("0");
		string scmd("0");
		string ssendid("000000000000");
		string ssendcount("0");

		//num_fields = mysql_num_fields(result);
		
		while ((row = mysql_fetch_row(result)))
		{
			
			if (NULL!=row[1])
			{
				stitle =row[1];
			}
			else
			{
				stitle="null";
			}
			if (NULL!=row[2])
			{
				sinfo = row[2];
			}
			else
			{
				sinfo ="null";
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
				ssendcount = "0";
			}

			ssendid  = trim_BLANK(row[0]);  
			{//auto lock block
				CAutoLock Lock(&g_cs);
				it= mapinfo->find(ssendid);			
				if (it == mapinfo->end() )
				{
					//UTF8  //unix_timestamp is time_t

					//Cinfo(char* mtitle,char* minfo,char* mcmd,time_t start,time_t stop,char* sendid,UINT sendcount)
#ifdef _DEBUG		
					char debuginfo[500];
					memset(debuginfo,0,sizeof(debuginfo));
					sprintf(debuginfo,"[log][loaddb]send_id=%s,cmd=%s,title=%s\n",ssendid.c_str(),scmd.c_str(),stitle.c_str());
					writelogimmediatly(debuginfo);
#endif
					Cinfo * info=new Cinfo(stitle.c_str(),sinfo.c_str(),scmd.c_str(), (time_t)atoi(row[4]), (time_t)atoi(row[5]),ssendid.c_str(),atoi(ssendcount.c_str())); 
					
					if (info)
					{
								
						 //从数据库中查询到的数据始终应该比内存中的新
						mapinfo->insert(pair<string, Cinfo*>(ssendid,info));	//<id,info>	//必须有序	
						
	#ifdef _DEBUG
						LogExt(DEBUG_ONLY_LEVEL,"\n[log][loaddb]mapinfo->insert(%s)\n", ssendid.c_str());
	#endif
					}
					else
					{
						g_log.log("[exception][loaddb]new fail!\n",ERROR_LEVEL);
					
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
		
			}//auto lock block
			
		}
		
		mysql_free_result(result);

		// : get imei -id   list
		switch(	mysql_query(conn, "SELECT imei,push_msg_id FROM  hly.Table_Relation_PushMsg_Mobile;"))
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
		if(NULL==result)
		{
			return;
		}
		
		//num_fields = mysql_num_fields(result);
		
		while ((row = mysql_fetch_row(result)))
		{
			
			mapimei->insert(pair<string, string>(row[0], row[1]));	//<imei,send_id>	//无序	
		}
		mysql_free_result(result);
	
	 
			
	}
	catch(...)
	{		
		g_log.log("[exception][loaddb]!\n",CRITICAL_LEVEL);
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
		pstr+=mysql_error(conn);
		pstr+="\n";
		g_log.log(pstr.c_str(),ERROR_LEVEL);

		return false;
	}
	else
	{
		return true;
	}
}

void BBT_DisConn()
{
	if (conn)
	{
		mysql_close(conn);
		conn = NULL;
	}
}
