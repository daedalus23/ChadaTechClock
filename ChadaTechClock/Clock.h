// Author: Jamie Wendle

#pragma once

#include <chrono>
#include <string>
#include <tuple>

class Clock {
private:
    std::chrono::system_clock::time_point now; // Stores the current time as time_point
    std::time_t now_c;                         // Stores the current time as time_t
    std::tm now_tm;                            // Stores the current local time as tm structure

public:
    Clock();

    void SetCurrentTime();
    std::tuple<std::string, std::string> FormatTime(const std::string& formatSpecifier) const;
    std::tuple<std::tuple<std::string, std::string>, std::tuple<std::string, std::string>> GetTime();

    void AddOneHour();
    void AddOneMinute();
    void AddOneSecond();
    void ResyncTime();
};
