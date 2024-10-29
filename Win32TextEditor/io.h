#pragma once
#include <string>

std::string openFileDialog();
std::string saveFileDialog();
std::string readFile(const std::string& path);
void writeFile(const std::string& path, const std::string& content);
