// sender.h: interface for the CCKThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SENDER_H__CBEEC053_69A9_4609_B104_EA2B2D8D143B__INCLUDED_)
#define AFX_SENDER_H__CBEEC053_69A9_4609_B104_EA2B2D8D143B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCKThread  
{
public:
	CCKThread();
	virtual ~CCKThread();
	virtual void start();
	virtual void stop();
	virtual void ckSetEvent();
protected:

	HANDLE	mEvent;
	HANDLE  hthread;

protected:
	bool	creatwork(void (__cdecl * run) (void *));
};

#endif // !defined(AFX_SENDER_H__CBEEC053_69A9_4609_B104_EA2B2D8D143B__INCLUDED_)
