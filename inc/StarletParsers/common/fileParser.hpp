#pragma once

#include <string>
#include <vector>

bool loadFile(std::string& out, const std::string& path);
bool loadBinaryFile(std::vector<unsigned char>& dataOut, const std::string& path);