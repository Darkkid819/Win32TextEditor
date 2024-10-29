#pragma once
#include <windows.h>
#include <string>

void showErrorDialog(const std::string& message);
void showInfoDialog(const std::string& message);
void centerWindow(HWND hwnd);
