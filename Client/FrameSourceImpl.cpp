#include "stdafx.h"
#include "FrameSourceImpl.h"
#include "../common/common.h"

static int s_counter = 0;

Frame::Frame() : m_counter{ s_counter++ } {}

HRESULT Frame::GetId(int * id) {
    if (!id)
        return E_POINTER;
    
    Sleep(1); // Any work will do to make the server process it's own messages
    *id = m_counter;
    return S_OK;
}

HRESULT CFrameSourceImpl::GetFrame(IFrame ** frame) {
    if (!frame)
        return E_POINTER;   

    auto tmp = CreateLocalInstance<Frame>();
    *frame = tmp.Detach();
    return S_OK;
}

HRESULT CFrameSourceImpl::GetFrameCount(unsigned int * count) {
    if (!count)
        return E_POINTER;

    *count = m_frame_count;
    return S_OK;
}
