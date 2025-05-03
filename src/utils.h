#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

bool IsNaturalNumber(const std::string& str);
bool IsValidTimeFormat(const std::string& str);
int TimeToMinutes(const std::string& str);
std::string MinutesToTime(int minutes);
std::vector<std::string> splitString(const std::string& input);