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

LRESULT Player::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled) {
    if (s_created && m_source && m_timer != -1) {
        
        m_frame = nullptr;                   // Release frame, before we get a new one from the client. (1)
        CHECK(m_source->GetFrame(&m_frame)); // This call may have to wait, if client is busy.          (2)
        ATLASSERT(m_frame != nullptr);       // We are now guaranteed that m_frame is not null          (3)
       
        InvalidateRect(nullptr);             // Trigger a redraw                                        (4)
    }
    return 0;
}

LRESULT Player::OnPaint(UINT /*nMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    std::wstringstream  ss;
    if (m_frame) {                           // According to (3) above, m_frame can not be nullptr
        int frameNo = 0;
        CHECK(m_frame->GetId(&frameNo));

        ss << "Showing frame " << frameNo;
    }
    else {                                   // Still, we sometimes end up here.
                                             // This indicates that OnPaint is called while 
                                             // OnTimer is executing m_source->GetFrame(...)
        ss << "Ops, we don't have a frame (unstructured behavior)";
    }

    auto str = ss.str();

    PAINTSTRUCT ps = {};
    auto hdc = BeginPaint(&ps);
    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_BACKGROUND));
    TextOut(hdc, 0, 0, str.data(), static_cast<int>(str.size()));
    EndPaint(&ps);
    return 0L;
}

HRESULT Player::FinalConstruct()
{
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

    if (m_timer == -1)
        SetTimer(m_timer = 1, 10, nullptr);
    return S_OK;
}

HRESULT Player::Pause() {
    if (m_timer != -1)
        KillTimer(m_timer);
    m_timer = -1;
    return S_OK;
}

HRESULT Player::Initialize(IFrameSource * source) {
    if (!source)
        return E_POINTER;

    m_source = CComPtr<IFrameSource>(source);
    PostMessage(WM_INITIALIZED, 0, 0);
    return S_OK;
}
