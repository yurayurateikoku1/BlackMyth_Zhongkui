#pragma once
#include "../core/object_screen.h"
#include "../affiliate/text_label.h"
#include "../affiliate/sprite.h"

class HUDText : public ObjectScreen
{
public:
    static HUDText *addHUDTextChild(Object *parent, const std::string &text, const glm::vec2 &render_position, const glm::vec2 &size, const std::string &font_path = "assets/font/VonwaonBitmap-16px.ttf", int font_size = 32, const std::string &bg_path = "assets/UI/Textfield_01.png", AnchorType anchor = AnchorType::CENTER);
    void setTextLabel(TextLabel *text_label) { _text_label = text_label; }
    void setSpriteBg(Sprite *sprite_bg) { _sprite_bg = sprite_bg; }
    TextLabel *getTextLabel() const { return _text_label; }
    Sprite *getSpriteBg() const { return _sprite_bg; }

    void setBgSizeByText(float margin = 10.0f);
    void setText(const std::string &text) { _text_label->setText(text); }
    std::string getText() const { return _text_label->getText(); }
    void setSize(const glm::vec2 &size)
    {
        _size = size;
        _sprite_bg->setSize(size);
    }
    void setBackground(const std::string &file_path);

protected:
    TextLabel *_text_label = nullptr;
    Sprite *_sprite_bg = nullptr; /* data */
    glm::vec2 _size = glm::vec2(0, 0);

private:
};
