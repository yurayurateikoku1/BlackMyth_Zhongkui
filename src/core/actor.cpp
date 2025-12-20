#include "actor.h"
#include "scene.h"
#include "../raw/states.h"
#include "../affiliate/affiliate_bar.h"
void Actor::move(float dt)
{
    setPosition(_position + _velocity * dt);
    _position = glm::clamp(_position, glm::vec2(0, 0), _game.getCurrentScene()->getWorldSize());
}

void Actor::update(float dt)
{
    ObjectWorld::update(dt);
    updateHealthBar();
}

void Actor::takeDamage(float damage)
{
    if (!_states)
        return;
    _states->takeDamage(damage);
}

bool Actor::IsAlive() const
{
    if (!_states)
    {
        return true;
    }
    return _states->getIsAlive();
}

void Actor::updateHealthBar()
{
    if (!_states || !_health_bar)
    {
        return;
    }
    _health_bar->setPercentage(_states->getHealth() / _states->getMaxHealth());
}
