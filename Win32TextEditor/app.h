#pragma once
#include <windows.h>
#include "editor.h"
#include "menu.h"
#include "resource.h"

class App {
public:
    static App& getInstance();

    void createMainWindow(HINSTANCE hInstance, int nCmdShow);
    static LRESULT CALLBACK messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    void resizeComponents();
    HWND getMainWindow() const { return mainWindow; }
    Editor& getEditor() { return editor; }

private:
    App();
    HWND mainWindow;
    Editor editor;
    Menu menu;
};
