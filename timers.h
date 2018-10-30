#ifndef TIMERS_H
#define TIMERS_H

#include <windows.h>

class timer{
public:
    timer(){
        QueryPerformanceFrequency(&frequency);
    }
    const double operator()(){
        //return the time
        return (double)((t_end.QuadPart - t_start.QuadPart) * 1000.0 / frequency.QuadPart);
    }
    void start(){ //set start time
        QueryPerformanceCounter(&t_start);
    }
    void end(){ //set end time
        QueryPerformanceCounter(&t_end);
    }
private:
    LARGE_INTEGER frequency;
    LARGE_INTEGER t_start, t_end;
};


#endif // TIMERS_H
