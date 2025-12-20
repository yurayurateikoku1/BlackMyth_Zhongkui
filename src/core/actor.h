#pragma once
#include "object_world.h"
class States;
class AffiliateBar;
class Actor : public ObjectWorld
{
protected:
    States *_states = nullptr;
    glm::vec2 _velocity{0, 0}; //
    float _max_speed = 500.0f;
    AffiliateBar *_health_bar = nullptr;

public:
    virtual void update(float dt) override;

    virtual void takeDamage(float damage);

    void move(float dt);
    glm::vec2 getVelocity() const { return _velocity; }
    void setVelocity(const glm::vec2 &velocity) { _velocity = velocity; }
    float getMaxSpeed() const { return _max_speed; }
    void setMaxSpeed(float max_speed) { _max_speed = max_speed; }

    void setStates(States *states) { _states = states; }
    States *getStates() const { return _states; }

    void setHealthBar(AffiliateBar *health_bar) { _health_bar = health_bar; }
    AffiliateBar *getHealthBar() const { return _health_bar; }
    bool IsAlive() const;

private:
    void updateHealthBar();
};
