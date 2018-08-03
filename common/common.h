#pragma once
#include <stdexcept>
#include <atlcomcli.h>

template <class T>
static ATL::CComPtr<T> CreateLocalInstance() {
    // create an object (with ref. count zero)
    CComObject<T> * tmp = nullptr;
    if (FAILED(ATL::CComObject<T>::CreateInstance(&tmp)))
        throw std::runtime_error("Failed to create instance");

    // move into smart-ptr (will incr. ref. count to one)
    return ATL::CComPtr<T>(static_cast<T*>(tmp));
}

inline void CHECK(HRESULT hr) {
    if (FAILED(hr))
        throw std::runtime_error("Com call failed");
}

inline void DisableComCatchExceptions() {
    ATL::CComPtr<IGlobalOptions> globalOptions;
    CHECK(globalOptions.CoCreateInstance(CLSID_GlobalOptions, NULL, CLSCTX_INPROC_SERVER));
    CHECK(globalOptions->Set(COMGLB_EXCEPTION_HANDLING, COMGLB_EXCEPTION_DONOT_HANDLE));
}
