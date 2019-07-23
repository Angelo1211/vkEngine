#include <stdio.h>
#define UNICODE
#include <windows.h>
#include <assert.h>
#include <vulkan/vulkan.h>

/*
PLAN:
---------------
*/

//Globals
LPCSTR WndClassName = "testWindow";
HWND hwnd = NULL;
const int Width = 800;
const int Height = 600;

#define VK_CHECK(call) \
   do { \
        VkResult result_ = call; \
        assert(result_ = VK_SUCCESS); \
  } while(0)                 \


bool InitializeWindow(HINSTANCE hInstance,
                      int ShowWnd,
                      int width,
                      int height,
                      bool windowed);

int messageloop();

LRESULT CALLBACK WndProc(HWND hWnd,
                         UINT msg,
                         WPARAM wParam,
                         LPARAM lParam);

int main(){
  return WinMain(GetModuleHandle(NULL), 0, 0, 0);
}

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLIne,
                   int nShowCmd)
{

    if (!InitializeWindow(hInstance, nShowCmd, Width, Height, true))
    {
        MessageBox(0, L"Window Init Failed",
                   L"Error", MB_OK);
        return 0;
    }

    VkInstanceCreateInfo createInfo;

    VkInstance instance = 0;
    // VK_CHECK(vkCreateInstance(&createInfo, 0, &instance));

    messageloop();

    return 0;
}

bool InitializeWindow(HINSTANCE hInstance,
                      int ShowWnd,
                      int width,
                      int height,
                      bool windowed)
{
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

    hwnd = CreateWindowEx(0,
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

    if (!hwnd)
    {
        MessageBox(0, L"Error creating window",
                   L"Error", MB_OK | MB_ICONERROR);
        return false;
    }

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);
    return true;
}

int messageloop()
{
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

LRESULT CALLBACK WndProc(HWND hwnd,
                         UINT msg,
                         WPARAM wParam,
                         LPARAM lParam)
{
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
