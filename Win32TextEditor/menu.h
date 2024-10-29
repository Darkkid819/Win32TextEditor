#pragma once
#include <windows.h>

class Menu {
public:
    void initialize(HWND hwnd);
    void handleMenuCommand(WPARAM wParam);

private:
    HMENU hMenu;
};
