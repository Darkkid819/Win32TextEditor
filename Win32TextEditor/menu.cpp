#include "menu.h"

void Menu::initialize(HWND hwnd) {
    hMenu = CreateMenu();
    HMENU hFileMenu = CreatePopupMenu();
    AppendMenu(hFileMenu, MF_STRING, 1, "Open");
    AppendMenu(hFileMenu, MF_STRING, 2, "Save");
    AppendMenu(hFileMenu, MF_STRING, 3, "Exit");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
    SetMenu(hwnd, hMenu);
}

void Menu::handleMenuCommand(WPARAM wParam) {
    switch (LOWORD(wParam)) {
    case 1: // Open
        // Handle Open command
        break;
    case 2: // Save
        // Handle Save command
        break;
    case 3: // Exit
        PostQuitMessage(0);
        break;
    }
}
