#pragma once
#include <atlwin.h>
#include <atltypes.h>
#include "../common/common.h"
#include "FrameSourceImpl.h"
#include "Client_i.h"

using namespace ATL;
class ClientWindow : public CWindowImpl<ClientWindow, ATL::CWindow, ATL::CFrameWinTraits >
{
public:
    BEGIN_MSG_MAP(ClientWindow)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
    END_MSG_MAP()

    void OnFinalMessage(HWND /*hWnd*/)
    {
        ::PostQuitMessage(0);
    }

    LRESULT OnDestroy(UINT, WPARAM, LPARAM, BOOL& bHandled)
    {
        m_player.Release();
        bHandled = FALSE;
        return 0;
    }

    LRESULT OnCreate(UINT, WPARAM, LPARAM, BOOL& handled)
    {
        try {
            CLSID clsid = {};
            CHECK(CLSIDFromString(L"Player", &clsid));

            CComPtr<IUnknown> ctrl;
            CHECK(ctrl.CoCreateInstance(clsid, nullptr, CLSCTX_LOCAL_SERVER)); // allow both in-process and out-of-process "apps"
            CHECK(ctrl.QueryInterface(&m_player));

            m_source = CreateLocalInstance<CFrameSourceImpl>();
            CHECK(m_player->Initialize(m_source));
            CHECK(m_player->Play());

            handled = TRUE;
            return 0;
        }
        catch (std::runtime_error & /*e*/) {
            return 1;
        }
    }

private:
    CComPtr<IPlayer> m_player;
    CComPtr<IFrameSource> m_source;
};

