#pragma once
#include <windows.h>
#include <string>

std::wstring openFileDialog(HWND owner);
std::wstring saveFileDialog(HWND owner);
std::string readFile(const std::wstring& path);
void writeFile(const std::wstring& path, const std::string& content);