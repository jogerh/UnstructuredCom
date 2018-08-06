#pragma once
#include <atlbase.h>
#include <atlctl.h>

using namespace ATL;

class ATL_NO_VTABLE CMyMessageFilter :
    public CComObjectRootEx<CComMultiThreadModel>,
    public CComCoClass<CMyMessageFilter>,
    public IMessageFilter
{
public:
    BEGIN_COM_MAP(CMyMessageFilter)
        COM_INTERFACE_ENTRY(IMessageFilter)
    END_COM_MAP()

    DWORD STDMETHODCALLTYPE HandleInComingCall(
        DWORD dwCallType,
        HTASK threadIDCaller,
        DWORD dwTickCount,
        LPINTERFACEINFO lpInterfaceInfo) override;

    DWORD STDMETHODCALLTYPE RetryRejectedCall(
        HTASK threadIDCallee,
        DWORD dwTickCount,
        DWORD dwRejectType) override;

    DWORD STDMETHODCALLTYPE MessagePending(
        HTASK threadIDCallee,
        DWORD dwTickCount,
        DWORD dwPendingType) override;

};
