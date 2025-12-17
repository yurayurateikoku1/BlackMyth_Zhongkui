#include "object.h"

void Object::init()
{
}

void Object::handleEvents(SDL_Event &event)
{
    for (auto &child : _children)
    {
        if (child->getActive())
        {
            child->handleEvents(event);
        }
    }
}

void Object::update(float dt)
{
    for (auto it = _children.begin(); it != _children.end();)
    {
        auto child = *it;
        if (child->getNeedRemove())
        {
            it = _children.erase(it);
            child->clean();
            delete child;
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
