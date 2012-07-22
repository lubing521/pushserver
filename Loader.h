// Loader.h: interface for the CLoader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOADER_H__77822550_B09D_4F78_AA21_605877241DE6__INCLUDED_)
#define AFX_LOADER_H__77822550_B09D_4F78_AA21_605877241DE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "sender.h"

class CLoader  : public CCKThread
{
public:
	CLoader();
	virtual ~CLoader();

	void init(CFG* cfg);	
	void start();
	void stop();
	IMEIID_MAP* getImeiIdMap();

	INFO_MAP* mpMapInfo;
	
private:
	static void run( LPVOID lpParam );

	INFO_MAP		minfo;	
	IMEIID_MAP	mapImeiId;
	
};

#endif // !defined(AFX_LOADER_H__77822550_B09D_4F78_AA21_605877241DE6__INCLUDED_)
