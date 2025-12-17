#include "actor.h"
#include "scene.h"

void Actor::move(float dt)
{
    setPosition(_position + _velocity * dt);
    _position = glm::clamp(_position, glm::vec2(0, 0), _game.getCurrentScene()->getWorldSize());
}