#pragma once
#include "resource.h"       // main symbols
#include "Player_i.h"
#include "../common/common.h"
using namespace ATL;

class ATL_NO_VTABLE Player :
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<Player, &CLSID_Player>,
    public IPlayer
{
public:
    DECLARE_REGISTRY_RESOURCEID(IDR_PLAYERIMPL)

    BEGIN_COM_MAP(Player)
        COM_INTERFACE_ENTRY(IPlayer)
    END_COM_MAP()

public:
    LRESULT RunUpdateLoop();

    DECLARE_PROTECT_FINAL_CONSTRUCT()
    HRESULT FinalConstruct();
    void FinalRelease();

    HRESULT STDMETHODCALLTYPE Play() override;
    HRESULT STDMETHODCALLTYPE Pause() override;
    HRESULT STDMETHODCALLTYPE Initialize(IFrameSource * source) override;
private:
    CComPtr<IFrame> m_frame;
    CComPtr<IFrameSource> m_source;
};

OBJECT_ENTRY_AUTO(__uuidof(Player), Player)
