#include "ui_mouse.h"

UIMouse *UIMouse::addUIMouseChild(Object *parent, const std::string file_path1, const std::string file_path2, float scale, AnchorType anchor)
{
    auto ui_mouse = new UIMouse();
    ui_mouse->init();
    ui_mouse->_sprite1 = Sprite::addSpriteChild(ui_mouse, file_path1, scale, anchor);
    ui_mouse->_sprite2 = Sprite::addSpriteChild(ui_mouse, file_path2, scale, anchor);
    if (parent)
        parent->addChild(ui_mouse);
    return ui_mouse;
}

void UIMouse::update(float dt)
{
    _timer += dt;
    if (_timer < 0.3f)
    {
        _sprite1->setActive(true);
        _sprite2->setActive(false);
    }
    else if (_timer < 0.6f)
    {
        /* code */
        _sprite1->setActive(false);
        _sprite2->setActive(true);
    }
    else
    {
        _timer = 0;
    }
    setRenderPosition(_game.getMousePosition());
}
