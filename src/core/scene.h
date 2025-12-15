#pragma once
#include "object.h"
#include <glm/glm.hpp>
#include <vector>
#include "object_world.h"
#include "object_screen.h"
class Scene : public Object
{
protected:
    /* data */
    glm::vec2 _camera_position = glm::vec2{0}; // 相机位置
    glm::vec2 _word_size;
    std::vector<ObjectWorld *> _children_world;
    std::vector<ObjectScreen *> _children_screen;

public:
    Scene(/* args */) = default;
    ~Scene() = default;
    virtual void init() override {}
    virtual void handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

    virtual void addChild(Object *child) override;
    virtual void removeChild(Object *child) override;

    glm::vec2 world2Srceen(const glm::vec2 &world_position) const { return world_position - _camera_position; }
    glm::vec2 srceen2World(const glm::vec2 &screen_position) const { return screen_position + _camera_position; }

    glm::vec2 getCameraPosition() const { return _camera_position; }
    void setCameraPosition(const glm::vec2 &camera_position);

    glm::vec2 getWorldSize() const { return _word_size; }
    void setWorldSize(const glm::vec2 &word_size) { _word_size = word_size; }
};
