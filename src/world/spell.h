#pragma once
#include "../core/object_world.h"
#include "../affiliate/sprite_anim.h"
class Spell : public ObjectWorld
{
protected:
    SpriteAnim *_sprite = nullptr;
    float _damage = 60.0f;

public:
    static Spell *addSpellChild(Object *parent, const std::string &file_path, glm::vec2 positon, float damage, float scale = 1.0f, AnchorType anchor = AnchorType::CENTER);
    void update(float dt) override;
    void setSpriteAinm(SpriteAnim *sprite) { _sprite = sprite; }
    void setDamage(float damage) { _damage = damage; }
    float getDamage() const { return _damage; }

private:
    void attack();
};