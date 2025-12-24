#pragma once
#include "../core/object.h"

class Timer : public Object
{
protected:
    float _timer = 0;
    float _interval = 3;
    bool _time_out = false;

public:
    static Timer *addTimerChild(Object *parrent, float interval = 3.0f);
    virtual void update(float dt) override;
    void start() { _is_active = true; }
    void stop() { _is_active = false; }
    bool timeOut();
    void setInterval(float interval) { _interval = interval; }
    float getInterval() const { return _interval; }
    void setTimer(float timer) { _timer = timer; }
    float getTimer() const { return _timer; }

    float getProgress() const { return _timer / _interval; }
};