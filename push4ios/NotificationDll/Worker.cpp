// Worker.cpp: implementation of the CWorker class.
//// ���͹�����
// 1.����Apple Feedback service����ȡע�����ݣ�����ע���������ڴ�ע��ӳ�䣬����ע��������ڴ�ע��ӳ�䣻
//   ����Apple APNs Service��
//       1�����ݷ���״̬����Ϣӳ����ҵ���ǰ�����·���һ����Ϣ��
//       2����ʱ�����̷߳��ͣ���ʵ�֡�����CPU������ע���豸�ֶΣ�ÿһ��һ���ӷ����̡߳���
//       3�����̸߳�����https���ӣ���ȡpem�ļ�������Ϣ���payload������ظ��豸����֪ͨ��
//       4��������ɣ��ͷ����̣߳�  
// 2.���Ž׶�ʵ�֡����豸�ֶδ�������������
// 3.����sql���д���ݿ��Ч��
// 4.sql ��־���ظ���־
//// author: ������ 2012.8   87895224@QQ.com
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "client.h"
#include "ClientManager.h"
#include "Loader.h"
#include "Manager.h"
#include "Worker.h"
#include "db.h"

#include "openssl/err.h"

typedef  unsigned char uint8_t;
typedef  unsigned short uint16_t;
typedef  unsigned int uint32_t;

#define FEEDBUFLEN 4*1024
#define DEVICE_BINARY_SIZE 32
#define MAXPAYLOAD_SIZE 256
extern CFG	g_cfg;
extern Clog g_log;

string mkjson(Cinfo* pin);
bool IsSandBox();
int SSL_connect(SSL *ssl);
int SSL_read(SSL *ssl, void *buf, int num);
int SSL_write(SSL *ssl, const void *buf, int num);
//#define CHK_NULL(x) if ((x)==NULL) setallthreadexitflag()
//#define CHK_ERR(err,s) if ((err)==-1) { /*perror(s);*/ setallthreadexitflag(); }
//#define CHK_SSL(err) if ((err)==-1) { /*ERR_print_errors_fp(stderr);*/ setallthreadexitflag(); }
//////////////////////////////////////////////////////////////////////
// Construction/Destruction 
//////////////////////////////////////////////////////////////////////

CWorker::CWorker():mpclm(NULL),mpinfoqueue(NULL),mpManager(NULL)
{	
	memset(&apns,0,sizeof(APP_SERVER));
	memset(&feed,0,sizeof(APP_SERVER));
	
	SSL_library_init(); 
	SSL_load_error_strings();
	SSLeay_add_ssl_algorithms();
	

}

CWorker::~CWorker()
{
	stop();	
}

void CWorker::init(CClientManager* pclm, CManager * pmg)
{
	this->mpclm = pclm;
//	this->mpinfoqueue = pmg->p_minfo;
	this->mpManager = pmg;
	if (IsSandBox())
	{
		feed.pemfile = g_cfg.sandbox_pem_file.c_str();	 
		apns.pemfile = g_cfg.sandbox_pem_file.c_str();
	}
	else
	{
		feed.pemfile = g_cfg.pem_file.c_str();
		apns.pemfile = g_cfg.pem_file.c_str();

	}
}

