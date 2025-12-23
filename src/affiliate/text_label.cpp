#include "text_label.h"

TextLabel *TextLabel::addTextLabelChild(ObjectScreen *parent, const std::string &text, const std::string &font_path, int font_size, AnchorType anchor)
{
    auto text_label = new TextLabel();
    text_label->init();
    text_label->setFont(font_path, font_size);
    text_label->setText(text);
    text_label->setAnchor(anchor);
    text_label->updateSize();
    if (parent)
    {
        parent->addChild(text_label);
        text_label->setParrent(parent);
    }
    return text_label;
}

void TextLabel::render()
{
    ObjectAffiliate::render();
    auto position = _parrent->getRenderPosition() + _offset;
    TTF_DrawRendererText(_ttf_text, position.x, position.y);
}

void TextLabel::clean()
{
    if (!_ttf_text)
        return;
    TTF_DestroyText(_ttf_text);
}

void TextLabel::setFont(const std::string &font_path, int font_size)
{
    _font_path = font_path;
    _font_size = font_size;
    if (!_ttf_text)
        _ttf_text = _game.createTTF_Text("", _font_path, _font_size);
    auto font = _game.getAssetStore()->getFont(_font_path, _font_size);
    TTF_SetTextFont(_ttf_text, font);
    updateSize();
}

void TextLabel::setFontPath(const std::string &font_path)
{
    _font_path = font_path;
    auto font = _game.getAssetStore()->getFont(_font_path, _font_size);
    TTF_SetTextFont(_ttf_text, font);
    updateSize();
}

void TextLabel::setFontSize(int font_size)
{
    font_size = font_size;
    auto font = _game.getAssetStore()->getFont(_font_path, _font_size);
    TTF_SetTextFont(_ttf_text, font);
    updateSize();
}

void TextLabel::setText(const std::string &ttf_text)
{
    TTF_SetTextString(_ttf_text, ttf_text.c_str(), 0);
    updateSize();
}

void TextLabel::updateSize()
{
    int w, h;
    TTF_GetTextSize(_ttf_text, &w, &h);
    setSize(glm::vec2(w, h));
}
