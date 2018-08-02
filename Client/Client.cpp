// Client.cpp : Implementation of WinMain


#include "stdafx.h"
#include "resource.h"
#include "ClientWindow.h"
#include "Client_i.h"
#include "Client_i.c"
#include <memory>

using namespace ATL;


class CClientModule : public ATL::CAtlExeModuleT< CClientModule >
{
public :
	DECLARE_LIBID(LIBID_ClientLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_CLIENT, "{CF183989-CBDF-4E1C-887E-B8526323193F}")

    HRESULT PreMessageLoop(int nShowCmd) throw()
    {
        DisableComCatchExceptions();
        EnableFastRundown();

        HRESULT hr = __super::PreMessageLoop(nShowCmd);
        if (FAILED(hr))
        {
            return hr;
        }

        HMENU hMenu = LoadMenu(_AtlBaseModule.GetResourceInstance(), MAKEINTRESOURCE(IDR_MENU1));

        m_window = std::make_unique<ClientWindow>();
        auto wnd = m_window->Create(GetDesktopWindow(), 0, _T("Client"), 0, 0, hMenu);
        if (!IsWindow(wnd))
            return E_FAIL;
        
        m_window->ShowWindow(nShowCmd);

        return S_OK;
    }

    std::unique_ptr<ClientWindow> m_window;
};

CClientModule _AtlModule;

extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, 
								LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	return _AtlModule.WinMain(nShowCmd);
}

