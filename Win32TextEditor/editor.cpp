#include "editor.h"

void Editor::initialize(HWND parent) {
    editControl = CreateWindowEx(0, "EDIT", "",
        WS_CHILD | WS_VISIBLE | WS_VSCROLL |
        ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
        0, 0, 800, 600,
        parent, (HMENU)1,
        GetModuleHandle(NULL), NULL);
}

void Editor::loadFile(const std::string& path) {
    // Implement file reading logic
    currentFilePath = path;
}

void Editor::saveFile(const std::string& path) {
    // Implement file saving logic
}

void Editor::clear() {
    SetWindowText(editControl, "");
}

std::string Editor::getText() {
    int length = GetWindowTextLength(editControl);
    char* buffer = new char[length + 1];
    GetWindowText(editControl, buffer, length + 1);
    std::string text(buffer);
    delete[] buffer;
    return text;
}

void Editor::setText(const std::string& text) {
    SetWindowText(editControl, text.c_str());
}

void Editor::resize(const RECT& rect) {
    SetWindowPos(editControl, NULL, 0, 0, rect.right, rect.bottom, SWP_NOZORDER);
}
