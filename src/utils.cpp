#include "utils.h"

bool IsNaturalNumber(const std::string& str)
{
    if (str.empty()) return false;
    if (str[0] == '0') return false;

    for (char c : str)
    {
        if (!isdigit(c)) 
            return false;
    }
    
    return true;
}

bool IsValidTimeFormat(const std::string& str)
{
    if (str.size() != 5 || str[2] != ':')
        return false;

    std::string hourStr = str.substr(0, 2);
    std::string minuteStr = str.substr(3, 2);

    for (char c : hourStr)
        if (!isdigit(c)) return false;

    for (char c : minuteStr)
        if (!isdigit(c)) return false;

    int hours = std::stoi(hourStr);
    int minutes = std::stoi(minuteStr);

    if (hours < 0 || hours > 23) 
        return false;

    if (minutes < 0 || minutes > 59)  
        return false;
        
    return true;
}

int TimeToMinutes(const std::string& str)
{
    std::string hourStr = str.substr(0, 2);
    std::string minuteStr = str.substr(3, 2);
    
    int hours = std::stoi(hourStr);
    int minutes = std::stoi(minuteStr);

    return hours * 60 + minutes;
}

std::string MinutesToTime(int minutes)
{
    int hours = minutes / 60;
    int mins = minutes % 60;

    std::ostringstream ss;
    ss << std::setw(2) << std::setfill('0') << hours << ":" 
        << std::setw(2) << std::setfill('0') << mins;

    return ss.str();
}

std::vector<std::string> splitString(const std::string& input)
{
    std::vector<std::string> words;
    auto start = input.begin();
    
    while (start != input.end())
    {
        start = std::find_if_not(start, input.end(), [](char c) { return std::isspace(c); });
        
        auto end = std::find_if(start, input.end(), [](char c) { return std::isspace(c); });
        
        if (start != end)
        {
            words.emplace_back(start, end);
        }
        
        start = end;
    }
    
    return words;
}