// Notify.h : Declaration of the CNotify

#ifndef __NOTIFY_H_
#define __NOTIFY_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CNotify
class ATL_NO_VTABLE CNotify : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CNotify, &CLSID_Notify>,
	public IDispatchImpl<INotify, &IID_INotify, &LIBID_NOTIFICATIONDLLLib>
{
public:
	CNotify()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_NOTIFY)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CNotify)
	COM_INTERFACE_ENTRY(INotify)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// INotify
public:
	STDMETHOD(set_cb)(long* pcb);
	STDMETHOD(stop)(void);
	STDMETHOD(start)(void);
};

#endif //__NOTIFY_H_
