#pragma once
#include "object_world.h"
class States;
class Actor : public ObjectWorld
{
protected:
    States *_states = nullptr;
    glm::vec2 _velocity{0, 0}; //
    float _max_speed = 500.0f;

public:
    void move(float dt);
    glm::vec2 getVelocity() const { return _velocity; }
    void setVelocity(const glm::vec2 &velocity) { _velocity = velocity; }
    float getMaxSpeed() const { return _max_speed; }
    void setMaxSpeed(float max_speed) { _max_speed = max_speed; }

    void setStates(States *states) { _states = states; }
    States *getStates() const { return _states; }
    void takeDamage(float damage);
    bool IsAlive() const;
};
