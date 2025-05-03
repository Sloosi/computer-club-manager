#pragma ocne

#include <vector>
#include <string>
#include <deque>
#include <map>
#include <exception>

class Error
{
public:
    virtual const char* what() const noexcept = 0;
};

class YouShallNotPassError final : public Error
{
public:
    const char* what() const noexcept override
    {
        return "YouShallNotPass";
    }
};

class NotOpenYetError final : public Error
{
public:
    const char* what() const noexcept override
    {
        return "NotOpenYet";
    }
};

class PlaceIsBusyError final : public Error
{
public:
    const char* what() const noexcept override
    {
        return "PlaceIsBusy";
    }
};

class ClientUnknownError final : public Error
{
public:
    const char* what() const noexcept override
    {
        return "ClientUnknown";
    }
};

class ICanWaitNoLongerError final : public Error
{
public:
    const char* what() const noexcept override
    {
        return "ICanWaitNoLonger!";
    }
};

class ComputerClubManager
{
public:
    ComputerClubManager() = delete;
    ComputerClubManager(const ComputerClubManager&) = delete;
    ComputerClubManager& operator=(const ComputerClubManager&) = delete;
    ComputerClubManager(ComputerClubManager&&) = delete;
    ComputerClubManager& operator=(ComputerClubManager&&) = delete;

    ComputerClubManager(int computerCount, int pricePerHour, int workBegin, int workEnd);
    ~ComputerClubManager() = default;

    void AddClient(int time, const std::string& client);
    void TakeTable(int time, const std::string& client, int tableID);
    void ClientWaiting(int time, const std::string& client);
    void RemoveClient(int time, const std::string& client);

    void EndDay();
    void LogStat() const;
private:
    void RemoveClientInternal(int time, const std::string& client);
    void TakeTableInternal(int time, int tableID);
    void HandleError(int time, const Error& error);
    
    void FreeTable(int time, int tableID);
private:
    int pricePerHour_;
    int workBegin_;
    int workEnd_;

    struct TableInfo
    {
        bool isBusy = false;
        int busyTimeStart = 0;
        int totalBusy = 0;
        size_t totalEarn = 0;
    };

    std::vector<TableInfo> tables_;
    std::deque<std::string> queue_;
    std::map<std::string, int> clients_; 
};
