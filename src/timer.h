#pragma once
#include "common.h"

struct Timer {
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    std::chrono::duration<float> duration;

    std::string operation_desc;

    Timer(std::string input = "Timer took") {
        start = std::chrono::high_resolution_clock::now();
        operation_desc = input;
    }

    ~Timer() {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;

        float ms = duration.count() * 1000.0f;
        std::cout << operation_desc << " took " << ms << "ms" << std::endl;
    }   
};