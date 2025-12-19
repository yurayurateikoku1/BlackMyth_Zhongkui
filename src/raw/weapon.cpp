#include "weapon.h"
#include "../core/actor.h"
#include "../world/spell.h"
#include "states.h"
#include "../core/scene.h"
void Weapon::update(float dt)
{
    Object::update(dt);
    _cool_down_timer += dt;
}

bool Weapon::canAttack()
{
    if (_cool_down_timer < _cool_down)
    {
        return false;
    }
    if (!_parent->getStates()->canUseMana(_mana_cost))
    {
        return false;
    }
    return true;
}

void Weapon::attack(glm::vec2 position, Spell *spell)
{
    if (spell == nullptr)
    {
        return;
    }
    _parent->getStates()->useMana(_mana_cost);
    _cool_down_timer = 0.0f;
    spell->setPosition(position);
    _game.getCurrentScene()->safeAddChild(spell);
}
