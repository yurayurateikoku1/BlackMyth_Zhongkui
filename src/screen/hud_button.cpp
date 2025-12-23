#include "hud_button.h"

HUDButton *HUDButton::addHUDButtonChild(Object *parrent, const glm::vec2 &position, const std::string &file_path1, const std::string &file_path2, const std::string &file_path3, float scale, AnchorType anchor)
{
    auto hud_button = new HUDButton();
    hud_button->init();
    hud_button->setRenderPosition(position);
    hud_button->_sprite_normal = Sprite::addSpriteChild(hud_button, file_path1, scale, anchor);
    hud_button->_sprite_hover = Sprite::addSpriteChild(hud_button, file_path2, scale, anchor);
    hud_button->_sprite_press = Sprite::addSpriteChild(hud_button, file_path3, scale, anchor);
    hud_button->_sprite_hover->setActive(false);
    hud_button->_sprite_press->setActive(false);

    if (parrent)
    {
        parrent->addChild(hud_button);
    }
    return hud_button;
}

bool HUDButton::handleEvents(SDL_Event &event)
{
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            if (_is_hover)
            {
                _is_press = true;
                _game.playSound("assets/sound/UI_button08.wav");
                return true;
            }
        }
    }
    else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP)
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            _is_press = false;
            if (_is_hover)
            {
                _is_trigger = true;
                return true;
            }
        }
    }
    return false;
}

void HUDButton::update(float dt)
{
    checkHover();
    checkState();
}

void HUDButton::checkHover()
{
    bool new_hover;
    auto position = _render_position + _sprite_normal->getOffset();
    auto size = _sprite_normal->getSize();
    if (_game.isMouseInRect(position, position + size))
    {
        new_hover = true;
    }
    else
    {
        new_hover = false;
    }
    if (new_hover != _is_hover)
    {
        _is_hover = new_hover;
        if (_is_hover && !_is_press)
            _game.playSound("assets/sound/UI_button12.wav");
    }
}

void HUDButton::checkState()
{
    if (!_is_press && !_is_hover)
    {
        _sprite_normal->setActive(true);
        _sprite_hover->setActive(false);
        _sprite_press->setActive(false);
    }
    else if (!_is_press && _is_hover)
    {
        _sprite_normal->setActive(false);
        _sprite_hover->setActive(true);
        _sprite_press->setActive(false);
    }
    else
    {
        _sprite_normal->setActive(false);
        _sprite_hover->setActive(false);
        _sprite_press->setActive(true);
    }
}

bool HUDButton::getIsTrigger()
{
    if (_is_trigger)
    {
        _is_trigger = false;
        return true;
    }
    return false;
}