bool CWorker::verifyServer(APP_SERVER *ptserver)
{
	/* Following two steps are optional and not required for
     data exchange to be successful. */

	/* Set for server verification*/
	SSL_CTX_set_verify(ptserver->psslctx,SSL_VERIFY_PEER,NULL);

	/* Get the cipher - opt */
#ifdef _DEBUG
	LogExt(LOG_LOG_LEVEL,"SSL connection using %s\n", SSL_get_cipher(ptserver->ssl));
#endif
	/* Get server's certificate (note: beware of dynamic allocation) - opt */

	ptserver->server_cert = SSL_get_peer_certificate (ptserver->ssl);       
	if (!ptserver->server_cert) 
	{
		writelogimmediatly("[exception]SSL_get_peer_certificate \n");
		setallthreadexitflag();
		return false;
	}
#ifdef _DEBUG
	LogExt(LOG_LOG_LEVEL,"Server certificate:\n");
#endif
	char*  str = X509_NAME_oneline (X509_get_subject_name (ptserver->server_cert),0,0);
	if (!str) 
	{
		writelogimmediatly("[exception]X509_NAME_oneline\n");
		setallthreadexitflag();
		return false;
	}

#ifdef _DEBUG
	LogExt(LOG_LOG_LEVEL,"\t subject: %s\n", str);
//subject: /C=US/ST=California/L=Cupertino/O=Apple Inc./OU=iTMS Engineering/CN=gateway.sandbox.push.apple.com
//issuer: /C=US/O=Entrust, Inc./OU=www.entrust.net/rpa is incorporated by reference/OU=(c) 2009 Entrust, Inc./CN=Entrust Certification Authority - L1C
#endif

	OPENSSL_free (str);

	str = X509_NAME_oneline (X509_get_issuer_name(ptserver->server_cert),0,0);
	if (!str) 
	{
		writelogimmediatly("[exception]X509_NAME_oneline.\n");
		setallthreadexitflag();
		return false;
	}

#ifdef _DEBUG
	LogExt(LOG_LOG_LEVEL,"\t issuer: %s\n", str);
#endif

	OPENSSL_free (str);

	/* We could do all sorts of certificate verification stuff here before
	 deallocating the certificate. */

	X509_free (ptserver->server_cert);

	return true;
}
bool CWorker::caVerify(APP_SERVER *ptserver)
{
	/* define HOME to be dir for key and certificate files... */
	//#define HOME "/certs/"
	/* Make these what you want for certificate & key files */
	#define CERT_FILE  ptserver->pemfile   ///// HOME "1024ccert.pem"
	#define KEY_FILE   ptserver->pemfile
		
		/*Cipher list to be used*/
	#define CIPHER_LIST "AES128-SHA"
		
		/*Trusted CAs location*/
	#define CA_FILE  ptserver->pemfile   ////"/certs/1024ccert.pem"
	#define CA_DIR  NULL
	
	/*Set cipher list*/
	if (SSL_CTX_set_cipher_list(ptserver->psslctx,CIPHER_LIST) <= 0) 
	{
		writelogimmediatly("[exception][CWorker][SSL]Error setting the cipher list.\n");
	    setallthreadexitflag();
		return false ;
	}

	/*Indicate the certificate file to be used*/

string pathfile=getExePath();
    pathfile+="\\";
	pathfile+=ptserver->pemfile;
	if (SSL_CTX_use_certificate_file(ptserver->psslctx, pathfile.c_str(), SSL_FILETYPE_PEM) <= 0) 
	{

		string errstr("[err][SSL]Error setting the certificate file");
		const char * pc=ERR_reason_error_string(ERR_get_error());
		errstr.append(pc?pc:"!\n");
		errstr.append("\n");
		writelogimmediatly(errstr.c_str() );

		setallthreadexitflag();
		return false;
	}


	/*Load the password for the Private Key*/
	SSL_CTX_set_default_passwd_cb_userdata(ptserver->psslctx, (void*)g_cfg.pem_psw.c_str());

	pathfile=getExePath();
	pathfile+= "\\";
	pathfile+=KEY_FILE;
	/*Indicate the key file to be used*/
	if (SSL_CTX_use_PrivateKey_file(ptserver->psslctx, pathfile.c_str(), SSL_FILETYPE_PEM) <= 0) 
	{
		writelogimmediatly("[exception][CWorker][SSL]Error setting the key file.\n");
		setallthreadexitflag();
		return false;
	}

	/*Make sure the key and certificate file match*/
	if (SSL_CTX_check_private_key(ptserver->psslctx) == 0) {
		writelogimmediatly("[log][CWorker][SSL]Private key does not match the certificate public key\n");
		setallthreadexitflag();
		return false;
	}

	/* Set the list of trusted CAs based on the file and/or directory provided*/
	pathfile=getExePath();
	pathfile+= "\\";
	pathfile+=CA_FILE;
	if(SSL_CTX_load_verify_locations(ptserver->psslctx, pathfile.c_str(), CA_DIR)<1) {
		writelogimmediatly("[log][CWorker][SSL]Error setting verify location\n");
		setallthreadexitflag();
		return false;
	}

	return true;

}

