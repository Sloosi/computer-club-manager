#include <iostream>
#include <fstream>
#include <string>

#include "utils.h"
#include "ComputerClubManager.h"

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        std::cerr << "Invalid argument list!\n"
            << "Please specify the source file!" << std::endl;

        return 1;
    }

    std::ifstream input_file(argv[1]);
    if(!input_file.is_open())
    {
        std::cerr << "The file cannot be opened!\n"
        << "Please make sure that the file path is correct!" << std::endl; 
        
        return 1;
    }

    int computerCount = 0;
    int pricePerHour = 0;
    int workBegin = 0;
    int workEnd = 0;

    std::string line;

    //Read and Validate computerCount data from file
    if(std::getline(input_file, line))
    {
        if(!IsNaturalNumber(line))
        {
            std::cout << line << std::endl;
            return 1;
        }

        computerCount = std::stoi(line);
    }
    else
    {
        return 1;
    }

    //Read and Validate working hour data from file
    if(std::getline(input_file, line))
    {
        size_t first_beg = line.find_first_not_of(' ');
        size_t first_end = line.find(' ', first_beg);
        size_t second_beg = line.find_first_not_of(' ', first_end);
        size_t second_end = line.find(' ', second_beg);

        std::string first = line.substr(first_beg, first_end);
        std::string second = 
            (second_beg != std::string::npos) ? line.substr(second_beg, second_end) : "";

        if(!IsValidTimeFormat(first) || !IsValidTimeFormat(second))
        {
            std::cout << line << std::endl;
            return 1;
        }

        workBegin = TimeToMinutes(first);
        workEnd = TimeToMinutes(second);

        if(workEnd <= workBegin)
        {
            std::cout << line << std::endl;
            return 1;
        }
    }
    else
    {
        return 1;
    }

    //Read and Validate pricePerHour data from file
    if(std::getline(input_file, line))
    {
        if(!IsNaturalNumber(line))
        {
            std::cout << line << std::endl;
            return 1;
        }

        pricePerHour = std::stoi(line);
    }
    else
    {
        return 1;
    }

    ComputerClubManager manager(computerCount, pricePerHour, workBegin, workEnd);

    int lastRequestTime = 0;
    while(std::getline(input_file, line))
    {
        std::cout << line << std::endl;
        auto words = splitString(line);
        if(words.size() < 3 || !IsValidTimeFormat(words.at(0)) || !IsNaturalNumber(words.at(1)))
        {
            return 1;
        }

        int curRequestTime = TimeToMinutes(words.at(0));
        if(lastRequestTime >= curRequestTime) return 1;

        lastRequestTime = curRequestTime;
        
        int RequestID = std::stoi(words.at(1));

        if(RequestID == 1)
        {
            if(words.size() != 3) return 1;
            
            manager.AddClient(curRequestTime, words.at(2));
        }
        else if(RequestID == 2)
        {
            if(words.size() != 4 || !IsNaturalNumber(words.at(3))) return 1;
            
            int tableID = std::stoi(words.at(3));
            if(tableID < 1 || tableID > computerCount) return 1;

            manager.TakeTable(curRequestTime, words.at(2), tableID);
        }
        else if(RequestID == 3)
        {
            if(words.size() != 3) return 1;

            manager.ClientWaiting(curRequestTime, words.at(2));
        }
        else if(RequestID == 4)
        {
            if(words.size() != 3) return 1;
            manager.RemoveClient(curRequestTime, words.at(2));
        }
        else
        {
            return 1;
        }
    }
    input_file.close();
    
    manager.EndDay();
    manager.LogStat();
    return 0;
}