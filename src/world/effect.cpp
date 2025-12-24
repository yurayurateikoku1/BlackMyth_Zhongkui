#include "effect.h"
#include "../core/scene.h"
void Effect::checkFininsh()
{
    if (_sprite->getIsFinished())
    {
        _need_remove = true;
        if (_next_object)
        {
            _game.getCurrentScene()->safeAddChild(_next_object);
            _next_object = nullptr;
        }
    }
}

Effect *Effect::addEffectChild(Object *parent, const std::string &file_path, const glm::vec2 position, float scale, ObjectWorld *next_object)
{
    auto effect = new Effect();
    effect->init();
    effect->_sprite = SpriteAnim::addSpriteAnimChild(effect, file_path, scale);
    effect->_sprite->setIsLoop(false);
    effect->setPosition(position);
    effect->setNextObject(next_object);
    if (parent)
        parent->addChild(effect);
    return effect;
}

void Effect::update(float dt)
{
    ObjectWorld::update(dt);
    checkFininsh();
}

void Effect::clean()
{
    ObjectWorld::clean();
    if (_next_object)
    {
        _next_object->clean();
        delete _next_object;
        _next_object = nullptr;
    }
}
