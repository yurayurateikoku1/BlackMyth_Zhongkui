#pragma once
#include "raw/weapon.h"
class WeaponThunder : public Weapon
{
private:
public:
    virtual void handleEvents(SDL_Event &event);
};
