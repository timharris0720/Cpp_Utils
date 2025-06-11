#pragma once
#include <chrono>

namespace Time{
    using namespace std::chrono;

    uint64_t GetTimeMilliseconds() {
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }
    uint64_t GetTimeSeconds(){
        return duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
    }

}