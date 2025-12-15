#pragma once
#include "game.h"
#include "defs.h"
class Object
{
protected:
    /* data */
    Game &_game = Game::GetInstance();
    std::vector<Object *> _children;
    ObjectType _type = ObjectType::NONE;

public:
    Object(/* args */) = default;
    virtual ~Object() = default;
    virtual void init();
    virtual void handleEvents(SDL_Event &event);
    virtual void update(float dt);
    virtual void render();
    virtual void clean();

    virtual void addChild(Object *child) { _children.push_back(child); }
    virtual void removeChild(Object *child)
    {
        _children.erase(std::remove(_children.begin(), _children.end(), child), _children.end());
    }
    ObjectType getType() const { return _type; }
    void setType(ObjectType type) { _type = type; }
};
