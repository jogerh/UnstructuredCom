# UnstructuredCom
Sample code to demonstrate unstructured behavior when running a local COM server

## Issue summary
While a local single threaded COM server is doing an outgoing call to a single threaded client, it appears to be able to process it's own message queue. The server state may therefore have changed when the outgoing call returns. 

## Description
This sample code implements a client application, and a local COM server called 'Player'. The client creates a Player object, and provides the player with a frame data source. Once started, the player continuously queries the client for frame information. The player's main thread is therefore busy all the time.

When left clicking in the client window, the client releases it's reference to the player object. Even if the Player's main thread is busy calling back into the client, the release is processed, destroying the Player object. However, since the player at this time is busy calling into the client process, the Player crashes when the function call into the client returns. 

Since the player is single threaded, it is surprising that it is able to run it's own destructors while it is, at the same time, calling a function on the client. As a result, the player appears to run two threads, but since it is single threaded, regular synchronization primitives (mutexes) can not be used to protect data.

## Interesting code snippets:
See Player.cpp, Player::RunUpdateLoop(), where the player is spinning on m_frame->GetId(). 

## Sequence diagram
![Sequence diagram](doc/SequenceDiagram.png?raw=true "Sequence diagram")

## Build/run instructions

* Build projects Client and Player. Player.exe is registered automatically in a post build event.
* Run Client.exe
* Two windows should appear, Player and Client. 
* Attach with a debugger to Player.exe, and put a breakpoint in FinalRelease
* Click in client window.
* Observe call stack of the Player.exe, where the outgoing call m_frame->GetId() from Player::RunUpdateLoop() results in a call to the Player's destructor
```
    Player.exe!Player::FinalRelease() Line 29   C++
    Player.exe!ATL::CComObject<Player>::~CComObject<Player>() Line 2915 C++
    Player.exe!ATL::CComObject<Player>::`scalar deleting destructor'(unsigned int)  C++
--->Player.exe!ATL::CComObject<Player>::Release() Line 2934 C++
    ole32.dll!CStdIdentity::ReleaseCtrlUnk() Line 1149  C++
    ole32.dll!CStdMarshal::Disconnect(unsigned long dwType) Line 3608   C++
    ole32.dll!CStdMarshal::HandlePendingDisconnect(HRESULT hr)  C++
    ole32.dll!CRemoteUnknown::RemReleaseWorker(unsigned short cInterfaceRefs, tagREMINTERFACEREF * InterfaceRefs, int fTopLevel) Line 1078  C++
    rpcrt4.dll!Invoke()    Unknown
    rpcrt4.dll!Ndr64StubWorker(void *,void *,struct _RPC_MESSAGE *,struct _MIDL_SERVER_INFO_ *,long (*const *)(void),struct _MIDL_SYNTAX_INFO *,unsigned long *)    Unknown
    rpcrt4.dll!NdrStubCall3()  Unknown
    ole32.dll!CStdStubBuffer_Invoke(IRpcStubBuffer * This, tagRPCOLEMESSAGE * prpcmsg, IRpcChannelBuffer * pRpcChannelBuffer) Line 1586 C++
    ole32.dll!SyncStubInvoke(tagRPCOLEMESSAGE * pMsg, const _GUID & riid, CIDObject * pID, void * pVtableAddress, IRpcChannelBuffer * pChnl, IRpcStubBuffer * pStub, unsigned long * pdwFault) Line 1187    C++
    ole32.dll!StubInvoke(tagRPCOLEMESSAGE * pMsg, CStdIdentity * pStdID, IRpcStubBuffer * pStub, IRpcChannelBuffer * pChnl, tagIPIDEntry * pIPIDEntry, unsigned long * pdwFault) Line 1396  C++
    ole32.dll!CCtxComChnl::ContextInvoke(tagRPCOLEMESSAGE * pMessage, IRpcStubBuffer * pStub, tagIPIDEntry * pIPIDEntry, unsigned long * pdwFault) Line 1263    C++
    ole32.dll!MTAInvoke(tagRPCOLEMESSAGE * pMsg, unsigned long CallCatIn, IRpcStubBuffer * pStub, IInternalChannelBuffer * pChnl, tagIPIDEntry * pIPIDEntry, unsigned long * pdwFault) Line 2105    C++
    ole32.dll!STAInvoke(tagRPCOLEMESSAGE * pMsg, unsigned long CallCatIn, IRpcStubBuffer * pStub, IInternalChannelBuffer * pChnl, void * pv, tagIPIDEntry * pIPIDEntry, unsigned long * pdwFault) Line 1924 C++
    ole32.dll!AppInvoke(CMessageCall * pCall, CRpcChannelBuffer * pChannel, IRpcStubBuffer * pStub, void * pv, void * pStubBuffer, tagIPIDEntry * pIPIDEntry, LocalThis * pLocalb) Line 1081    C++
    ole32.dll!ComInvokeWithLockAndIPID(CMessageCall * pCall, tagIPIDEntry * pIPIDEntry) Line 1727   C++
    ole32.dll!ComInvoke(CMessageCall * pCall) Line 1469 C++
    ole32.dll!ThreadDispatch(void * param) Line 298 C++
    ole32.dll!ThreadWndProc(HWND__ * window, unsigned int message, unsigned __int64 wparam, __int64 params) Line 654    C++
    user32.dll!UserCallWinProcCheckWow()   Unknown
    user32.dll!DispatchMessageWorker() Unknown
    ole32.dll!CCliModalLoop::PeekRPCAndDDEMessage() Line 1508   C++
    ole32.dll!CCliModalLoop::BlockFn(void * * ahEvent, unsigned long cEvents, unsigned long * lpdwSignaled) C++
    ole32.dll!ModalLoop(CMessageCall * pcall) Line 211  C++
    ole32.dll!ThreadSendReceive(CMessageCall * pCall) Line 4938 C++
    ole32.dll!CRpcChannelBuffer::SwitchAptAndDispatchCall(CMessageCall * * ppCall) Line 4454    C++
    ole32.dll!CRpcChannelBuffer::SendReceive2(tagRPCOLEMESSAGE * pMessage, unsigned long * pstatus) Line 4074   C++
    ole32.dll!CCliModalLoop::SendReceive(tagRPCOLEMESSAGE * pMsg, unsigned long * pulStatus, IInternalChannelBuffer * pChnl) Line 899   C++
    ole32.dll!CAptRpcChnl::SendReceive(tagRPCOLEMESSAGE * pMsg, unsigned long * pulStatus) Line 583 C++
    ole32.dll!CCtxComChnl::SendReceive(tagRPCOLEMESSAGE * pMessage, unsigned long * pulStatus) Line 734 C++
    ole32.dll!NdrExtpProxySendReceive(void * pThis, _MIDL_STUB_MESSAGE * pStubMsg) Line 1932    C++
    rpcrt4.dll!NdrpClientCall2(struct _MIDL_STUB_DESC const *,unsigned char const *,unsigned char *)    Unknown
    ole32.dll!ObjectStublessClient(void * ParamAddress, __int64 * FloatRegisters, long Method) Line 620 C++
    ole32.dll!ObjectStubless() Line 117 Unknown
