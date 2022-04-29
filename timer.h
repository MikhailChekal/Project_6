//
// Created by misha on 14.02.2022.
//

#ifndef PROJECT_2_TIMER_H
#define PROJECT_2_TIMER_H

#endif //PROJECT_2_TIMER_H

#include <iostream>
#include <chrono>
#include <cmath>

using namespace std::chrono;

template <class T>
class Timer {

private:
    steady_clock::time_point start = steady_clock::now();
    int dur = 0;
public:
    Timer() {};
    ~Timer() {
    }
    void pause(){ // pause и cont всегда должны идти вместе
        dur += int(duration_cast<T>(steady_clock::now() - start).count());
        std::cout << dur << std::endl;
    };
    int prt(){
        dur = int(duration_cast<T>(steady_clock::now() - start).count());
        std::cout << dur << std::endl;
        start = steady_clock::now();
        return dur;

    };
    int silent_prt(){
        dur = int(duration_cast<T>(steady_clock::now() - start).count());
        start = steady_clock::now();
        return dur;
    }
};