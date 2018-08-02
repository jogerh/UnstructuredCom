#include "stdafx.h"
#include "FrameSourceImpl.h"
#include "../common/common.h"

static int s_counter = 0;
Frame::Frame() : m_counter{ s_counter++ } {}

HRESULT Frame::GetId(int * id) {
    if (!id)
        return E_POINTER;
    
    Sleep(100);         // Simulate workload
    *id = m_counter;
    return S_OK;
}

void Frame::FinalRelease()
{
    MessageBox(0, L"CFrameSourceImpl::FinalRelease was called", L"Info", MB_OK);
}

HRESULT CFrameSourceImpl::GetFrame(IFrame ** frame) {
    if (!frame)
        return E_POINTER;   

    auto tmp = CreateLocalInstance<Frame>();
    *frame = tmp.Detach();
    return S_OK;
}

