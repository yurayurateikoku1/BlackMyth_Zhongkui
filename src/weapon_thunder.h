#pragma once
#include "raw/weapon.h"
#include "screen/hud_skill.h"
class WeaponThunder : public Weapon
{
protected:
    HUDSkill *_hud_skill = nullptr;

private:
public:
    virtual void init() override;
    virtual void update(float dt) override;
    static WeaponThunder *addWeaponThunderChild(Actor *parent, float cool_down, float mana_cost);
    virtual bool handleEvents(SDL_Event &event);
};
