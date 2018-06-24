#include "stdafx.h"
#include "PlayerModule.h"
#include "resource.h"
#include "Player_i.h"
#include "../common/common.h"
#include "Player.h"
#include <memory>

using namespace ATL;


CPlayerModule _AtlModule;

extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, 
								LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	return _AtlModule.WinMain(nShowCmd);
}

CPlayerModule * GetModule()
{
    return &_AtlModule;
}
