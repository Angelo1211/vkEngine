#pragma once

LPCSTR g_WndClassName = "testWindow";
HWND g_hwnd = NULL;

int
messageloop(){
    MSG msg;

    ZeroMemory(&msg, sizeof(MSG));

    for (;;)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            //Run game
        }
    }
    return msg.wParam;
}

LRESULT CALLBACK
WndProc(HWND hwnd,
        UINT msg,
        WPARAM wParam,
        LPARAM lParam){
    switch (msg)
    {
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE)
        {
            if (MessageBox(0, L"Are you sure?",
                           L"Really",
                           MB_YESNO | MB_ICONQUESTION) == IDYES)
                DestroyWindow(hwnd);
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd,
                         msg,
                         wParam,

                         lParam);
}

bool
InitializeWindow(HINSTANCE hInstance,
                      int ShowWnd,
                      int width,
                      int height,
                      bool windowed){
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(0, IDI_APPLICATION);
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    wc.lpszClassName = L"window";
    wc.hIconSm = LoadIcon(0, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(0, L"Error registering class",
                   L"Error", MB_OK | MB_ICONERROR);
        return false;
    }

    g_hwnd = CreateWindowEx(0,
                          wc.lpszClassName,
                          L"TestWindow",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          width,
                          height,
                          0,
                          0,
                          hInstance,
                          0);

    if (!g_hwnd)
    {
        MessageBox(0, L"Error creating window",
                   L"Error", MB_OK | MB_ICONERROR);
        return false;
    }

    ShowWindow(g_hwnd, SW_SHOWDEFAULT);
    UpdateWindow(g_hwnd);
    return true;
}

int WINAPI
WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLIne,
                   int nShowCmd){
    if (!InitializeWindow(hInstance, nShowCmd, g_Width, g_Height, true))
    {
        MessageBox(0, L"Window Init Failed",
                   L"Error", MB_OK);
        return 0;
    }

    if (!InitializeVulkan()){
        MessageBox(0, L"Vulkan Init Failed",
                   L"Error", MB_OK);
        return 0;
    }

    InitializeVulkan();

    messageloop();

    vkDestroyInstance(g_instance, 0);

    return 0;
}
