#pragma once
#include "object_world.h"
class Actor : public ObjectWorld
{
protected:
    glm::vec2 _velocity{0, 0}; //
    float _max_speed = 500.0f;

public:
    glm::vec2 getVelocity() const { return _velocity; }
    void setVelocity(const glm::vec2 &velocity) { _velocity = velocity; }
    float getMaxSpeed() const { return _max_speed; }
    void setMaxSpeed(float max_speed) { _max_speed = max_speed; }
};
