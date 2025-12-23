#pragma once
#include "../core/object_affiliate.h"
class TextLabel : public ObjectAffiliate
{
private:
    /* data */
protected:
    TTF_Text *_ttf_text = nullptr;
    std::string _font_path;
    int _font_size = 16;

public:
    static TextLabel *addTextLabelChild(ObjectScreen *parent, const std::string &text, const std::string &font_path, int font_size, AnchorType anchor = AnchorType::CENTER);
    virtual void render() override;
    virtual void clean() override;
    void setFont(const std::string &font_path, int font_size);
    void setFontPath(const std::string &font_path);
    void setFontSize(int font_size);
    void setText(const std::string &ttf_text);

    std::string getText() const { return _ttf_text->text; }

private:
    void updateSize();
};
