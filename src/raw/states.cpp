#include "states.h"

States *States::addStatesChild(Actor *parent, float max_health, float max_mana, float damage, float mana_regen)
{
    States *states = new States();
    states->_parent = parent;
    states->_max_health = max_health;
    states->_health = max_health;
    states->_max_mana = max_mana;
    states->_mana = max_mana;
    states->_damage = damage;
    states->_mana_regen = mana_regen;
    parent->addChild(states);
    return states;
}

void States::update(float dt)
{
    Object::update(dt);
    regenMana(dt);
    if (_is_invincible)
    {
        _invincible_timer += dt;
        if (_invincible_timer >= _invincible_time)
        {
            _is_invincible = false;
            _invincible_timer = 0.0f;
        }
    }
}

bool States::canUseMana(float mana_cost)
{
    return _mana >= mana_cost;
}

void States::useMana(float mana_cost)
{
    _mana -= mana_cost;
    if (_mana < 0)
    {
        _mana = 0;
    }
}

void States::takeDamage(float damage)
{
    if (_is_invincible)
        return;
    _health -= damage;
    if (_health < 0)
    {
        _health = 0;
        _is_alive = false;
    }
    _is_invincible = true;
    _invincible_timer = 0.0f;
}

void States::regenMana(float dt)
{
    _mana += _mana_regen * dt;
    if (_mana > _max_mana)
    {
        _mana = _max_mana;
    }
}
