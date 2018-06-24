#include "stdafx.h"
#include "Player.h"
#include "PlayerModule.h"

static bool s_created = false;

LRESULT Player::RunUpdateLoop() {
    
    while(m_frame) {
        
        int frameNo = 0;
        if (!s_created) {
            // We experienced unstructured behavior, because Player was destroyed while main thread is processing
            Beep(500, 250);
        }
        CHECK(m_frame->GetId(&frameNo));
    }
    
    return S_OK;
}

HRESULT Player::FinalConstruct()
{
    s_created = true;
    return S_OK;
}

void Player::FinalRelease()
{
    GetModule()->m_window->SetPlayer(nullptr);
    m_frame = nullptr;
    m_source = nullptr;
    s_created = false;
}

HRESULT Player::Play() {
    // Register player to the main window, 
    // so we get notified when user clicks
    // in client window. This will
    // start the RunUpdateLoop
    GetModule()->m_window->SetPlayer(this);

    return S_OK;
}

HRESULT Player::Pause() {
    return E_NOTIMPL;
}

HRESULT Player::Initialize(IFrameSource * source) {
    if (!source)
        return E_POINTER;

    m_source = CComPtr<IFrameSource>(source);
    CHECK(m_source->GetFrame(&m_frame));
   
    return S_OK;
}

