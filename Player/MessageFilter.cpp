#include "stdafx.h"
#include "MessageFilter.h"

///////////////////////////////////////////////////////////////////////////////
// IMessageFilter
///////////////////////////////////////////////////////////////////////////////
DWORD CMyMessageFilter::HandleInComingCall(
    DWORD dwCallType,
    HTASK threadIDCaller,
    DWORD dwTickCount,
    LPINTERFACEINFO lpInterfaceInfo)
{
    AtlTrace(_T("CMyMessageFilter::HandleInComingCall()\n"));
    AtlTrace(_T("\t threadIDCaller = %d \n"), threadIDCaller);

    DWORD dwRetVal{ 0 };
    //we cannot reject these calls
    if (dwCallType == CALLTYPE_ASYNC_CALLPENDING || dwCallType == CALLTYPE_ASYNC || dwCallType == CALLTYPE_TOPLEVEL) {
        AtlTrace("\t HandleInComingCall(): dwCallType == %d. SERVERCALL_ISHANDLED \n", dwCallType);
        dwRetVal = SERVERCALL_ISHANDLED;
    }
    else {//CALLTYPE_TOPLEVEL_CALLPENDING or CALLTYPE_NESTED
        AtlTrace("HandleInComingCall(): re-entrancy detected!!! SERVERCALL_RETRYLATER \n");
        dwRetVal = SERVERCALL_RETRYLATER;
    }
    return dwRetVal;
}

DWORD CMyMessageFilter::RetryRejectedCall(
    HTASK /*threadIDCallee*/,
    DWORD /*dwTimeOut*/,
    DWORD /*dwRejectType*/)//the ret val from HandleInComingCall()
{
    return -1; //indicates that the call should be canceled
}

DWORD CMyMessageFilter::MessagePending(
    HTASK /*threadIDCallee*/ ,
    DWORD /*dwTickCount*/ ,
    DWORD /*dwPendingType*/ )
{
    return PENDINGMSG_WAITDEFPROCESS;
}
