#pragma once
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
namespace Time{
    using namespace std::chrono;

    inline uint64_t GetTimeMilliseconds() {
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }
    inline uint64_t GetTimeSeconds(){
        return duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
    }
    inline std::string GetTime_HH_MM_SS_MMM(){
        using namespace std::chrono;

        // get current time
        auto now = system_clock::now();

        // get number of milliseconds for the current second
        // (remainder after division into seconds)
        auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

        // convert to std::time_t in order to convert to std::tm (broken time)
        auto timer = system_clock::to_time_t(now);

        // convert to broken time
        std::tm bt = *std::localtime(&timer);

        std::ostringstream oss;

        oss << std::put_time(&bt, "%H:%M:%S"); // HH:MM:SS
        oss << '.' << std::setfill('0') << std::setw(3) << ms.count();

        return oss.str();

    }
    inline std::string getDate_DD_MM_YYYY(){
        time_t timestamp;
        time(&timestamp);
        struct tm datetime = *localtime(&timestamp);
        std::string t = std::to_string(datetime.tm_mday) + "/" + std::to_string(datetime.tm_mon + 1) + "/" + std::to_string(datetime.tm_year + 1900);
        return t;
    }
}