bool CWorker::nonblock_connect(int sd,struct sockaddr_in &sa,const char *hostname,int port)
{
	int ul = 1;

#ifdef NONEBLOCK_SOCKET

    if(ioctlsocket(sd, FIONBIO, (unsigned long*)&ul)==SOCKET_ERROR)////������ģʽ
    {
		return false;
	}

#else

	int timeout = 200; //ms
	int res = setsockopt(sd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,sizeof(timeout));
	if(SOCKET_ERROR == res ) return false;
	 
	int res = setsockopt(sd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,sizeof(timeout));
	if(SOCKET_ERROR == res) return false;

#endif

	memset (&sa, '\0', sizeof(sa));
	sa.sin_family      = AF_INET;
	string ip(GetIPbyHostName(hostname)); ///getaddrinfo()
	sa.sin_addr.s_addr = inet_addr (ip.c_str());  
	sa.sin_port        = htons     (port);        
	
#ifdef NONEBLOCK_SOCKET
    /////
	fd_set fdw,fde;
	
	FD_ZERO( &fdw );
	FD_ZERO( &fde );
	FD_SET( sd, &fdw );
	FD_SET( sd, &fde );
	
	struct timeval tv;
	
	// block for 10 ms to keep from eating up all cpu time          
	tv.tv_sec = 0;
	tv.tv_usec = 350000;
	
	int retsoc=0;
	
	int err = connect(sd, (struct sockaddr*) &sa,sizeof(sa));
	
	if(SOCKET_ERROR == err)
	{  
		switch(	WSAGetLastError())
		{
		case WSAEWOULDBLOCK:
		
			err = connect(sd, (struct sockaddr*) &sa,sizeof(sa));
			//getpeername
			while(1)
			{
				retsoc=select( NULL, NULL,&fdw,&fde, &tv );
				
				if(0==retsoc)    //TIMEOUT
				{
					continue;
				}
				else if(0<retsoc)
				{
					int error = 0;      
					int sz = sizeof(error); /* even if we get -1 */
					int code =0; 
					if( FD_ISSET( sd, &fdw ) ) ////�жϾ����д�����ܴ��������ӳɹ���
					{ 	
						code = getsockopt(sd,SOL_SOCKET,SO_ERROR,(char *)&error, &sz);
						if ((code < 0) || error) 
						{
							return false;							
						}
						else
						{
							return true;
						}
					} 
					else if (FD_ISSET( sd, &fde ))//exception
					{
						return false;
					}
					else
					{
						continue;	
					}
					
				}
				else
				{
					return false;
				}
			} 
			break;
		default:
			return false;
		}
		 			
		 			 
	} 
#else
	int err = connect(sd, (struct sockaddr*) &sa,sizeof(sa));
	
	if(SOCKET_ERROR == err)
	{
		writelogimmediatly("[err][connectToServer]connect Error\n");
		return false;
	}
#endif
	// 	if(SOCKET_ERROR == ptserver->err)
	
	return true;
}
bool CWorker::connectToServer(const char *hostname,int port,APP_SERVER *ptserver)
{
#ifdef _DEBUG
	writelogimmediatly("connectToServer start\n");
#endif

	//set client using SSL version
	ptserver->meth = (SSL_METHOD *)SSLv23_client_method();
	

	//����SSL�����Ļ��� ÿ������ֻ��ά��һ��SSL_CTX�ṹ��
	ptserver->psslctx = SSL_CTX_new (ptserver->meth);
	if(!ptserver->psslctx)
	{
	   writelogimmediatly("[err]SSL_CTX_new: NULL\n");
	   //LogExt(LOG_LOG_LEVEL,"Error: %s\n", ERR_reason_error_string(ERR_get_error()));
	   return false;
	}

	caVerify(ptserver);	
	/* ----------------------------------------------- */
	/* Create a socket and connect to server using normal socket calls. */
	
	ptserver->sd = socket (AF_INET, SOCK_STREAM, 0);       
	if(SOCKET_ERROR == ptserver->sd)
	{
		writelogimmediatly("[err][connectToServer]socket\n");
		return false;
	}

    if(!nonblock_connect(ptserver->sd,ptserver->sa,hostname,port))
	{
		return false;
	}
	
	/* ----------------------------------------------- */
	/* Now we have TCP conncetion. Start SSL negotiation. */
	ptserver->ssl = SSL_new (ptserver->psslctx);  
	if(!ptserver->ssl)
	{	
		string errstr("[err][SSL_new]");
		const char * pc=ERR_reason_error_string(ERR_get_error());
		errstr.append(pc?pc:"fail!\n");		
		writelogimmediatly(errstr.c_str() );
		return false;
	}
	SSL_set_fd (ptserver->ssl, ptserver->sd);
	SSL_set_mode(ptserver->ssl, SSL_MODE_AUTO_RETRY);

#ifdef NONEBLOCK_SOCKET

CONN_RE:

	ptserver->err = SSL_connect (ptserver->ssl); 
	if(1 == ptserver->err)
	{
#ifdef _DEBUG
		LogExt(LOG_LOG_LEVEL,"The TLS/SSL handshake was successfully completed, a TLS/SSL connection has been established.\n");
#endif
	}
	else if(-1 == ptserver->err)
	{		
		ptserver->err = SSL_get_error(ptserver->ssl,ptserver->err);
		if (SSL_ERROR_WANT_READ==ptserver->err || SSL_ERROR_WANT_WRITE==ptserver->err)
		{
			goto CONN_RE;
		}
		string errstr("[err][SSL_connect]fail!\n");
		writelogimmediatly(errstr.c_str() );
		return false;
	}

#else

	ptserver->err = SSL_connect (ptserver->ssl); 
	if(1 == ptserver->err)
	{
		LogExt(LOG_LOG_LEVEL,"The TLS/SSL handshake was successfully completed, a TLS/SSL connection has been established.\n");
	}
	else if(-1 == ptserver->err)
	{		
		string errstr("[err][SSL_connect]");
		const char * pc=ERR_reason_error_string(ERR_get_error());
		errstr.append(pc?pc:"fail!\n");
		writelogimmediatly(errstr.c_str() );
		return false;
	}
#endif
	// ���֤���Ƿ���Ч 
	//20 X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY: unable to get local issuer certificate
	//	the issuer certificate could not be found: this occurs if the issuer certificate of an untrusted certificate cannot be found.

	int ret_ssl=0;
	if(X509_V_OK !=  ( ret_ssl=SSL_get_verify_result(ptserver->ssl)))
	{
		LogExt(LOG_LOG_LEVEL,"SSL_get_verify_result =>%d\n",ret_ssl);
	}
	
	return true;
}
bool CWorker::connectToFeedbackSandBoxServer()
{	
	bool ret = connectToServer(g_cfg.feedback_sandbox_www.c_str(),g_cfg.feedback_sandbox_port,&this->feed);
	if (ret)
	{
		verifyServer(&this->feed);
	}

	return ret;
}
bool CWorker::connectToFeedbackServer()
{
	bool ret = connectToServer(g_cfg.feedback_www.c_str(),g_cfg.feedback_port,&this->feed);
	if (ret)
	{
		verifyServer(&this->feed);
	}

	return ret;
}
bool CWorker::connectToAPNsSandBox()
{
	bool ret =connectToServer(g_cfg.APNs_sandbox_www.c_str(),g_cfg.APNs_sandbox_port,&this->apns);
	if (ret)
	{
		verifyServer(&this->apns);
	}
	return ret;
}
bool CWorker::connectToAPNs()
{		
	bool ret =connectToServer(g_cfg.APNs_www.c_str(),g_cfg.APNs_port,&this->apns);
	if (ret)
	{
		verifyServer(&this->apns);
	}
	return ret;
}

