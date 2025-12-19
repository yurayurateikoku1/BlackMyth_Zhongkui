#include "spell.h"
#include "../core/scene.h"
Spell *Spell::addSpellChild(Object *parent, const std::string &file_path, glm::vec2 positon, float damage, float scale, AnchorType anchor)
{
    auto spell = new Spell();
    spell->init();
    spell->_damage = damage;
    spell->_sprite = SpriteAnim::addSpriteAnimChild(spell, file_path, scale, anchor);
    auto size = spell->_sprite->getSize();
    spell->_collider = Collider::addColliderChild(spell, size, Collider::ColliderType::Circle, anchor);
    spell->_sprite->setIsLoop(false);
    spell->setPosition(positon);
    if (parent)
        parent->addChild(spell);
    return spell;
}
void Spell::update(float dt)
{
    ObjectWorld::update(dt);
    if (_sprite->getIsFinished())
    {
        _need_remove = true;
    }
    attack();
}

void Spell::attack()
{
    auto objects = _game.getCurrentScene()->getChildWorld();
    for (auto &object : objects)
    {
        if (object->getType() != ObjectType::ENEMY)
            continue;
        if (_collider && object->getCollider() && _collider->isColliding(object->getCollider()))
        {
            object->takeDamage(_damage);
        }
    }
}
