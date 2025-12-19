#pragma once
#include "../core/object_screen.h"
#include "../affiliate/sprite.h"

class UIMouse : public ObjectScreen
{
protected:
    /* data */
    Sprite *_sprite1 = nullptr;
    Sprite *_sprite2 = nullptr;
    float _timer = 0.0f;

public:
    static UIMouse *addUIMouseChild(Object *parent, const std::string file_path1, const std::string file_path2, float scale = 1.0f, AnchorType anchor = AnchorType::CENTER);
    virtual void update(float dt) override;
    Sprite *getSprite1() const { return _sprite1; };
    Sprite *getSprite2() const { return _sprite2; };
    void setSprite1(Sprite *sprite) { _sprite1 = sprite; }
    void setSprite2(Sprite *sprite) { _sprite2 = sprite; }
};
