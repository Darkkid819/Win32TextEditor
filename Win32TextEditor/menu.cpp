#include <Windows.h>
#include "menu.h"
#include "app.h"
#include "io.h"

void Menu::initialize(HWND hwnd) {
    hMenu = CreateMenu();

    // File Menu
    HMENU hFileMenu = CreatePopupMenu();
    AppendMenu(hFileMenu, MF_STRING, ID_FILE_NEW, L"New");
    AppendMenu(hFileMenu, MF_STRING, ID_FILE_OPEN, L"Open");
    AppendMenu(hFileMenu, MF_STRING, ID_FILE_SAVE, L"Save");
    AppendMenu(hFileMenu, MF_STRING, ID_FILE_SAVE_AS, L"Save As");
    AppendMenu(hFileMenu, MF_STRING, ID_FILE_CLOSE, L"Close");
    AppendMenu(hFileMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hFileMenu, MF_STRING, ID_FILE_EXIT, L"Exit");

    // Edit Menu
    HMENU hEditMenu = CreatePopupMenu();
    AppendMenu(hEditMenu, MF_STRING, ID_EDIT_UNDO, L"Undo");
    AppendMenu(hEditMenu, MF_STRING, ID_EDIT_REDO, L"Redo");
    AppendMenu(hEditMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hEditMenu, MF_STRING, ID_EDIT_CUT, L"Cut");
    AppendMenu(hEditMenu, MF_STRING, ID_EDIT_COPY, L"Copy");
    AppendMenu(hEditMenu, MF_STRING, ID_EDIT_PASTE, L"Paste");
    AppendMenu(hEditMenu, MF_STRING, ID_EDIT_SELECT_ALL, L"Select All");

    // View Menu
    HMENU hViewMenu = CreatePopupMenu();
    AppendMenu(hViewMenu, MF_STRING, ID_VIEW_ZOOM_IN, L"Zoom In");
    AppendMenu(hViewMenu, MF_STRING, ID_VIEW_ZOOM_OUT, L"Zoom Out");
    AppendMenu(hViewMenu, MF_STRING, ID_VIEW_RESET_ZOOM, L"Reset Zoom");
    AppendMenu(hViewMenu, MF_STRING, ID_VIEW_STATUS_BAR, L"Toggle Status Bar");

    // Window Menu
    HMENU hWindowMenu = CreatePopupMenu();
    AppendMenu(hWindowMenu, MF_STRING, ID_WINDOW_MINIMIZE, L"Minimize");
    AppendMenu(hWindowMenu, MF_STRING, ID_WINDOW_MAXIMIZE, L"Maximize");
    AppendMenu(hWindowMenu, MF_STRING, ID_WINDOW_CLOSE, L"Close Window");

    // Help Menu
    HMENU hHelpMenu = CreatePopupMenu();
    AppendMenu(hHelpMenu, MF_STRING, ID_HELP_VIEW_HELP, L"View Help");
    AppendMenu(hHelpMenu, MF_STRING, ID_HELP_CHECK_UPDATES, L"Check for Updates");
    AppendMenu(hHelpMenu, MF_STRING, ID_HELP_ABOUT, L"About");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"File");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hEditMenu, L"Edit");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hViewMenu, L"View");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hWindowMenu, L"Window");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, L"Help");

    SetMenu(hwnd, hMenu);
}


void Menu::handleMenuCommand(WPARAM wParam) {
    App& app = App::getInstance();
    Editor& editor = app.getEditor();

    switch (LOWORD(wParam)) {
    // File Menu
    case ID_FILE_NEW:
        editor.clear();
        break;

    case ID_FILE_OPEN: {
        std::wstring path = openFileDialog(app.getMainWindow());
        if (!path.empty()) {
            std::string content = readFile(path);
            editor.setText(std::wstring(content.begin(), content.end()));
            editor.setCurrentFilePath(path); 
        }
        break;
    }

    case ID_FILE_SAVE: {
        std::wstring path = editor.getCurrentFilePath();
        if (path.empty()) {
            path = saveFileDialog(app.getMainWindow());
            editor.setCurrentFilePath(path);
        }
        if (!path.empty()) {
            std::wstring content = editor.getText();
            writeFile(path, std::string(content.begin(), content.end()));
        }
        break;
    }

    case ID_FILE_SAVE_AS: {
        std::wstring path = saveFileDialog(app.getMainWindow());
        if (!path.empty()) {
            std::wstring content = editor.getText();
            writeFile(path, std::string(content.begin(), content.end()));
            editor.setCurrentFilePath(path); 
        }
        break;
    }

    case ID_FILE_CLOSE:
        editor.clear();
        break;

    case ID_FILE_EXIT:
        PostQuitMessage(0);
        break;

	// Edit Menu
	case ID_EDIT_UNDO:
		break;

	case ID_EDIT_REDO:
        break;

	case ID_EDIT_CUT:
        break;

	case ID_EDIT_COPY:
        break;

	case ID_EDIT_PASTE:
        break;

	case ID_EDIT_SELECT_ALL:
        break;

	// View Menu
	case ID_VIEW_ZOOM_IN:
		break;

	case ID_VIEW_ZOOM_OUT:
		break;

	case ID_VIEW_RESET_ZOOM:
		break;

	case ID_VIEW_STATUS_BAR:
		break;

	// Window Menu
	case ID_WINDOW_MINIMIZE:
		break;

	case ID_WINDOW_MAXIMIZE:
		break;

	case ID_WINDOW_CLOSE:
		break;
    
    // Help Menu
	case ID_HELP_VIEW_HELP:
		break;

	case ID_HELP_CHECK_UPDATES:
		break;

    case ID_HELP_ABOUT:
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