bool CWorker::UpdateSendCount(string &sendid,UINT sendcount)
{
	bool ret =true;
	char buf[20];
	memset(buf,0,sizeof(buf));
	
	string sql="update hly.table_baseinfo_pushmsg set send_count='";
	sql.append(itoa(sendcount,buf,10));
	sql.append("' where send_id='");
	sql.append(sendid);
	sql.append("';");
											 
	if(!BBT_DOSQL(sql.c_str()))
	{
		ret = false;				
	}

	return ret;
}

bool CWorker::UpdateSendIDRegMap(string &token,string &sendid,UINT curid)
{
	bool ret =true;
	char buf[20];
	memset(buf,0,sizeof(buf));

	LogExt(LOG_LOG_LEVEL,"[log][APNS]okto[%s,%s]\n",token.c_str(),sendid.c_str());
	

	string sql("update hly.table_relation_pushmsg_mobile_ios set sended_id='");
	sql+= sendid;
	sql+="' where id='";
	sql+=itoa(curid,buf,10);
	sql+="';";
	if(!BBT_DOSQL(sql.c_str()))
	{
		ret = false;
	}

	//����regDevMap
	mpManager->EnterCriticalSection_regDevMap();
	REGDEVICE_MAP::iterator reg_it = mpManager->get_p_regDeviceMap()->find(token) ;
	if (reg_it != mpManager->get_p_regDeviceMap()->end())
	{
		reg_it->second->m_sended_id =sendid;
	}
	mpManager->LeaveCriticalSection_regDevMap();

	return ret;
}


//����һ���õ���feedback����
bool  CWorker::readFeedbackUpdateSendStatus(UINT timet,string token)
{
	char buf[20];
	memset(buf,0,sizeof(buf));

#ifdef UNREG_MAN
	
	//����regDevMap
	mpManager->EnterCriticalSection_regDevMap();
	REGDEVICE_MAP::iterator reg_it = mpManager->get_p_regDeviceMap()->find(token) ;
	if (reg_it != mpManager->get_p_regDeviceMap()->end())
	{
		mpManager->get_p_regDeviceMap()->erase(reg_it);
		mpManager->LeaveCriticalSection_regDevMap();

		sqlstr ="update hly.Table_Relation_PushMsg_Mobile_IOS \
			set is_need_send ='false', reg_time_t='";
		sqlstr.append(itoa(timet,buf,10));
		sqlstr.append("' where device_token='");
		sqlstr.append(token);
		sqlstr.append("';");
		sqlstr.append("insert into hly.table_baseinfo_ios_feedback_service (device_token,times) \
			values('");
		sqlstr.append(token);
		sqlstr.append("','");
		sqlstr.append(buf);
		sqlstr.append("') ON DUPLICATE KEY set times='");
		sqlstr.append(buf);
		sqlstr.append("';");

		BBT_DOSQL(sqlstr.c_str());

		mpManager->EnterCriticalSection_unregDevMap();
		UNREGDEVICE_MAP::iterator unreg_it = mpManager->get_p_unregDeviceMap()->find(token);
		if (unreg_it == mpManager->get_p_unregDeviceMap()->end())//��ע���豸
		{
			//����unregDevMap		
			mpManager->get_p_unregDeviceMap()->insert(pair<string,CDevice*>(token,new CDevice(token.c_str(),timet)));
			mpManager->LeaveCriticalSection_unregDevMap();
		}
		else
		{
			mpManager->LeaveCriticalSection_unregDevMap();
		}
	}
	else
	{
		mpManager->LeaveCriticalSection_regDevMap();
	}

#else
	
	
	string sqlstr ="";

	//����regDevMap
	mpManager->EnterCriticalSection_regDevMap();
	REGDEVICE_MAP::iterator reg_it = mpManager->get_p_regDeviceMap()->find(token) ;
	if (reg_it != mpManager->get_p_regDeviceMap()->end())
	{
		mpManager->get_p_regDeviceMap()->erase(reg_it);
		mpManager->LeaveCriticalSection_regDevMap();
		sqlstr ="update hly.Table_Relation_PushMsg_Mobile_IOS \
			set is_need_send ='false', reg_time_t='";
		sqlstr.append(itoa(timet,buf,10));
		sqlstr.append("' where device_token='");
		sqlstr.append(token);
		sqlstr.append("';");
		BBT_DOSQL(sqlstr.c_str());
	}
	else
	{
		mpManager->LeaveCriticalSection_regDevMap();
	}

#endif
	return true;
}
//[time_t][tokenlen][token]
//  4bytes  2bytes    32bytes
//bigendian
char *  CWorker::parseFeedBuf(char * buf,int* plen)
{
	#define TIMET_LEN 4
    #define TOKEN_LEN 2

	assert(plen!=NULL);

	char * mbuf = buf;
	int len= strlen(mbuf);
	UINT timet;
	char ptoken[2*DEVICE_BINARY_SIZE+2];

	while (len>=(DEVICE_BINARY_SIZE+TOKEN_LEN+TIMET_LEN))
	{		
		timet = *((UINT*)mbuf);
        mbuf +=TIMET_LEN+TOKEN_LEN;
		memset(ptoken,0,sizeof(ptoken));
		binarychartoHexchar(mbuf,ptoken,DEVICE_BINARY_SIZE);
		readFeedbackUpdateSendStatus(timet,string(ptoken));
		mbuf +=DEVICE_BINARY_SIZE;
		len-=(DEVICE_BINARY_SIZE+TOKEN_LEN+TIMET_LEN);
	}
	
	*plen = len;
    return mbuf;	
}
//��feedback
void CWorker::readFeedbackSub()
{
	int ret;
	char buf[FEEDBUFLEN+2];
	int len=0;
	char * offset=0;
	char * curbuf= buf;
	bool readloop=true;
	
	while (readloop)
	{
		ret = SSL_pending(feed.ssl);
		memset(curbuf,0,FEEDBUFLEN-(curbuf-buf));
		ret = SSL_read(feed.ssl,curbuf,FEEDBUFLEN-(curbuf-buf));
		ret = SSL_get_error(feed.ssl,ret);
		switch(ret )
		{
		case SSL_ERROR_SSL:
		case SSL_ERROR_SYSCALL:
		case SSL_ERROR_ZERO_RETURN://SSL 3.0 or TLS 1.0
			readloop =  false;
			break;
			
		case SSL_ERROR_WANT_READ:
		case SSL_ERROR_WANT_WRITE:
		case SSL_ERROR_NONE:
		default:
			offset = parseFeedBuf(buf,&len);
			memcpy(buf,offset,len);
			curbuf = buf + len;
			
			break;
		}
		
	}
}
void CWorker::getFeedback()
{
	bool ret = false;
	if ( IsSandBox())
	{
		ret = connectToFeedbackSandBoxServer();	
	}
	else
	{
		ret = connectToFeedbackServer();
	}
	
	//��feedback
	if (ret)
	{
		readFeedbackSub();
	}
		 
	stopSSLFeed();
}

