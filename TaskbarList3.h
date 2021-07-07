#pragma once

#ifndef _INC_WINDOWS
    #include <windows.h>
#endif
#include <shobjidl.h>

// typedef enum TBPFLAG {
//     TBPF_NOPROGRESS = 0x0,
//     TBPF_INDETERMINATE = 0x1,
//     TBPF_NORMAL = 0x2,
//     TBPF_ERROR = 0x4,
//     TBPF_PAUSED = 0x8
// } TBPFLAG;

inline ITaskbarList3 *TBL3_Create(void)
{
    ITaskbarList3 *pTBL = NULL;
    HRESULT hr = CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_ALL, IID_ITaskbarList3, (LPVOID*)&pTBL);
    if (SUCCEEDED(hr) && pTBL)
    {
        pTBL->HrInit();
        return pTBL;
    }
    return NULL;
}

inline HRESULT
TBL3_SetProgressState(ITaskbarList3 *pTBL, HWND hwnd, TBPFLAG flags)
{
    return pTBL->SetProgressState(hwnd, flags);
}

inline HRESULT
TBL3_SetProgressValue(ITaskbarList3 *pTBL, HWND hwnd,
                      ULONGLONG ullCompleted, ULONGLONG ullTotal)
{
    return pTBL->SetProgressValue(hwnd, ullCompleted, ullTotal);
}
