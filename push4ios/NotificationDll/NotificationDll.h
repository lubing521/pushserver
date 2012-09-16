/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Sep 11 11:23:05 2012
 */
/* Compiler settings for F:\hly\PushSubsystem\Notification4IOS\NotificationDll\NotificationDll.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __NotificationDll_h__
#define __NotificationDll_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __INotify_FWD_DEFINED__
#define __INotify_FWD_DEFINED__
typedef interface INotify INotify;
#endif 	/* __INotify_FWD_DEFINED__ */


#ifndef __Notify_FWD_DEFINED__
#define __Notify_FWD_DEFINED__

#ifdef __cplusplus
typedef class Notify Notify;
#else
typedef struct Notify Notify;
#endif /* __cplusplus */

#endif 	/* __Notify_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __INotify_INTERFACE_DEFINED__
#define __INotify_INTERFACE_DEFINED__

/* interface INotify */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_INotify;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9FD8910B-01BF-40F1-B38C-936611C8DFC2")
    INotify : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE start( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE stop( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE set_cb( 
            long __RPC_FAR *pcb) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INotifyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INotify __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INotify __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INotify __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            INotify __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            INotify __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            INotify __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            INotify __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *start )( 
            INotify __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *stop )( 
            INotify __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *set_cb )( 
            INotify __RPC_FAR * This,
            long __RPC_FAR *pcb);
        
        END_INTERFACE
    } INotifyVtbl;

    interface INotify
    {
        CONST_VTBL struct INotifyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INotify_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INotify_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INotify_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INotify_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define INotify_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define INotify_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define INotify_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define INotify_start(This)	\
    (This)->lpVtbl -> start(This)

#define INotify_stop(This)	\
    (This)->lpVtbl -> stop(This)

#define INotify_set_cb(This,pcb)	\
    (This)->lpVtbl -> set_cb(This,pcb)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INotify_start_Proxy( 
    INotify __RPC_FAR * This);


void __RPC_STUB INotify_start_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INotify_stop_Proxy( 
    INotify __RPC_FAR * This);


void __RPC_STUB INotify_stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INotify_set_cb_Proxy( 
    INotify __RPC_FAR * This,
    long __RPC_FAR *pcb);


void __RPC_STUB INotify_set_cb_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INotify_INTERFACE_DEFINED__ */



#ifndef __NOTIFICATIONDLLLib_LIBRARY_DEFINED__
#define __NOTIFICATIONDLLLib_LIBRARY_DEFINED__

/* library NOTIFICATIONDLLLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_NOTIFICATIONDLLLib;

EXTERN_C const CLSID CLSID_Notify;

#ifdef __cplusplus

class DECLSPEC_UUID("A26B7E05-9E4A-4297-8225-5673ACFA22F8")
Notify;
#endif
#endif /* __NOTIFICATIONDLLLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
