#include "hud_skill.h"
#include "../affiliate/sprite.h"
HUDSkill *HUDSkill::addHUDSkillChild(Object *parent, const std::string &file_path, const glm::vec2 &position, float scale, AnchorType anchor)
{
    auto hud_skill = new HUDSkill();
    hud_skill->init();
    hud_skill->_icon = Sprite::addSpriteChild(hud_skill, file_path, scale, anchor);
    hud_skill->setRenderPosition(position);
    if (parent)
    {
        /* code */
        parent->addChild(hud_skill);
    }

    return hud_skill;
}

void HUDSkill::render()
{
    SDL_SetTextureColorModFloat(_icon->getTexture().texture, 0.3f, 0.3f, 0.3f);
    auto position = getRenderPosition() + _icon->getOffset();
    _game.renderTexture(_icon->getTexture(), position, _icon->getSize());
    SDL_SetTextureColorModFloat(_icon->getTexture().texture, 1.0f, 1.0f, 1.0f);
    ObjectScreen::render();
}

void HUDSkill::setPercentage(float percentage)
{
    percentage = glm::clamp(percentage, 0.0f, 1.0f);
    _percentage = percentage;
    if (_icon)
    {
        /* code */
        _icon->setPercentage(glm::vec2(1.0f, percentage));
    }
}
