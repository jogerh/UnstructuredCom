#include "stdafx.h"
#include "common.h"

DWORD MessageFilter::HandleInComingCall(DWORD dwCallType, HTASK htaskCaller, DWORD dwTickCount, LPINTERFACEINFO lpInterfaceInfo)
{
    if (dwCallType == CALLTYPE_TOPLEVEL_CALLPENDING)
        return SERVERCALL_RETRYLATER;
    return SERVERCALL_ISHANDLED; 
}

DWORD MessageFilter::RetryRejectedCall(HTASK htaskCallee, DWORD dwTickCount, DWORD dwRejectType)
{
    if (dwRejectType == SERVERCALL_RETRYLATER)
        return 0;
    return -1;
}

DWORD MessageFilter::MessagePending(HTASK htaskCallee, DWORD dwTickCount, DWORD dwPendingType)
{
    return PENDINGMSG_WAITDEFPROCESS;
}
