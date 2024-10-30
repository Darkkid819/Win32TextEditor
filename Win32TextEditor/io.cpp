#include "io.h"

#include "io.h"
#include <fstream>
#include <commdlg.h>

std::wstring openFileDialog(HWND owner) {
    OPENFILENAME ofn = {};
    wchar_t fileName[MAX_PATH] = L"";

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = owner;
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = L"Text Files\0*.TXT\0All Files\0*.*\0";
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

    if (GetOpenFileName(&ofn)) {
        return fileName;
    }
    return L"";
}

std::wstring saveFileDialog(HWND owner) {
    OPENFILENAME ofn = {};
    wchar_t fileName[MAX_PATH] = L"";

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = owner;
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = L"Text Files\0*.TXT\0All Files\0*.*\0";
    ofn.Flags = OFN_OVERWRITEPROMPT;

    if (GetSaveFileName(&ofn)) {
        return fileName;
    }
    return L"";
}

std::string readFile(const std::wstring& path) {
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file) return "";

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
}

void writeFile(const std::wstring& path, const std::string& content) {
    std::ofstream file(path, std::ios::out | std::ios::binary);
    if (file) {
        file.write(content.c_str(), content.size());
        file.close();
    }
}
