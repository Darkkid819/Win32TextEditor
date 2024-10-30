#include "editor.h"
#include "resource.h"

void Editor::initialize(HWND parent) {
    editControl = CreateWindowEx(
        0,
        L"EDIT", 
        L"",  
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
        0, 0, 800, 600,
        parent, (HMENU)IDC_EDITOR, 
        GetModuleHandle(NULL), NULL);
}

void Editor::clear() {
    SetWindowText(editControl, L"");
}

std::wstring Editor::getText() {
    int length = GetWindowTextLength(editControl);
    wchar_t* buffer = new wchar_t[length + 1];
    GetWindowText(editControl, buffer, length + 1);
    std::wstring text(buffer);
    delete[] buffer;
    return text;
}

void Editor::setText(const std::wstring& text) {
    SetWindowText(editControl, text.c_str());
}

void Editor::resize(const RECT& rect) {
    SetWindowPos(editControl, NULL, 0, 0, rect.right, rect.bottom, SWP_NOZORDER);
}
