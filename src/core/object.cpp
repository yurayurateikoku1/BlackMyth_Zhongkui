#include "object.h"

void Object::init()
{
}

bool Object::handleEvents(SDL_Event &event)
{

    for (auto &child : _children)
    {
        if (child->getActive())
        {
            if (child->handleEvents(event))
            {
                return true;
            }
                }
    }
    return false;
}

void Object::update(float dt)
{
    for (auto &child : _object_to_add)
    {
        addChild(child);
    }
    _object_to_add.clear();
    for (auto it = _children.begin(); it != _children.end();)
    {
        auto child = *it;
        if (child->getNeedRemove())
        {
            it = _children.erase(it);
            child->clean();
            delete child;
            child = nullptr;
        }
        else
        {
            if (child->getActive())
            {
                child->update(dt);
            }
            ++it;
        }
    }
}

void Object::render()
{
    for (auto &child : _children)
    {
        if (child->getActive())
        {
            child->render();
        }
    }
}

void Object::clean()
{
    for (auto &child : _children)
    {
        child->clean();
    }
    _children.clear();
}
