#pragma once
#include "game.h"
#include "defs.h"
class Object
{
protected:
    /* data */
    Game &_game = Game::GetInstance();
    std::vector<Object *> _object_to_add;
    std::vector<Object *> _children;
    ObjectType _type = ObjectType::NONE;
    bool _is_active = true;
    bool _need_remove = false;

public:
    Object(/* args */) = default;
    virtual ~Object() = default;
    virtual void init();
    virtual void handleEvents(SDL_Event &event);
    virtual void update(float dt);
    virtual void render();
    virtual void clean();

    void safeAddChild(Object *child) { _object_to_add.push_back(child); };
    virtual void addChild(Object *child) { _children.push_back(child); }
    virtual void removeChild(Object *child)
    {
        _children.erase(std::remove(_children.begin(), _children.end(), child), _children.end());
    }
    ObjectType getType() const { return _type; }
    void setType(ObjectType type) { _type = type; }
    void setActive(bool active) { _is_active = active; }
    bool getActive() const { return _is_active; }
    void setNeedRemove(bool need_remove) { _need_remove = need_remove; }
    bool getNeedRemove() const { return _need_remove; }
};
