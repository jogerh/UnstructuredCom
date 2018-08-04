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
        MESSAGE_HANDLER(WM_LBUTTONUP, OnClosePlayer)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
    END_MSG_MAP()

    void OnFinalMessage(HWND /*hWnd*/)
    {
        ::PostQuitMessage(0);
    }

    LRESULT OnPaint(UINT, WPARAM, LPARAM, BOOL&) {
        PAINTSTRUCT ps = {};
        auto hdc = BeginPaint(&ps);

        std::wstring text = L"Click in window to stop player. If you hear a beep, unstructured behavior occured";
        TextOut(hdc, 0, 0, text.data(), static_cast<int>(text.size()));

        EndPaint(&ps);
        return 0;
    }

    LRESULT OnClosePlayer(UINT, WPARAM, LPARAM, BOOL&) {
        m_player = nullptr;
        return 0;
    }

    LRESULT OnDestroy(UINT, WPARAM, LPARAM, BOOL& bHandled)
    {
        m_player = nullptr;
        bHandled = FALSE;
        return 0;
    }

    LRESULT OnCreate(UINT, WPARAM, LPARAM, BOOL& handled)
    {
        try {
            m_filter = CreateLocalInstance<MessageFilter>();
            CComPtr<IUnknown> ctrl;
            CHECK(ctrl.CoCreateInstance(L"Player", nullptr, CLSCTX_LOCAL_SERVER)); // Create a Player instance in a separate process
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
    CComPtr<IMessageFilter> m_filter;
    CComPtr<IPlayer> m_player;
    CComPtr<IFrameSource> m_source;
};

