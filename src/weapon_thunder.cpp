#include "weapon_thunder.h"
#include "world/spell.h"
#include "core/scene.h"
#include "core/actor.h"
void WeaponThunder::init()
{
    Weapon::init();
    auto scence = _game.getCurrentScene();
    auto pos = glm::vec2(_game.getScreenSize().x - 300, 30);
    _hud_skill = HUDSkill::addHUDSkillChild(scence, "assets/UI/Electric-Icon.png", pos, 0.14f, AnchorType::CENTER);
}
void WeaponThunder::update(float dt)
{
    Weapon::update(dt);
    if (_hud_skill)
    {
        _hud_skill->setPercentage(_cool_down_timer / _cool_down);
    }
}
WeaponThunder *WeaponThunder::addWeaponThunderChild(Actor *parent, float cool_down, float mana_cost)
{
    auto weapon = new WeaponThunder();
    weapon->init();
    weapon->setParent(parent);
    weapon->setCoolDown(cool_down);
    weapon->setManaCost(mana_cost);
    parent->addChild(weapon);
    return weapon;
}
bool WeaponThunder::handleEvents(SDL_Event &event)
{
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        /* code */
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            if (canAttack())
            {
                _game.playSound("assets/sound/big-thunder.mp3");
                auto position = _game.getMousePosition() + _game.getCurrentScene()->getCameraPosition();
                auto spell = Spell::addSpellChild(nullptr, "assets/effect/Thunderstrike w blur.png", position, 60.0f, 3.0f, AnchorType::CENTER);
                attack(position, spell);
                return true;
            }
        }
    }
    return false;
}
