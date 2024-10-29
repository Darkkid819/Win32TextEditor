#include <windows.h>
#include "app.h"

void initApp();
void runEventLoop();

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    initApp();
    App::getInstance().createMainWindow(hInstance, nCmdShow);
    runEventLoop();
    return 0;
}

void initApp() {
    App::getInstance();
}

void runEventLoop() {
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (msg.message != WM_QUIT) {
        MessageBox(NULL, L"Unexpected Message Loop Error!", L"Error", MB_ICONEXCLAMATION | MB_OK);
    }
}
