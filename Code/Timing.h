//
// Created by thero on 2025/10/28.
//
#pragma once
#include <chrono>
#include <thread>

namespace timing {

    // Global speed multiplier. 1.0 = real time.
    // Set to 0.05 in tests to make 20s -> 1s, etc.
    extern double SPEED;

    // Scale any duration by SPEED and sleep.
    template <class Rep, class Period>
    inline void sleep_for(std::chrono::duration<Rep, Period> d) {
        using namespace std::chrono;
        const auto ms = duration_cast<milliseconds>(d).count();
        long long scaled = static_cast<long long>(ms * SPEED);
        if (scaled < 0) scaled = 0;
        std::this_thread::sleep_for(milliseconds(scaled));
    }

} // namespace timing

