#include "ComputerClubManager.h"

#include <iostream>
#include "utils.h" 

ComputerClubManager::ComputerClubManager(int computerCount, int pricePerHour, int workBegin, int workEnd) :
    pricePerHour_(pricePerHour),
    workBegin_(workBegin),
    workEnd_(workEnd),
    tables_(computerCount)
{
    std::cout << MinutesToTime(workBegin_) << std::endl;
}

void ComputerClubManager::AddClient(int time, const std::string& client)
{
    if(clients_.count(client) != 0)
    {
        HandleError(time, YouShallNotPassError());
        return;
    }
    if(time < workBegin_ || time > workEnd_)
    {
        HandleError(time, NotOpenYetError());
        return;
    }

    clients_.emplace(client, -1);
}

void ComputerClubManager::TakeTable(int time, const std::string& client, int tableID)
{
    if(tables_.at(tableID - 1).isBusy)
    {
        HandleError(time, PlaceIsBusyError());
        return;
    }
    if(clients_.count(client) == 0)
    {
        HandleError(time, ClientUnknownError());
        return;
    }

    auto& table = tables_.at(tableID - 1);
    table.isBusy = true;
    table.busyTimeStart = time;

    clients_.at(client) = tableID;
}

void ComputerClubManager::ClientWaiting(int time, const std::string& client)
{
    for(const auto& table : tables_)
    {
        if(!table.isBusy)
        {
            HandleError(time, ICanWaitNoLongerError());
            return;
        }
    }

    if(queue_.size() > tables_.size())
    {
        RemoveClientInternal(time, client);
        return;
    }

    queue_.push_back(client);
}

void ComputerClubManager::RemoveClient(int time, const std::string& client)
{
    if(clients_.count(client) == 0)
    {
        HandleError(time, ClientUnknownError());
        return;
    }
    
    int tableID = clients_.at(client);
    if(tableID != -1)
    {
        FreeTable(time, tableID);
        TakeTableInternal(time, tableID);
    }

    clients_.erase(client);
}

void ComputerClubManager::EndDay()
{
    for(auto [client, _]: clients_)
    {
        RemoveClientInternal(workEnd_, client);
    }
    std::cout << MinutesToTime(workEnd_) << std::endl;
}

void ComputerClubManager::LogStat() const
{
    for(size_t i = 0; i < tables_.size(); i++)
    {
        const auto& table = tables_.at(i);
        std::cout << i + 1 << " " << table.totalEarn << " "  << MinutesToTime(table.totalBusy) << std::endl;
    }
}

void ComputerClubManager::RemoveClientInternal(int time, const std::string& client)
{
    int tableID = clients_.at(client);
    if(tableID != -1)
    {
        FreeTable(time, tableID);
    }

    clients_.erase(client);

    std::cout << MinutesToTime(time) << " 11 " << client << std::endl;
}

void ComputerClubManager::TakeTableInternal(int time, int tableID)
{
    if(queue_.size() != 0)
    {
        auto client = queue_.front();
        queue_.pop_front();

        auto& table = tables_.at(tableID - 1);
        table.isBusy = true;
        table.busyTimeStart = time;

        clients_.at(client) = tableID;

        std::cout << MinutesToTime(time) << " 12 " << client << " " << tableID << std::endl;
    }
}

void ComputerClubManager::HandleError(int time, const Error & error)
{
    std::cout << MinutesToTime(time) << " 13 " << error.what() << std::endl;
}

void ComputerClubManager::FreeTable(int time, int tableID)
{
    auto& table = tables_.at(tableID - 1);
    int wasBusy = time - table.busyTimeStart;
    size_t wasEarned = (wasBusy / 60) * pricePerHour_;
    if(wasBusy % 60 != 0) wasEarned += pricePerHour_;

    table.isBusy = false;
    table.busyTimeStart = 0;
    table.totalBusy += wasBusy;
    table.totalEarn += wasEarned; 
}
