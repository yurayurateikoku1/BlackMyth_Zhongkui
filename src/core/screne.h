#pragma once
#include "object.h"
#include <glm/glm.hpp>
class Screne : public Object
{
private:
    /* data */
    glm::vec2 _camera_position = glm::vec2{0}; // 相机位置
    std::vector<Object *> _objects;            // 场景中的物体

public:
    Screne(/* args */) = default;
    ~Screne() = default;
    virtual void init() override {}
    virtual void handleEvents(SDL_Event &event) override {}
    virtual void update(float dt) override {}
    virtual void render() override {}
    virtual void clean() override {}
};
