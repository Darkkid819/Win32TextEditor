#include "editor.h"

void Editor::initialize(HWND parent) {
    editControl = CreateWindowEx(
        0,                    // Optional window styles
        L"EDIT",              // Control class name (as wide string)
        L"",                  // Window text (empty string)
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
        0, 0, 800, 600,       // Position and size
        parent, (HMENU)1,     // Parent window and control ID
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
    SetWindowText(editControl, L"");
}

std::wstring Editor::getText() {
    int length = GetWindowTextLength(editControl);
    wchar_t* buffer = new wchar_t[length + 1];  // Use wchar_t buffer
    GetWindowText(editControl, buffer, length + 1);
    std::wstring text(buffer);  // Convert buffer to wstring
    delete[] buffer;
    return text;
}

void Editor::setText(const std::wstring& text) {
    SetWindowText(editControl, text.c_str());
}

void Editor::resize(const RECT& rect) {
    SetWindowPos(editControl, NULL, 0, 0, rect.right, rect.bottom, SWP_NOZORDER);
}
