#pragma once
#include <windows.h>
#include <string>

class Editor {
public:
    void initialize(HWND parent);
    void clear();
    std::wstring getText();
    void setText(const std::wstring& text);
    void resize(const RECT& rect);
    std::wstring getCurrentFilePath() const;
    void setCurrentFilePath(const std::wstring& path);

private:
    HWND editControl;
    std::wstring currentFilePath;
};