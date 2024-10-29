#include "app.h"

App::App() : mainWindow(nullptr) {}

App& App::getInstance() {
    static App instance;
    return instance;
}

void App::createMainWindow(HINSTANCE hInstance, int nCmdShow) {
    const char* className = "TextEditorClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = App::messageHandler;
    wc.hInstance = hInstance;
    wc.lpszClassName = className;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    mainWindow = CreateWindowEx(0, className, "Text Editor", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL);

    menu.initialize(mainWindow);
    editor.initialize(mainWindow);

    ShowWindow(mainWindow, nCmdShow);
}

LRESULT CALLBACK App::messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_SIZE:
        getInstance().resizeComponents();
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
