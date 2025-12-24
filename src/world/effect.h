#pragma once
#include "../core/object_world.h"
#include "../affiliate/sprite_anim.h"
class Effect : public ObjectWorld
{
private:
    SpriteAnim *_sprite = nullptr;
    ObjectWorld *_next_object = nullptr;

    void checkFininsh();

public:
    static Effect *addEffectChild(Object *parent, const std::string &file_path, const glm::vec2 position, float scale = 1.0f, ObjectWorld *next_object = nullptr);
    virtual void update(float dt) override;
    virtual void clean() override;
    void setSpriteAnim(SpriteAnim *sprite)
    {
        _sprite = sprite;
    }
    SpriteAnim *getSpriteAnim() { return _sprite; }

    void setNextObject(ObjectWorld *next_object)
    {
        _next_object = next_object;
    }
    ObjectWorld *getNextObject() { return _next_object; }
};
