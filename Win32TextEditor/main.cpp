#include <windows.h>
#include "app.h"

void initApp();
void runEventLoop();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    initApp();

    App::getInstance().createMainWindow(hInstance, nCmdShow);

    runEventLoop();

    return 0;
}

void initApp() {
    App::getInstance();
}

void runEventLoop() {
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