void CWorker::sendtoAPNs()
{
	bool ret = false;
	if ( IsSandBox())
	{
		ret = connectToAPNsSandBox();	
	}
	else
	{
		ret = connectToAPNs();
	}
	
	if (ret)
	{
		//�ҵ���ʼ��һ����Ϣ����ʼ��һ���豸
		string current_info_id("");//send_id char12
		UINT   current_device_id=0;
		string current_device_token("");
		
		StartSend(current_info_id,current_device_token,&current_device_id);
		if (!current_info_id.empty() && !current_device_token.empty() )
		{
			batchSendtoApns(current_info_id,current_device_token,current_device_id);
		}
		
		//
		
	}
	stopSSLApns(); 
	
}

//�ҵ���ʼ��Ϣ����ʼ�豸id��token
void CWorker::StartSend(string &current_info_id,string &current_device_token,UINT*p_current_device_id )
{
#ifdef REMEMBER_STATUS
	//�ҵ�һ����Ϣ

	REGDEVICE_MAP::iterator reg_it   = NULL;
	REGDEVICE_MAP::reverse_iterator reg_rit ;
	UNREGDEVICE_MAP::iterator unreg_it = NULL;
	INFO_MAP::iterator info_it = NULL;
	bool sendedflag = false;
 
	//��鷢����Ϣ״̬
	if(!mpManager->get_p_SendStatus()->info_id.empty())
	{	
		
		//��鵱ǰ��Ϣ�Ƿ����꣺���豸�������id
		mpManager->EnterCriticalSection_regDevMap();
		reg_rit = mpManager->get_p_regDeviceMap()->rbegin();
		if (reg_rit != mpManager->get_p_regDeviceMap()->rend())
		{
			//reg_rit->first ;//device_token
			if (reg_rit->second->m_id > mpManager->get_p_SendStatus()->device_id)//�豸û�з���
			{
				
				reg_it = mpManager->get_p_regDeviceMap()->begin();
				while(reg_it != mpManager->get_p_regDeviceMap()->end())
				{
					if (reg_it->second->m_id == mpManager->get_p_SendStatus()->device_id)
					{
						break;
					}
					++reg_it;
				}
				if (reg_it == mpManager->get_p_regDeviceMap()->end())
				{//error
				}
				else
				{
					++reg_it;
					*p_current_device_id   = reg_it->second->m_id;
					current_device_token= reg_it->second->m_token;
				}				
				current_info_id = mpManager->get_p_SendStatus()->info_id; 
				mpManager->LeaveCriticalSection_regDevMap();
			}
			else
			{  
				mpManager->LeaveCriticalSection_regDevMap();

				//��Ϣ�Ѿ����������豸������һ������
				//mpManager->EnterCriticalSection_infoMap();
				info_it = mpManager->get_p_minfo()->find(mpManager->get_p_SendStatus()->info_id);
				if(info_it != mpManager->get_p_minfo()->end())
				{
					++info_it;
					if(info_it != mpManager->get_p_minfo()->end())
					{
						current_info_id = info_it->first;
					}
				}				
				//mpManager->LeaveCriticalSection_infoMap();

				if (!current_info_id.empty())
				{
					//����״̬
					mpManager->get_p_SendStatus()->info_id =current_info_id;
					mpManager->get_p_SendStatus()->device_id =0;	
					//��һ���豸
					mpManager->EnterCriticalSection_regDevMap();
					reg_it = mpManager->get_p_regDeviceMap()->begin();
					if(reg_it != mpManager->get_p_regDeviceMap()->end())
					{
						*p_current_device_id   = reg_it->second->m_id;
						current_device_token= reg_it->second->m_token;
					}
					mpManager->LeaveCriticalSection_regDevMap();
				}	
			}
		}
		else
		{
			mpManager->LeaveCriticalSection_regDevMap();
		}
				
	}
	else
	{ //״̬Ϊ�ռ���һ��ʹ��
		//��һ����Ϣ
		//mpManager->EnterCriticalSection_infoMap();
		info_it = mpManager->get_p_minfo()->begin();
		if (info_it != mpManager->get_p_minfo()->end())
		{
			current_info_id = info_it->first;//send_id
		}
		//mpManager->LeaveCriticalSection_infoMap();

		if (!current_info_id.empty())
		{
			//����״̬
			mpManager->get_p_SendStatus()->info_id =current_info_id;
			mpManager->get_p_SendStatus()->device_id =0;	

			//��һ���豸
			mpManager->EnterCriticalSection_regDevMap();
			reg_it = mpManager->get_p_regDeviceMap()->begin();
			if(reg_it != mpManager->get_p_regDeviceMap()->end())
			{
				*p_current_device_id   = reg_it->second->m_id;
				current_device_token= reg_it->second->m_token;
			}
			mpManager->LeaveCriticalSection_regDevMap();
		}

	}
#else


	//��һ����Ϣ
	//mpManager->EnterCriticalSection_infoMap();

	INFO_MAP::iterator info_it = mpManager->get_p_minfo()->begin();

	if (info_it != mpManager->get_p_minfo()->end())
	{
		current_info_id = info_it->first;//send_id
	}
	//mpManager->LeaveCriticalSection_infoMap();

	//��һ���豸
	{
		CAutoLock Lock(mpManager->get_regdevmap_CS());
		
		REGDEVICE_MAP::iterator reg_it = mpManager->get_p_regDeviceMap()->begin();

		if(reg_it != mpManager->get_p_regDeviceMap()->end())
		{
			*p_current_device_id   = reg_it->second->m_id;
			current_device_token= reg_it->second->m_token;
		}
	}
#endif
}

