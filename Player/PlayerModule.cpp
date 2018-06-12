#include "stdafx.h"
#include "resource.h"
#include "Player_i.h"
#include "../common/common.h"
using namespace ATL;
class CPlayerModule : public ATL::CAtlExeModuleT< CPlayerModule >
{
public :
	DECLARE_LIBID(LIBID_PlayerLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_PLAYER, "{A8FB7E99-B022-49A3-B329-E2DDF3FF64B8}")
    HRESULT Run(_In_ int nShowCmd = SW_HIDE) throw() {
        DisableComCatchExceptions();
        //while (!IsDebuggerPresent())
        //    Sleep(100);
        return ATL::CAtlExeModuleT< CPlayerModule >::Run(nShowCmd);
    }
};

CPlayerModule _AtlModule;

extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, 
								LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	return _AtlModule.WinMain(nShowCmd);
}
