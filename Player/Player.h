#pragma once
#include "resource.h"       // main symbols
#include <atlctl.h>
#include <sstream>
#include "Player_i.h"
#include <atlbase.h>
#include "../common/common.h"
using namespace ATL;

static bool s_created = false;

class PlayerWindow : public ATL::CWindowImpl<PlayerWindow, ATL::CWindow, ATL::CFrameWinTraits> {
public:
    DECLARE_WND_CLASS(L"PlayerWindow");
    BEGIN_MSG_MAP(PlayerWindow)
        MESSAGE_HANDLER(WM_TIMER, OnTimer)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
    END_MSG_MAP()

protected:
    virtual LRESULT OnTimer(UINT /*nMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/) = 0;
    virtual LRESULT OnPaint(UINT /*nMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/) = 0;
    virtual LRESULT OnDestroy(UINT /*nMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/) = 0;
};

class ATL_NO_VTABLE Player :
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<Player, &CLSID_Player>,
    public IPlayer,
    public PlayerWindow
{
public:
    Player() {
        RECT rect = {0, 0, 600, 400};
        Create(NULL, &rect, L"Player" );
        ShowWindow(SW_SHOW);
    }
    ~Player() {
        Pause();
        m_frame = nullptr;
        m_source = nullptr;
        DestroyWindow();
    }

    DECLARE_REGISTRY_RESOURCEID(IDR_PLAYERIMPL)

    BEGIN_COM_MAP(Player)
        COM_INTERFACE_ENTRY(IPlayer)
    END_COM_MAP()

public:
    LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
    LRESULT OnPaint(UINT /*nMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/) override;
    LRESULT OnDestroy(UINT /*nMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/) override;

    DECLARE_PROTECT_FINAL_CONSTRUCT()
    HRESULT FinalConstruct();
    void FinalRelease();

    HRESULT STDMETHODCALLTYPE Play() override;
    HRESULT STDMETHODCALLTYPE Pause() override;
    HRESULT STDMETHODCALLTYPE Initialize(IFrameSource * source) override;

private:
    CComPtr<IFrame> m_frame;
    CComPtr<IFrameSource> m_source;
    int m_timer = -1;
};

OBJECT_ENTRY_AUTO(__uuidof(Player), Player)
