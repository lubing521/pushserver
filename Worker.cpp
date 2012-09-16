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
	writelogimmediatly("[log][CWorker]start.\n");
}

void CWorker::stop()
{
	in_exit_flag = true;
	SetEvent(this->mEvent);
	WaitForSingleObject( this->hthread ,3000);
	CloseHandle(this->mEvent);
	writelogimmediatly("[log][CWorker]stop.\n");
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


//���ԣ�
//1.ʹ��ClientMap���ٽ���������æʱ�����������豸���ʱ���ʱ���𣬸���һ�����ܵ���̫��Ķ�ջ��
//2.��ʹ��ClientMap���ٽ���������ʱ�����ܷ�����һ���Ѿ���free��clientָ�룻���ǻ�õĻر���û�з��ʱ����𣬷���ʱ����Ҳ���ᱻ����
void send_worker(CWorker* p)
{
	////�����ʹ���ٽ���������Ҫ�����쳣���ʣ�

	string currentid("000000000000") ;
	CLIENT_MAP::iterator dev_it   = NULL;
	IMEIID_MAP::iterator imit = NULL;
	INFO_MAP::iterator infoit = NULL;
	INFO_MAP::iterator infoit2 = NULL;
	bool sendedflag =false;
	
// 	#ifdef _DEBUG
// 		char debuginfo[500];
// 	#endif
	char buf[16];

	//send info
	string sql("");
	string onesql("");
					

	try
	{
		dev_it = p->mpclm->getClientMap()->begin();
		while(dev_it != p->mpclm->getClientMap()->end()) 
		{
		
			if (dev_it->second && strlen(dev_it->second->imei)) //client ����,imei��ֵ���������//�����Ѿ�killed,���쳣
			{
 			
				imit = p->mploader->getImeiIdMap()->find(dev_it->first);//����IMEI�Ƿ���imeiID����

				if (imit != p->mploader->getImeiIdMap()->end()) // IMEI-ID���ݱ����Ѿ��м�¼��Ϣ�汾
				{
					currentid = imit->second;
				}
				else  //IMEI-ID���ݱ��л�û�м�¼��������
				{
					//getYYYYMMDD(buf); // �޸Ĺ�����ǰ��û���ڵ���ϢҲҪ������ȥ
					currentid="000000000000";
					p->mploader->getImeiIdMap()->insert(pair<string, string>(dev_it->first,currentid));
				}
				
				sendedflag = false;
				
									
						{//auto lock block								
							CAutoLock Lock(&g_cs);

							infoit= p->mpinfoqueue->begin();
							
							while (infoit != p->mpinfoqueue->end()) //delete outtime info
							{
								if (time(NULL) >= infoit->second->expired)
								{
									delete infoit->second ;
									infoit2 = infoit;
									++infoit2;
									p->mpinfoqueue->erase(infoit);
									infoit= infoit2;
								}
								else
								{
									++infoit;
								}
								
							} 

							infoit= p->mpinfoqueue->begin();									
							
							while(infoit != p->mpinfoqueue->end())
							{	
		// 										#ifdef _DEBUG						
		// 											memset(debuginfo,0,sizeof(debuginfo));
		// 											sprintf(debuginfo,"[log][worker]infoit->first=%s,currentid=%s,cmd=%s,title=%s\n",infoit->first.c_str(),currentid.c_str(),
		// 												infoit->second->cmd.c_str(),infoit->second->title.c_str());
		// 											writelogimmediatly(debuginfo);
		// 										#endif
													
													 
														
														
									//����info��Ҫ�·�
									if (currentid.compare(infoit->first)<0 && infoit->second->starttime <= time(NULL)) //currentid < info.send_id
									{
										sendedflag = true;
										if (dev_it->second)
										{
											string strbk = mkjson(infoit->second);
											dev_it->second->sendback(strbk.c_str(),strbk.length());
											infoit->second->send_count++;
											currentid = infoit->first;
											
											//update send_count
											memset(buf,0,sizeof(buf));
											
											onesql="update hly.table_baseinfo_pushmsg set send_count='";
											onesql.append(itoa(infoit->second->send_count,buf,10));
											onesql.append("' where send_id='");
											onesql.append(infoit->second->send_id);
											onesql.append("';");
											BBT_DOSQL(onesql.c_str());
											//sql.append(onesql);
										}
										
									}
									
									++infoit;
							}
												 
						}//end auto lock block
									
						//��Ϣ������Ҫ������Ӧ���ݿ��
						if (!sendedflag) ///û�з��͹���Ϣ��send back "{"statuscode":"0"}"
						{
							string strbk = mkjson(NULL);
							if (dev_it->second)
							{
								dev_it->second->sendback(strbk.c_str(),strbk.length());
							}
						}
						else  
						{    

							// update IMEI-ID
							imit = p->mploader->getImeiIdMap()->find(dev_it->first);
							if(imit != p->mploader->getImeiIdMap()->end())
							{
								imit->second = currentid;
// 							#ifdef _DEBUG
// 								memset(debuginfo,0,sizeof(debuginfo));
// 								sprintf(debuginfo,"[log][worker 3]update ImeiIdMap<%s,%s>\n",dev_it->first.c_str(),imit->second.c_str());
// 								g_log.log(debuginfo,LOG_LOG_LEVEL);
// 							#endif
							}
							
							// ���µ�ǰimei id ���ݿ��//Ҫ��imei��key����Ψһ��
							onesql = "insert into hly.Table_Relation_PushMsg_Mobile (push_msg_id,imei) values('";
							onesql.append(currentid);
							onesql.append("','");
							onesql.append(dev_it->first);
							onesql.append("') ON DUPLICATE KEY UPDATE push_msg_id='");
							onesql.append(currentid);
							onesql.append("';");
						
							if (sql.length()>512)
							{
								BBT_DOSQL(sql.c_str());
								sql="";
							}
							else
							{
								sql.append(onesql);
							}
							
							onesql="";
							
						}

						//�����Ѿ�killed,���쳣
						if (dev_it->second)
						{
							dev_it->second->delay_time = time(NULL);
							dev_it->second = NULL;
						}
										
			
				}
				
				++dev_it; //next client
			}//all client over	
			if (!sql.empty())
			{
				BBT_DOSQL(sql.c_str());
				sql="";
			}
	}
	catch(...)
	{

		if (!sql.empty())
		{
			BBT_DOSQL(sql.c_str());
			sql="";
		}
		printexception(__FILE__,__LINE__,"[worker][exception I know]\n");
	}	

}


//send info to imei
//update imei' infoid
void CWorker::run( LPVOID lpParam )
{
	DWORD dwResult = 0 ;
	CWorker* p = static_cast<CWorker*>(lpParam) ;
	
	
	while(!allExitFlag )
	{
		dwResult = WaitForSingleObject(p->mEvent, 15000);
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
					send_worker(p)	;
					
				}
				
			}
			else //if (WAIT_TIMEOUT == dwResult) 
			{				
				send_worker(p)	;
			}
		}
		else
		{
			CloseHandle(p->mEvent);
			break;
		}
	}
#ifdef _DEBUG
	DEBUGOUT("[log][CWorker]run exit\n");
	LogExt(WARNNING_LEVEL,"[log][CWorker]run Thread exit ID[0x%0x]\n",GetCurrentThreadId());
#endif
}
