#pragma once
#include "../core/object.h"
class Spell;
class Actor;
class Weapon : public Object
{
protected:
    /* data */
    Actor *_parent = nullptr;
    float _cool_down = 0.0f;
    float _mana_cost = 0.0f;
    float _cool_down_timer = 0.0f;

public:
    virtual void update(float dt) override;

    bool canAttack();

    float getCoolDown() const { return _cool_down; }
    void setCoolDown(float cool_down) { _cool_down = cool_down; }

    float getManaCost() const { return _mana_cost; }
    void setManaCost(float mana_cost) { _mana_cost = mana_cost; }

    void setParent(Actor *parent) { _parent = parent; }
    Actor *getParent() { return _parent; }

    void attack(glm::vec2 position, Spell *spell);

private:
};
