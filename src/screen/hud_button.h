#pragma once
#include "../core/object_screen.h"
#include "../affiliate/sprite.h"

class HUDButton : public ObjectScreen
{
private:
    /* data */
protected:
    Sprite *_sprite_normal = nullptr;
    Sprite *_sprite_hover = nullptr;
    Sprite *_sprite_press = nullptr;
    bool _is_hover = false;
    bool _is_press = false;
    bool _is_trigger = false;

public:
    static HUDButton *addHUDButtonChild(Object *parrent, const glm::vec2 &position, const std::string &file_path1, const std::string &file_path2, const std::string &file_path3, float scale = 1.0f, AnchorType anchor = AnchorType::CENTER);
    virtual bool handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;
    void checkHover();
    void checkState();
    Sprite *getSpriteNorml() const { return _sprite_normal; }
    Sprite *getSpriteHover() const { return _sprite_hover; }
    Sprite *getSpritePress() const { return _sprite_press; }

    bool getIsHover() const { return _is_hover; }
    bool getIsPress() const { return _is_press; }
    bool getIsTrigger();
    void setIsHover(bool flag) { _is_hover = flag; }
    void setIsTrigger(bool flag) { _is_trigger = flag; }
    void setIsPress(bool flag) { _is_press = flag; }
};
