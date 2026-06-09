#include "Timer.h"

Timer::Timer() 
{
    Elapsed = 0;
}

Timer::~Timer()
{

}

bool Timer::Update(Clock& clock, float ms_interval) 
{
    bool triggered = false;

    _Delta = clock.GetDeltaTime() * 1000.0f;
    Elapsed = Elapsed + _Delta;

    while (Elapsed >= ms_interval) {
        Elapsed = Elapsed - ms_interval;
        triggered = true;
    }
    
    return triggered;
}
