#include "TaskbarList3.h"
#include <windowsx.h>
#include <commctrl.h>
#include "resource.h"

static ITaskbarList3 *s_pTBL = NULL;
static UINT s_nPos = 0;
static UINT s_nMax = 100;

VOID DoSetProgress(HWND hwnd, UINT nPos, TBPFLAG flags = TBPF_NORMAL)
{
    s_nPos = nPos;
    SendDlgItemMessageW(hwnd, ctl1, PBM_SETRANGE, 0, MAKELPARAM(0, s_nMax));
    SendDlgItemMessageW(hwnd, ctl1, PBM_SETPOS, s_nPos, 0);

    if (s_pTBL)
    {
        TBL3_SetProgressState(s_pTBL, hwnd, flags);
        TBL3_SetProgressValue(s_pTBL, hwnd, s_nPos, s_nMax);
    }
}

BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    s_pTBL = TBL3_Create();
    DoSetProgress(hwnd, 0);
    return TRUE;
}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id)
    {
    case psh1:
        SetFocus(GetDlgItem(hwnd, IDOK));
        EnableWindow(GetDlgItem(hwnd, psh1), FALSE);
        DoSetProgress(hwnd, 0);
        SetTimer(hwnd, 999, 200, NULL);
        break;
    case IDOK:
    case IDCANCEL:
        EndDialog(hwnd, id);
        break;
    }
}

void OnTimer(HWND hwnd, UINT id)
{
    if (id == 999)
    {
        if (s_nPos >= s_nMax)
        {
            KillTimer(hwnd, id);
            EnableWindow(GetDlgItem(hwnd, psh1), TRUE);
            DoSetProgress(hwnd, 0, TBPF_NOPROGRESS);
        }
        else
        {
            DoSetProgress(hwnd, s_nPos + 5);
        }
    }
}

void OnDestroy(HWND hwnd)
{
    if (s_pTBL)
    {
        s_pTBL->Release();
        s_pTBL = NULL;
    }
}

INT_PTR CALLBACK
DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        HANDLE_MSG(hwnd, WM_INITDIALOG, OnInitDialog);
        HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
        HANDLE_MSG(hwnd, WM_TIMER, OnTimer);
        HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
    }
    return 0;
}

INT WINAPI
WinMain(HINSTANCE   hInstance,
        HINSTANCE   hPrevInstance,
        LPSTR       lpCmdLine,
        INT         nCmdShow)
{
    HRESULT hr = CoInitialize(NULL);

    InitCommonControls();
    DialogBoxW(hInstance, MAKEINTRESOURCEW(IDD_MAIN), NULL, DialogProc);

    if (SUCCEEDED(hr))
        CoUninitialize();
    return 0;
}