// void CWorker::WriteDBUpdateStatus(string &current_info_id,UINT current_device_id)
// {
// 	int ret=0;
// 	mpManager->EnterCriticalSection_sendStatus();
// 	if (0== (ret = mpManager->p_gSendStatus->info_id.compare(current_info_id)) )
// 	{
// 		if (mpManager->p_gSendStatus->device_id < current_device_id)
// 		{
// 			mpManager->p_gSendStatus->device_id = current_device_id;
// 		}
// 	}
// 	else if (0>ret)
// 	{
// 		mpManager->p_gSendStatus->info_id  = current_info_id;
// 		mpManager->p_gSendStatus->device_id = 0;
// 	}
// 	mpManager->LeaveCriticalSection_sendStatus();
// }
void CWorker::batchSendtoApns(string &current_info_id,string &current_device_token,UINT current_device_id)
{

	REGDEVICE_MAP::iterator reg_it   = NULL;
	INFO_MAP::iterator info_it = mpManager->get_p_minfo()->find(current_info_id);
	string spayload("");
	
	bool ret=true;

#ifdef _DEBUG
	char debuginfo[514];
    //current_device_token ="5af91bc1a29b2cd5aaada4f7776b53906c9ccaf651f5f54fa350a2cc8253ee43";
#endif

	char pbinarytoken[DEVICE_BINARY_SIZE+4];

	if (info_it==mpManager->get_p_minfo()->end())
	{
		writelogimmediatly("��ע����Ϣ��λ��Ϣ�����д���\n");
		return;
	}

	{

		CAutoLock Lock(mpManager->get_regdevmap_CS());	
		reg_it = mpManager->get_p_regDeviceMap()->find(current_device_token);
		if (reg_it == mpManager->get_p_regDeviceMap()->end())
		{
			writelogimmediatly("��ע���豸��λ�豸�����д���\n");
			return;
		}
	}
	
	while(info_it != mpManager->get_p_minfo()->end())
	{
		#ifdef _DEBUG	
				
				sprintf(debuginfo,"[log][worker]info.starttime=%d,now=%d,info.send_id=%s,device.sended_id=%s\n",
										info_it->second->starttime,time(NULL),
										info_it->second->send_id.c_str(),reg_it->second->m_sended_id.c_str());
				writelogimmediatly(debuginfo);
		#endif


	#ifdef REMEMBER_STATUS
		if ( info_it->second->starttime < time(NULL))//Ҫ��send_id ��start_time ���򲢱���һ��
	#else
		
	#endif
		{			

			current_info_id	= info_it->second->send_id;
			spayload = mkjson(info_it->second);
		
			//��������ע���豸			
			CAutoLock Lock(mpManager->get_regdevmap_CS());

			while (reg_it != mpManager->get_p_regDeviceMap()->end())
			{
				#ifndef REMEMBER_STATUS
				if ( info_it->second->starttime < time(NULL) && info_it->second->send_id.compare(reg_it->second->m_sended_id)>0)
				{
				#endif
					#ifdef _DEBUG
						sprintf(debuginfo,"[log][worker]will sendto %s\n",reg_it->second->m_token.c_str());
						writelogimmediatly(debuginfo);
					#endif

				
				
					current_device_token = reg_it->second->m_token;
					current_device_id    = reg_it->second->m_id   ;

					memset(pbinarytoken,0,sizeof(pbinarytoken));
					
					Hexchartobinarychar(reg_it->second->m_token.c_str(),pbinarytoken,2*DEVICE_BINARY_SIZE);
					ret = sendPayload(reg_it->second->m_id, pbinarytoken, spayload.c_str(), spayload.length());
					if(! ret )
					{
						writelogimmediatly("[err][worker]��Ϣ����ʧ�ܣ�ԭ��sendPayload����ʧ��!\n");
						break;//fail ,exit device loop
					}
					else
					{
						#ifdef _DEBUG
							writelogimmediatly("[log][worker]��Ϣ����ok!\n");
						#endif
					}

				#ifndef REMEMBER_STATUS
					
					UpdateSendCount(current_info_id,info_it->second->send_count+1);
					UpdateSendIDRegMap(current_device_token,current_info_id,current_device_id);
					
				}
				#endif

				++reg_it;//next device
			}

			if (!ret)
			{
			#ifdef _DEBUG
				writelogimmediatly("[log][worker]��Ϣ����:�˳���Ϣ����!\n");
			#endif
				break;//exit info loop
			}
			else
			{
				reg_it = mpManager->get_p_regDeviceMap()->begin();
				if(reg_it != mpManager->get_p_regDeviceMap()->end())
				{
					current_device_id = reg_it->second->m_id ;
				}
				
			}
			
		}

		#ifdef REMEMBER_STATUS
		else
		{
			break;					
		}
		#endif

		#ifndef REMEMBER_STATUS
		++info_it; //next info
			#ifdef _DEBUG
				writelogimmediatly("[log][worker]��Ϣ����:������Ϣ����!\n");
			#endif
		#endif
	}
	
	#ifdef REMEMBER_STATUS
	//���·���״̬:��¼���һ����Ϣid���豸id�������Ĳ����ٷ���
	//WriteDBUpdateStatus(current_info_id,current_device_id);
	#endif
}


