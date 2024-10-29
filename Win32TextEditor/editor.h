#pragma once
#include <windows.h>
#include <string>

class Editor {
public:
    void initialize(HWND parent);
    void loadFile(const std::string& path);
    void saveFile(const std::string& path);
    void clear();
    std::wstring getText();
    void setText(const std::wstring& text);
    void resize(const RECT& rect);

private:
    HWND editControl;
    std::string currentFilePath;
};