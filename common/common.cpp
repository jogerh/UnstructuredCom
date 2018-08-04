#include "stdafx.h"
#include "common.h"

DWORD MessageFilter::HandleInComingCall(DWORD dwCallType, HTASK htaskCaller, DWORD dwTickCount, LPINTERFACEINFO lpInterfaceInfo)
{
    return SERVERCALL_ISHANDLED;
}

DWORD MessageFilter::RetryRejectedCall(HTASK htaskCallee, DWORD dwTickCount, DWORD dwRejectType)
{
    return -1;
}

DWORD MessageFilter::MessagePending(HTASK htaskCallee, DWORD dwTickCount, DWORD dwPendingType)
{
    return PENDINGMSG_WAITDEFPROCESS;
}
