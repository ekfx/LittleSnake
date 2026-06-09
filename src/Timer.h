
#ifndef TIMER_H
#define TIMER_H

#include <GLFW/glfw3.h>
#include "Clock.h"

class Timer {
private:
    // Attributes
    float Elapsed;
    float _Delta;

public:
    // Constructor and Destructor
    Timer();
    ~Timer();

    // Functions
    bool Update(Clock& clock, float sec_interval);

};

#endif
