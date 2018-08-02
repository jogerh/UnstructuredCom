#pragma once
#include "resource.h"       // main symbols
#include "Interfaces.h"
using namespace ATL;

class ATL_NO_VTABLE Frame :
    public CComObjectRootEx<CComMultiThreadModel>,
    public CComCoClass<Frame>,
    public IFrame {
public:
    BEGIN_COM_MAP(Frame)
        COM_INTERFACE_ENTRY(IFrame)
    END_COM_MAP()

    Frame();
    HRESULT STDMETHODCALLTYPE GetId(int * id) override;
    void FinalRelease();

private:
    int m_counter = 0;
};

class ATL_NO_VTABLE CFrameSourceImpl :
    public CComObjectRootEx<CComMultiThreadModel>,
    public CComCoClass<CFrameSourceImpl>,
    public IFrameSource
{
public:
    BEGIN_COM_MAP(CFrameSourceImpl)
        COM_INTERFACE_ENTRY(IFrameSource)
    END_COM_MAP()

    HRESULT STDMETHODCALLTYPE GetFrame(IFrame ** frame) override;
};

