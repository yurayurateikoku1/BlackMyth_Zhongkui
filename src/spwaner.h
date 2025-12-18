#pragma once
#include "core/object.h"
class Player;
class Spwaner : public Object
{
protected:
    /* data */
    int _num = 20;
    float _timer = 0.0f;
    float _interval = 2.0f;
    Player *_target = nullptr;

public:
    virtual void update(float dt) override;

    void setNum(int num) { _num = num; }
    void setInterval(float interval) { _interval = interval; }
    void setTimer(float timer) { _timer = timer; }
    int getNum() const { return _num; }
    float getInterval() const { return _interval; }
    float getTimer() const { return _timer; }
    Player *getTarget() const { return _target; };
    void setTarget(Player *target) { _target = target; }
};
