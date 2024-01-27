// Author: Jamie Wendle

#include "Clock.h"
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <tuple>


const std::string time12hrFormat = "%I:%M:%S %p";
const std::string time24hrFormat = "%H:%M:%S";

Clock::Clock() {
    SetCurrentTime();
}

void Clock::SetCurrentTime() {
    now = std::chrono::system_clock::now();
    now_c = std::chrono::system_clock::to_time_t(now);
    localtime_s(&now_tm, &now_c);
}

std::tuple<std::string, std::string> Clock::FormatTime(const std::string& formatSpecifier) const {
    std::ostringstream oss;
    std::string format;
    std::string title;

    if (formatSpecifier == "12") {
        format = time12hrFormat;
        title = "12-Hour Clock";
    }
    else if (formatSpecifier == "24") {
        format = time24hrFormat;
        title = "24-Hour Clock";
    }
    else {
        format = time24hrFormat; // Default to 24-hour format
        title = "24-Hour Clock";
    }

    oss << std::put_time(&now_tm, format.c_str());
    return std::make_tuple(title, oss.str());
}

void Clock::AddOneHour() {
    now_c += 3600; // Add one hour in seconds
    localtime_s(&now_tm, &now_c);
}

void Clock::AddOneMinute() {
    now_c += 60; // Add one minute in seconds
    localtime_s(&now_tm, &now_c);
}

void Clock::AddOneSecond() {
    now_c += 1; // Add one second
    localtime_s(&now_tm, &now_c);
}

void Clock::ResyncTime() {
    SetCurrentTime(); // Resynchronize with the system clock
}

std::tuple<std::tuple<std::string, std::string>, std::tuple<std::string, std::string>> Clock::GetTime() {
    this->AddOneSecond();

    auto time12 = FormatTime("12");
    auto time24 = FormatTime("24");
    return std::make_tuple(time12, time24);
}
