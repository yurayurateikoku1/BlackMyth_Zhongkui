#pragma once
#include "raw/weapon.h"
class WeaponThunder : public Weapon
{
private:
public:
    static WeaponThunder *addWeaponThunderChild(Actor *parent, float cool_down, float mana_cost);
    virtual void handleEvents(SDL_Event &event);
};
