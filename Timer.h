#ifndef STG_TIMER_H
#define STG_TIMER_H

#include "headers.h"

class Timer {
    static Timer *instance;
    double interval;

    void (*func)();

    static void callback(void *) {
        instance->func();
        Fl::repeat_timeout(instance->interval, callback);
    }

public:
    Timer(double interval, void (*func)()) : interval(interval), func(func) {
        instance = this;
        Fl::add_timeout(interval, callback);
    }
};

#endif //STG_TIMER_H