void CWorker::start()
{
	if (INVALID_HANDLE_VALUE == this->mEvent)
	{
		this->creatwork( CWorker::run );
	}
#ifdef _DEBUG
	writelogimmediatly("[log][CWorker]start ok.\n");
#endif
}

void CWorker::stop()
{
	if(INVALID_HANDLE_VALUE != mEvent)
	{
		SetEvent(this->mEvent);
		WaitForSingleObject( this->hthread ,3000);
		CloseHandle(this->mEvent);
		mEvent = INVALID_HANDLE_VALUE;
		
		stopSSLFeed();
		stopSSLApns();
#ifdef _DEBUG
		writelogimmediatly("[log][CWorker]stop.\n");
#endif
	}

}
void CWorker::stopSSLFeed()
{

	if (feed.ssl)
	{
		SSL_shutdown (feed.ssl);  /* send SSL/TLS close_notify */
		
		close (feed.sd);
		SSL_free (feed.ssl);
		SSL_CTX_free (feed.psslctx);
	}
	feed.ssl=NULL;


}
void CWorker::stopSSLApns()
{

	if (apns.ssl)
	{
		SSL_shutdown (apns.ssl);  /* send SSL/TLS close_notify */
		
		close (apns.sd);
		SSL_free (apns.ssl);
		SSL_CTX_free (apns.psslctx);
	}
	apns.ssl=NULL;

}

//�ӿ�Э��
//{"aps":{"alert":"��Ϣ����","sound":"default"},"acme1":"1"}

string mkjson(Cinfo* pin)
{
	if (!pin) return string("");

	string s("{\"aps\":{\"alert\":\"");
	s.append(pin->info);
	s.append("\",\"sound\":\"default\"},\"acme1\":\"");
	s.append(pin->cmd);
	s.append("\"}");

    return s;
}

int parseresponse(const char * presponse)
{
	int ret= *presponse;
	switch(*presponse)	
	{	
	case 0://	No errors encountered
		break;
	case 1: //
		g_log.log("[log][APNs error]Processing error\n",WARNNING_LEVEL);
		break;
	case 2:
		g_log.log("[log][APNs error]Missing device token\n",WARNNING_LEVEL);
		break;
	case 3:
		g_log.log("[log][APNs error]Missing topic\n",WARNNING_LEVEL);
		break;
	case 4:		
		g_log.log("[log][APNs error]Missing payload\n",WARNNING_LEVEL);
		break;
	case 5:
		g_log.log("[log][APNs error]Invalid token size\n",WARNNING_LEVEL);
		break;
	case 6:
		g_log.log("[log][APNs error]Invalid topic size\n",WARNNING_LEVEL);
		break;
	case 7:
		g_log.log("[log][APNs error]Invalid payload size\n",WARNNING_LEVEL);
		break;
	case 8:
		g_log.log("[log][APNs error]Invalid token\n",WARNNING_LEVEL);
		break;
	case 255:
	default:
		g_log.log("[log][APNs error]None (unknown)\n",WARNNING_LEVEL);
		break;
	}
	return ret;

}
//gateway.sandbox.push.apple.com, port 2195
//gateway.push.apple.com, port 2195
//

//[command][identifier][expiry][0 32][devicetoken (binary)][0 ##][payload]
//id is identifier;
//deviceTokenBinary is 32bytechar device token;
//payloadBuff is msg that should be sended.
//
bool CWorker::sendPayload(unsigned int id,const char *deviceTokenBinary,const char *payloadBuff, size_t payloadLength)

