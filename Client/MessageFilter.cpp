#include "stdafx.h"
#include "MessageFilter.h"

DWORD CMyMessageFilter::HandleInComingCall(
    DWORD dwCallType,
    HTASK threadIDCaller,
    DWORD dwTickCount,
    LPINTERFACEINFO lpInterfaceInfo)
{
    return SERVERCALL_ISHANDLED;
}

DWORD CMyMessageFilter::RetryRejectedCall(
    HTASK threadIDCallee,
    DWORD dwTimeOut,
    DWORD dwRejectType)//the ret val from HandleInComingCall()
{
    AtlTrace(_T("entered CMyMessageFilter::RetryRejectedCall()\n"));
    if (dwRejectType == SERVERCALL_REJECTED)
        return -1; //indicates that the call should be canceled

    return 0;
}

DWORD CMyMessageFilter::MessagePending(
    HTASK /*threadIDCallee*/,
    DWORD /*dwTickCount*/,
    DWORD /*dwPendingType*/)
{
    return PENDINGMSG_WAITDEFPROCESS;
}
