#include "app.h"

App::App() : mainWindow(nullptr) {}

App& App::getInstance() {
    static App instance;
    return instance;
}

void App::createMainWindow(HINSTANCE hInstance, int nCmdShow) {
    const WCHAR* className = L"TextEditorClass";

    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = App::messageHandler;
    wc.hInstance = hInstance;
    wc.lpszClassName = className;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32TEXTEDITOR));  // Load large icon
    wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));          // Load small icon

 
    if (!RegisterClassEx(&wc)) {
        DWORD error = GetLastError();
        WCHAR errorMessage[256];
        wsprintf(errorMessage, L"Window Registration Failed! Error Code: %lu", error);
        MessageBox(NULL, errorMessage, L"Error", MB_ICONEXCLAMATION | MB_OK);
        return;
    }

    mainWindow = CreateWindowEx(
        0, className, L"Text Editor",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL);

    if (!mainWindow) {
        MessageBox(NULL, L"Window Creation Failed!", L"Error", MB_ICONEXCLAMATION | MB_OK);
        return;
    }

    menu.initialize(mainWindow);
    editor.initialize(mainWindow);

    ShowWindow(mainWindow, nCmdShow);
    UpdateWindow(mainWindow);
}

LRESULT CALLBACK App::messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_SIZE:
        getInstance().resizeComponents();
        return 0;

    case WM_COMMAND: {
        int controlID = LOWORD(wParam);
        HWND controlHandle = (HWND)lParam;

        if (controlHandle == NULL) {
            getInstance().menu.handleMenuCommand(wParam);
        }
        return 0;
    }

    case WM_CLOSE:
        if (MessageBox(hwnd, L"Are you sure you want to quit?", L"Exit", MB_OKCANCEL) == IDOK) {
            DestroyWindow(hwnd);
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}


void App::resizeComponents() {
    RECT rect;
    GetClientRect(mainWindow, &rect);
    editor.resize(rect);
}