--->Player.exe!Player::RunUpdateLoop() Line 16  C++
    Player.exe!PlayerWindow::OnUpdate(unsigned int __formal, unsigned __int64 __formal, __int64 __formal, int & bHandled) Line 35   C++
    Player.exe!PlayerWindow::ProcessWindowMessage(HWND__ * hWnd, unsigned int uMsg, unsigned __int64 wParam, __int64 lParam, __int64 & lResult, unsigned long dwMsgMapID) Line 28   C++
    Player.exe!ATL::CWindowImplBaseT<ATL::CWindow,ATL::CWinTraits<114229248,262400> >::WindowProc(HWND__ * hWnd, unsigned int uMsg, unsigned __int64 wParam, __int64 lParam) Line 3526  C++
    user32.dll!UserCallWinProcCheckWow()   Unknown
    user32.dll!DispatchMessageWorker() Unknown
    Player.exe!ATL::CAtlExeModuleT<CPlayerModule>::RunMessageLoop() Line 3698   C++
    Player.exe!ATL::CAtlExeModuleT<CPlayerModule>::Run(int nShowCmd) Line 3715  C++
    Player.exe!CPlayerModule::Run(int nShowCmd) Line 53 C++
    Player.exe!ATL::CAtlExeModuleT<CPlayerModule>::WinMain(int nShowCmd) Line 3537  C++
    Player.exe!wWinMain(HINSTANCE__ * __formal, HINSTANCE__ * __formal, wchar_t * __formal, int nShowCmd) Line 18   C++
    Player.exe!invoke_main() Line 118   C++
    Player.exe!__scrt_common_main_seh() Line 253    C++
    Player.exe!__scrt_common_main() Line 296    C++
    Player.exe!wWinMainCRTStartup() Line 17 C++
    kernel32.dll!BaseThreadInitThunk() Unknown
    ntdll.dll!RtlUserThreadStart() Unknown
```


## References
* [DCOM in Vista specifically processing WM_PAINT messages](https://social.msdn.microsoft.com/Forums/windowsdesktop/en-US/5a28a9f5-5711-4efa-843e-e98927fa2b92/dcom-in-vista-specifically-processing-wmpaint-messages?forum=windowsgeneraldevelopmentissues)
* [COM, Re-entrancy, and Message Pumping](https://blogs.msdn.microsoft.com/timng/2006/09/07/com-re-entrancy-and-message-pumping/)
* [How do I ensure no re-entrant access to my main-STA COM server (C++)?](https://stackoverflow.com/questions/2272715/how-do-i-ensure-no-re-entrant-access-to-my-main-sta-com-server-c)
* Essential COM, Don Box, Addison-Wesley, ISBN: 0-201-63446-5, 1998, pages 233-235
