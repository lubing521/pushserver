// Clientlog.h: interface for the CClientlog class.
//
//////////////////////////////////////////////////////////////////////


#if !defined(AFX_CLIENTLOG_H__59642F50_84BB_421E_BB71_4FCC1A098856__INCLUDED_)
#define AFX_CLIENTLOG_H__59642F50_84BB_421E_BB71_4FCC1A098856__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Clog  
{
public:
	Clog();
	virtual ~Clog();

private:
	int sockfd;
	int m_sendtimeout;
	int m_recvtimeout;
	int m_port;
	char m_ip[20];
	bool initedflag;
	int m_log_level;
public:
	void close();
	bool log(const char* msg,int loglevel);
	void setloglevel(int loglevel);

private:
	bool Connect();
	bool SetRecvTimeOut(int t);
	bool SetSendTimeOut(int t);
	int  Send(const char *lp , int len );
	int Recv(char*lp, int len);
	bool inicfg();

};

#endif // !defined(AFX_CLIENTLOG_H__59642F50_84BB_421E_BB71_4FCC1A098856__INCLUDED_)
