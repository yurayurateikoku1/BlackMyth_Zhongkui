#include "hud_states.h"
#include "../core/actor.h"
#include "../raw/states.h"
#include "../affiliate/sprite.h"
void HUDStates::init()
{
    ObjectScreen::init();
    _health_bar_bg = Sprite::addSpriteChild(this, "assets/UI/bar_bg.png", 3.0f, AnchorType::CENTER_LEFT);
    _health_bar_bg->setOffset(_health_bar_bg->getOffset() + glm::vec2(30, 0));
    _health_bar = Sprite::addSpriteChild(this, "assets/UI/bar_red.png", 3.0f, AnchorType::CENTER_LEFT);
    _health_bar->setOffset(_health_bar_bg->getOffset() + glm::vec2(0, 0));
    _health_icon = Sprite::addSpriteChild(this, "assets/UI/Red Potion.png", 0.5f, AnchorType::CENTER_LEFT);

    _mana_bar_bg = Sprite::addSpriteChild(this, "assets/UI/bar_bg.png", 3.0f, AnchorType::CENTER_LEFT);
    _mana_bar_bg->setOffset(_mana_bar_bg->getOffset() + glm::vec2(300, 0));
    _mana_bar = Sprite::addSpriteChild(this, "assets/UI/bar_blue.png", 3.0f, AnchorType::CENTER_LEFT);
    _mana_bar->setOffset(_mana_bar->getOffset() + glm::vec2(300, 0));
    _mana_icon = Sprite::addSpriteChild(this, "assets/UI/Blue Potion.png", 0.5f, AnchorType::CENTER_LEFT);
    _mana_icon->setOffset(_mana_icon->getOffset() + glm::vec2(270, 0));
}
void HUDStates::update(float dt)
{
    ObjectScreen::update(dt);
    updateHealthBar();
    updateManaBar();
}

HUDStates *HUDStates::addHUDStatesChild(Object *parent, Actor *target, const glm::vec2 &render_position)
{
    HUDStates *hud_states = new HUDStates();
    hud_states->init();
    hud_states->setRenderPosition(render_position);
    hud_states->setTarget(target);
    if (parent)
        parent->addChild(hud_states);
    return hud_states;
}

void HUDStates::updateHealthBar()
{
    if (!_target || !_health_bar || !_target->getStates())
    {
        return;
    }
    _health_bar->setPercentage(glm::vec2(_target->getStates()->getHealth() / _target->getStates()->getMaxHealth(), 1.0f));
}

void HUDStates::updateManaBar()
{
    if (!_target || !_mana_bar || !_target->getStates())
    {
        return;
    }
    _mana_bar->setPercentage(glm::vec2(_target->getStates()->getMana() / _target->getStates()->getMaxMana(), 1.0f));
}
