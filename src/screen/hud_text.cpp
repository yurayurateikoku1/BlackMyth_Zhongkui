#include "hud_text.h"

HUDText *HUDText::addHUDTextChild(Object *parent, const std::string &text, const glm::vec2 &render_position, const glm::vec2 &size, const std::string &font_path, int font_size, const std::string &bg_path, AnchorType anchor)
{
    auto hud_text = new HUDText();
    hud_text->init();
    hud_text->setRenderPosition(render_position);
    hud_text->setSpriteBg(Sprite::addSpriteChild(hud_text, bg_path, 1, anchor));
    hud_text->setSize(size);
    hud_text->setTextLabel(TextLabel::addTextLabelChild(hud_text, text, font_path, font_size, anchor));
    if (parent)
    {
        /* code */
        parent->addChild(hud_text);
    }

    return hud_text;
}

void HUDText::setBackground(const std::string &file_path)
{
    if (_sprite_bg)
    {
        _sprite_bg->setTexture(file_path);
    }
    else
    {
        _sprite_bg = Sprite::addSpriteChild(this, file_path, 1, AnchorType::CENTER);
    }
}
