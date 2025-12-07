#pragma once
#include "object_screen.h"
class ObjectWorld : public ObjectScreen
{
protected:
    glm::vec2 _position{0, 0}; // 世界位置
    /* data */
public:
    virtual void update(float dt) override;
    glm::vec2 getPosition() const { return _position; }
    void setPosition(const glm::vec2 &position);
    virtual void setRenderPosition(const glm::vec2 &render_position);
};
