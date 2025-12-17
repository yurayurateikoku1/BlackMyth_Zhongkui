#include "actor.h"
#include "scene.h"
#include "../raw/states.h"
void Actor::move(float dt)
{
    setPosition(_position + _velocity * dt);
    _position = glm::clamp(_position, glm::vec2(0, 0), _game.getCurrentScene()->getWorldSize());
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
