#include "stdafx.h"
#include "Player.h"

LRESULT Player::OnDestroy(UINT, WPARAM, LPARAM, BOOL& bHandled)
{
    Pause();
    m_frame = nullptr;
    m_source = nullptr;
    bHandled = FALSE;
    return 0;
}

LRESULT Player::OnInitialized(UINT, WPARAM, LPARAM, BOOL&) {
    if (m_source)
        m_source->GetFrameCount(&m_frame_count);
    return 0;
}

LRESULT Player::OnPaint(UINT /*nMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    PAINTSTRUCT ps = {};
    auto hdc = BeginPaint(&ps);
    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_BACKGROUND));
    std::wstring text;
    if (m_frame)
        text = L"We are playing!";
    else
        text = L"We are not playing";
    TextOut(hdc, 0, 0, text.data(), static_cast<int>(text.size()));
    EndPaint(&ps);
    return 0L;
}

HRESULT Player::FinalConstruct()
{
    m_message_filter = CreateLocalInstance<CMyMessageFilter>();
    CoRegisterMessageFilter(m_message_filter, nullptr);
    s_created = true;
    return S_OK;
}

void Player::FinalRelease()
{
    Pause();
    m_frame = nullptr;
    m_source = nullptr;
    PostQuitMessage(0);
    s_created = false;
}

HRESULT Player::Play() {
    if (m_frame_count == 0) 
        return S_OK; // Nothing to play

    CHECK(m_source->GetFrame(&m_frame));
    CHECK(InvalidateRect(nullptr));
    return S_OK;
}

HRESULT Player::Pause() {
    return S_OK;
}

HRESULT Player::Initialize(IFrameSource * source) {
    if (!source)
        return E_POINTER;

    m_source = CComPtr<IFrameSource>(source);
    PostMessage(WM_INITIALIZED, 0, 0);
    return S_OK;
}
