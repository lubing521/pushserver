// Worker.h: interface for the CWorker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORKER_H__4ED66344_F6A8_44FE_B348_9DE1C3104C57__INCLUDED_)
#define AFX_WORKER_H__4ED66344_F6A8_44FE_B348_9DE1C3104C57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "sender.h"
class CLoader;


class CWorker  : public CCKThread
{
public:
	CWorker();
	virtual ~CWorker();

	void init(CClientManager* pclm , CManager * pmg);
	void start();
	void stop();


	CClientManager* mpclm;
	INFO_MAP * mpinfoqueue;
	CManager * mpManager;

	static void run( LPVOID lpParam );
	
private:
	typedef struct APP_SERVER
	{
		int err;
		int sd;
		struct sockaddr_in sa;
		SSL_CTX *psslctx;
		SSL     *ssl;
		SSL_METHOD	*meth;
		X509		*server_cert;
		const char	* pemfile;	

	};
	APP_SERVER  feed;
	APP_SERVER  apns;
	

	bool connectToServer(const char *IP,int port,APP_SERVER *ptserver);
	bool connectToFeedbackSandBoxServer();
	bool connectToFeedbackServer();
	bool connectToAPNsSandBox();
	bool connectToAPNs();
	void getFeedback();
	
	void sendtoAPNs();
	bool readFeedbackUpdateSendStatus(UINT timet,string token);
	char* parseFeedBuf(char * buf,int* plen);
	void readFeedbackSub();

	bool caVerify(APP_SERVER *ptserver);
	bool verifyServer(APP_SERVER *ptserver);

	void stopSSLFeed();
	void stopSSLApns();
	void batchSendtoApns(string &current_info_id,string &current_device_token,UINT current_device_id);
	bool sendPayload(unsigned int id,const char *deviceTokenBinary,const char *payloadBuff, size_t payloadLength);
	void StartSend(string &current_info_id,string &current_device_token,UINT*p_current_device_id );

	bool nonblock_connect(int sd,struct sockaddr_in &sa,const char *hostname,int port);
	bool UpdateSendIDRegMap(string &token,string &sendid,UINT curid);
	bool UpdateSendCount(string &sendid,UINT sendcount);
};

#endif // !defined(AFX_WORKER_H__4ED66344_F6A8_44FE_B348_9DE1C3104C57__INCLUDED_)
