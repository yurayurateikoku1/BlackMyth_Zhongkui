#include "scene.h"

bool Scene::handleEvents(SDL_Event &event)
{

    for (auto &child : _children_screen)
    {
        if (child->getActive())
        {
            if (child->handleEvents(event))
            {
                return true;
            }
        }
    }
    if (_is_pause)
    {
        return false;
    }
    Object::handleEvents(event);
    for (auto &child : _children_world)
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

void Scene::update(float dt)
{
    if (!_is_pause)
    {
        Object::update(dt);
        for (auto it = _children_world.begin(); it != _children_world.end();)
        {
            auto child = *it;
            if (child->getNeedRemove())
            {
                it = _children_world.erase(it);
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

    for (auto it = _children_screen.begin(); it != _children_screen.end();)
    {
        auto child = *it;
        if (child->getNeedRemove())
        {
            it = _children_screen.erase(it);
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

void Scene::render()
{
    Object::render();
    for (auto &child : _children_world)
    {
        if (child->getActive())
        {
            child->render();
        }
    }
    for (auto &child : _children_screen)
    {
        if (child->getActive())
        {
            child->render();
        }
    }
}

void Scene::clean()
{
    Object::clean();
    for (auto &child : _children_world)
    {
        child->clean();
    }
    _children_world.clear();
    for (auto &child : _children_screen)
    {
        child->clean();
    }
    _children_screen.clear();
}

void Scene::addChild(Object *child)
{
    switch (child->getType())
    {
    case ObjectType::OBJECT_WORLD:
    case ObjectType::ENEMY:
        /* code */
        _children_world.push_back(dynamic_cast<ObjectWorld *>(child));
        break;
    case ObjectType::OBJECT_SCREEN:
        /* code */
        _children_screen.push_back(dynamic_cast<ObjectScreen *>(child));
        break;
    default:
        _children.push_back(child);
        break;
    }
}

void Scene::removeChild(Object *child)
{
    switch (child->getType())
    {
    case ObjectType::OBJECT_WORLD:
    case ObjectType::ENEMY:
        /* code */
        _children_world.erase(std::remove(_children_world.begin(), _children_world.end(), dynamic_cast<ObjectScreen *>(child)), _children_world.end());
        break;
    case ObjectType::OBJECT_SCREEN:
        /* code */
        _children_screen.erase(std::remove(_children_screen.begin(), _children_screen.end(), dynamic_cast<ObjectScreen *>(child)), _children_screen.end());
        break;
    default:
        _children.erase(std::remove(_children.begin(), _children.end(), child), _children.end());
        break;
    }
}

void Scene::pause()
{
    _is_pause = true;
    _game.pauseSound();
    _game.pauseMusic();
}

void Scene::resume()
{
    _is_pause = false;
    _game.resumeSound();
    _game.resumeMusic();
}

void Scene::setCameraPosition(const glm::vec2 &camera_position)
{
    _camera_position = camera_position;
    _camera_position = glm::clamp(_camera_position, glm::vec2(-30), _word_size - _game.getScreenSize() + glm::vec2(30));
}

void Scene::saveData(const std::string &file_path)
{
}

void Scene::loadData(const std::string &file_path)
{
}