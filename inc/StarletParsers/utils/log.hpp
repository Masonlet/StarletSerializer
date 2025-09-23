#pragma once

#include <string>

bool error(const char* caller, const char* function, const std::string& msg);
bool debugLog(const char* caller, const char* function, const std::string& msg, const bool debugOnly = false);