{
	bool rtn = false;
	
	if (apns.ssl && deviceTokenBinary && payloadBuff && payloadLength)
	{
		uint8_t command = 1; /* command number */
		char binaryMessageBuff[sizeof(uint8_t) + sizeof(uint32_t) + sizeof(uint32_t) + sizeof(uint16_t) +
								DEVICE_BINARY_SIZE + sizeof(uint16_t) + MAXPAYLOAD_SIZE];
		
		/* message format is, |COMMAND|ID|EXPIRY|TOKENLEN|TOKEN|PAYLOADLEN|PAYLOAD| */
		
		char *binaryMessagePt = binaryMessageBuff;
		uint32_t whicheverOrderIWantToGetBackInAErrorResponse_ID = id;
		uint32_t networkOrderExpiryEpochUTC = htonl(time(NULL)+86400); // expire message if not delivered in 1 day
		uint16_t networkOrderTokenLength = htons(DEVICE_BINARY_SIZE);
		uint16_t networkOrderPayloadLength = htons(payloadLength);
		
		/* command */
		*binaryMessagePt++ = command;
		
		/* provider preference ordered ID */
		memcpy(binaryMessagePt, &whicheverOrderIWantToGetBackInAErrorResponse_ID, sizeof(uint32_t));
		binaryMessagePt += sizeof(uint32_t);
		
		/* expiry date network order */
		memcpy(binaryMessagePt, &networkOrderExpiryEpochUTC, sizeof(uint32_t));
		binaryMessagePt += sizeof(uint32_t);
		
		/* token length network order */
		memcpy(binaryMessagePt, &networkOrderTokenLength, sizeof(uint16_t));
		binaryMessagePt += sizeof(uint16_t);
		
		/* device token */
		memcpy(binaryMessagePt, deviceTokenBinary, DEVICE_BINARY_SIZE);
		binaryMessagePt += DEVICE_BINARY_SIZE;
		
		/* payload length network order */
		memcpy(binaryMessagePt, &networkOrderPayloadLength, sizeof(uint16_t));
		binaryMessagePt += sizeof(uint16_t);
		
		/* payload */
		memcpy(binaryMessagePt, payloadBuff, payloadLength);
		binaryMessagePt += payloadLength;
		if (SSL_write(apns.ssl, binaryMessageBuff, (binaryMessagePt - binaryMessageBuff)) > 0)
		{
			rtn = true;
#ifdef _DEBUG
			writelogimmediatly("[debug out]SSL_write ok!\n");
#endif
			//��鷵�ؽ��
			char buf[24];
			int ret=0;
			int count=0;
			
			memset(buf,0,sizeof(buf));
AGAIN_READ:
			ret=SSL_read(apns.ssl,buf,20);//If there is no error, APNs doesn��t return anything
			ret = SSL_get_error(apns.ssl,ret);
			
	#ifdef _DEBUG
			char tbuf[64];
			sprintf(tbuf,"[err][SSL_read]%d\n",ret);
			writelogimmediatly(tbuf);
	#endif
			switch( ret)
			{
				case SSL_ERROR_NONE:
					ret = parseresponse(buf);
					break;
				case SSL_ERROR_SSL:
					break;
				case SSL_ERROR_SYSCALL:
					break;
				case SSL_ERROR_ZERO_RETURN://SSL 3.0 or TLS 1.0
					break;
				case SSL_ERROR_WANT_READ:
					{					
						if(count>3) break;
						++count;
						goto AGAIN_READ;
					}
				case SSL_ERROR_WANT_WRITE:
					break;
				case SSL_ERROR_WANT_CONNECT:
					break;
				case SSL_ERROR_WANT_ACCEPT:
					break;
				case SSL_ERROR_WANT_X509_LOOKUP:
					break;
				default: //
					ret = parseresponse(buf);
					//rtn = false ; //�κη���ʧ�ܶ��˳����͹���
					break;
			}
			
		}
		else
		{
			string errstr("[err][SSL_write]");
			const char * pc=ERR_reason_error_string(ERR_get_error());
			errstr.append(pc?pc:" fail!\n");
			writelogimmediatly(errstr.c_str() );			 
		}
	}
	#ifdef _DEBUG
	writelogimmediatly( rtn ? "[debug out]sendPayload =>true\n":"[debug out]sendPayload =>false\n");
	#endif
	return rtn;
	
}

//send info to ios APNs
//update imei' infoid
#ifdef _DEBUG
#define DELAY_TIME  60*1000
#else
#define DELAY_TIME  5*60*1000
#endif
void CWorker::run( LPVOID lpParam )
{
	DWORD dwResult = 0 ;
	CWorker* p = (CWorker*) lpParam ;

	while(!allExitFlag )
	{
		dwResult = WaitForSingleObject(p->mEvent, DELAY_TIME);
		if (allExitFlag )
		{
			break;
		}
		if( WAIT_TIMEOUT== dwResult)
		{
			CAutoLock Lock(p->mpManager->get_worker_loader_CS());
			p->getFeedback();
			p->sendtoAPNs();
			
		}
		else  
		{				
			break;
		}
	}
	CloseHandle(p->mEvent);
#ifdef _DEBUG
	LogExt(WARNNING_LEVEL,"[log][CWorker]run Thread exit ID[0x%0x]\n",GetCurrentThreadId());
#endif
}
