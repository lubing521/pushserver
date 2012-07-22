// Worker.cpp: implementation of the CWorker class.
//// ���͹�����
// 1.������ʽ
// 2.��������
// 3.д���ݿ��Ч��
// 4.sql ��־���ظ���־
//// author: ������ 2012.7
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "client.h"
#include "ClientManager.h"
#include "Loader.h"
#include "Worker.h"
#include "db.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction 
//////////////////////////////////////////////////////////////////////

CWorker::CWorker():in_exit_flag(false),mpclm(NULL),mpinfoqueue(NULL),mploader(NULL)
{
}

CWorker::~CWorker()
{

}
void CWorker::init(CClientManager* pclm, CLoader * loader)
{
	this->mpclm = pclm;
	this->mpinfoqueue = loader->mpMapInfo;
	this->mploader = loader;
}
void CWorker::start()
{
	if (INVALID_HANDLE_VALUE == this->mEvent)
	{
		this->creatwork( CWorker::run );
	}
}
void CWorker::stop()
{
	in_exit_flag = true;
	SetEvent(this->mEvent);
	WaitForSingleObject( this->hthread ,3000);
	CloseHandle(this->mEvent);
}
//�ӿ�Э��
//{"statuscode":"1","title":"��Ϣ����","content":"��Ϣ����","cmd":"3"}
//{"statuscode":"0"}
string mkjson(Cinfo* pin)
{
	string s("{\"statuscode\":\"");
	if (pin)
	{
		s.append("1\",\"title\":\"");
		s.append(pin->title);
		s.append("\",\"content\":\"");
		s.append(pin->info);
		s.append("\",\"cmd\":\"");
		s.append(pin->cmd);
		s.append("\"}\r\n");
	} 
	else
	{
		s.append("0\"}\r\n");
	}
    return s;
}


//send info to imei
//update imei' infoid
void CWorker::run( LPVOID lpParam )
{
	DWORD dwResult = 0 ;
	CWorker* p = (CWorker*) lpParam ;
	UINT currentid =0;
	CLIENT_MAP::iterator it   = NULL;
	IMEIID_MAP::iterator imit = NULL;
	INFO_MAP::iterator infoit = NULL;
	bool sendedflag =false;
	bool needinsertdb =false;
	char num[10]={0};

	while(!allExitFlag )
	{
		dwResult = WaitForSingleObject(p->mEvent, INFINITE);
		if (!allExitFlag )
		{
			if(WAIT_OBJECT_0 == dwResult)
			{
				if (p->in_exit_flag) //to exit
				{
					CloseHandle(p->mEvent);
					break;
				}
				else //
				{
					//send info
					string sql("");
					string onesql("");

					it = p->mpclm->getClientMap()->begin();
					while(it != p->mpclm->getClientMap()->end())
					{
						if (it->second) //client ����
						{		
							currentid = 0;
							needinsertdb =false;

							imit = p->mploader->getImeiIdMap()->find(it->first);
							if (imit != p->mploader->getImeiIdMap()->end()) // IMEI-ID���ݱ����Ѿ��м�¼��Ϣ�汾
							{
								currentid = imit->second;								
							}
							else  //IMEI-ID���ݱ��л�û�м�¼��������
							{
								needinsertdb = true;
								p->mploader->getImeiIdMap()->insert(pair<string, UINT>(string(it->second->imei),currentid));
								     
							}

							sendedflag = false;

							EnterCriticalSection(&g_cs);

							infoit= p->mpinfoqueue->begin();	
							

							while(infoit != p->mpinfoqueue->end())
							{																 	
								//����info��Ҫ�·�
								if (infoit->first > currentid)
								{
									sendedflag = true;
									string strbk = mkjson(infoit->second);
									it->second->sendback(strbk.c_str(),strbk.length());
								}
								currentid = infoit->first;
								++infoit;
							}
							LeaveCriticalSection(&g_cs);

							if (!sendedflag) ///no info then send back "{"statuscode":"0"}"
							{
								string strbk = mkjson(NULL);
								it->second->sendback(strbk.c_str(),strbk.length());
							}
							else  
							{    
								// update IMEI-ID
								imit = p->mploader->getImeiIdMap()->find(it->first);
								imit->second = currentid;
								
								// ���µ�ǰimei id ���ݿ��
								
								if (needinsertdb)
								{									
									onesql = "insert into Table_Relation_PushMsg_Mobile (push_msg_id,imei) values('";
									memset(num,0,sizeof(num));
									onesql.append(itoa(currentid,num ,10));
									onesql.append("','");
									onesql.append(it->first);
									onesql.append("');");									
								}
								else
								{
									onesql = "update Table_Relation_PushMsg_Mobile set push_msg_id='";
									onesql.append(itoa(currentid,num,10));
									onesql.append("' where imei ='");
									onesql.append(it->first);
									onesql.append("';");
								}
								LogExt(LOG_LOG_LEVEL,"[sql]%s",onesql.c_str());
								sql.append(onesql);
								onesql.empty();

							}
							//client close
							it->second->Close();							
							it->second = NULL;							
							
						}
						else
						{
							++it;
						}						

					}//all client over	
					
					BBT_DOSQL(sql.c_str());
					sql.empty();

				}
				
			}
			else //if (WAIT_TIMEOUT == dwResult) 
			{				
				g_log.log("[err][event]CWorker::run !",ERROR_LEVEL);
			}
		}
		else
		{
			CloseHandle(p->mEvent);
			break;
		}
	}
}
