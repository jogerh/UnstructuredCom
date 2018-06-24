#pragma once
#include <atlwin.h>
#include "Player.h"
#include <memory>
#define WM_UPDATE WM_USER+1
class Player;

class PlayerWindow : public ATL::CWindowImpl<PlayerWindow, ATL::CWindow, ATL::CFrameWinTraits> {
public:
    PlayerWindow() {
        RECT rect = { 0, 0, 600, 400 };
        Create(NULL, &rect, L"Player");
        ShowWindow(SW_SHOW);
    }

    ~PlayerWindow() {
        DestroyWindow();
        m_hWnd = NULL;
    }

    void SetPlayer(Player * player) {
        m_player = player;
        PostMessage(WM_UPDATE);
    }

    DECLARE_WND_CLASS(L"PlayerWindow");
    BEGIN_MSG_MAP(PlayerWindow)
        MESSAGE_HANDLER(WM_UPDATE, OnUpdate)
    END_MSG_MAP()

private:
    virtual LRESULT OnUpdate(UINT /*nMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled) {
        if (m_player)
            m_player->RunUpdateLoop();
        return 0;
    }

private:
    Player * m_player = nullptr;
};


class CPlayerModule : public ATL::CAtlExeModuleT< CPlayerModule >
{
public:
    DECLARE_LIBID(LIBID_PlayerLib)
    DECLARE_REGISTRY_APPID_RESOURCEID(IDR_PLAYER, "{A8FB7E99-B022-49A3-B329-E2DDF3FF64B8}")
    HRESULT Run(_In_ int nShowCmd = SW_HIDE) throw() {
        DisableComCatchExceptions();
        //while (!IsDebuggerPresent())
        //    Sleep(100);
        return ATL::CAtlExeModuleT< CPlayerModule >::Run(nShowCmd);
    }

    HRESULT PreMessageLoop(_In_ int nShowCmd) throw() {
        auto result = ATL::CAtlExeModuleT< CPlayerModule >::PreMessageLoop(nShowCmd);
        m_window = std::make_unique<PlayerWindow>();
        return result;
    }

    std::unique_ptr<PlayerWindow> m_window;
};

CPlayerModule * GetModule();