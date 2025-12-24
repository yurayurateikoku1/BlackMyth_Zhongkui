#include "timer.h"

Timer *Timer::addTimerChild(Object *parrent, float interval)
{
    Timer *timer = new Timer();
    timer->setInterval(interval);
    if (parrent)
    {
        /* code */
        parrent->addChild(timer);
    }
    timer->setActive(false);
    return timer;
}

void Timer::update(float dt)
{
    _timer += dt;
    if (_timer >= _interval)
    {
        _timer = 0.0f;
        _time_out = true;
    }
}

bool Timer::timeOut()
{
    if (_time_out)
    {
        _time_out = false;
        return true; /* code */
    }
    return false;
}
