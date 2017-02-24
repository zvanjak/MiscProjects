
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0280 */
/* at Wed Nov 08 15:08:28 2000
 */
/* Compiler settings for GravitySimulation.odl:
    Os (OptLev=s), W1, Zp8, env=Win32 (32b run), ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __GravitySimulation_h_h__
#define __GravitySimulation_h_h__

/* Forward Declarations */ 

#ifndef __IGravitySimulation_FWD_DEFINED__
#define __IGravitySimulation_FWD_DEFINED__
typedef interface IGravitySimulation IGravitySimulation;
#endif 	/* __IGravitySimulation_FWD_DEFINED__ */


#ifndef __Document_FWD_DEFINED__
#define __Document_FWD_DEFINED__

#ifdef __cplusplus
typedef class Document Document;
#else
typedef struct Document Document;
#endif /* __cplusplus */

#endif 	/* __Document_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __GravitySimulation_LIBRARY_DEFINED__
#define __GravitySimulation_LIBRARY_DEFINED__

/* library GravitySimulation */
/* [version][uuid] */ 


DEFINE_GUID(LIBID_GravitySimulation,0x7D4C0BB8,0xCBC1,0x439C,0x9F,0xC6,0x04,0x27,0xC7,0x37,0xCB,0x46);

#ifndef __IGravitySimulation_DISPINTERFACE_DEFINED__
#define __IGravitySimulation_DISPINTERFACE_DEFINED__

/* dispinterface IGravitySimulation */
/* [uuid] */ 


DEFINE_GUID(DIID_IGravitySimulation,0x4BB2307F,0x4C0F,0x4EE4,0xAA,0x6C,0xAD,0x43,0x46,0x9D,0x70,0xA8);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("4BB2307F-4C0F-4EE4-AA6C-AD43469D70A8")
    IGravitySimulation : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IGravitySimulationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IGravitySimulation __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IGravitySimulation __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IGravitySimulation __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IGravitySimulation __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IGravitySimulation __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IGravitySimulation __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IGravitySimulation __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IGravitySimulationVtbl;

    interface IGravitySimulation
    {
        CONST_VTBL struct IGravitySimulationVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGravitySimulation_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGravitySimulation_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGravitySimulation_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGravitySimulation_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IGravitySimulation_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IGravitySimulation_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IGravitySimulation_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IGravitySimulation_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_Document,0xA9D369B6,0xAACF,0x417C,0x86,0x03,0xC1,0x91,0xB9,0xFA,0xD0,0x99);

#ifdef __cplusplus

class DECLSPEC_UUID("A9D369B6-AACF-417C-8603-C191B9FAD099")
Document;
#endif
#endif /* __GravitySimulation_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


