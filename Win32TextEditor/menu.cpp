#include <Windows.h>
#include "menu.h"
#include "app.h"
#include "io.h"

void Menu::initialize(HWND hwnd) {
    hMenu = CreateMenu();
    HMENU hFileMenu = CreatePopupMenu();

    AppendMenu(hFileMenu, MF_STRING, ID_FILE_OPEN, L"Open");
    AppendMenu(hFileMenu, MF_STRING, ID_FILE_SAVE, L"Save");
    AppendMenu(hFileMenu, MF_STRING, IDM_EXIT, L"Exit");
    AppendMenu(hFileMenu, MF_STRING, IDM_ABOUT, L"About");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"File");
    SetMenu(hwnd, hMenu);
}

void Menu::handleMenuCommand(WPARAM wParam) {
    App& app = App::getInstance();

    switch (LOWORD(wParam)) {
    case ID_FILE_OPEN: {
        std::wstring path = openFileDialog(app.getMainWindow());
        if (!path.empty()) {
            std::string content = readFile(path);
            app.getEditor().setText(std::wstring(content.begin(), content.end()));
        }
        break;
    }
    case ID_FILE_SAVE: { 
        std::wstring path = saveFileDialog(app.getMainWindow());
        if (!path.empty()) {
            std::wstring content = app.getEditor().getText();
            writeFile(path, std::string(content.begin(), content.end()));
        }
        break;
    }
    case IDM_EXIT:
        PostQuitMessage(0);
        break;
    
    case IDM_ABOUT:
        DialogBox(
            GetModuleHandle(NULL),
            MAKEINTRESOURCE(IDD_ABOUTBOX),
            app.getMainWindow(),
            [](HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> INT_PTR { 
                if (msg == WM_COMMAND && LOWORD(wParam) == IDOK) {
                    EndDialog(hwnd, IDOK);
                    return TRUE;
                }
                return FALSE;
            }
        );
        break;
    default: break;
    }
}
