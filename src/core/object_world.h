#pragma once
#include "object_screen.h"
#include "../affiliate/collider.h"
class ObjectWorld : public ObjectScreen
{
protected:
    glm::vec2 _position{0, 0}; // 世界位置
    Collider *_collider = nullptr;
    /* data */
public:
    virtual void init() override { _type = ObjectType::OBJECT_WORLD; }
    virtual void update(float dt) override;
    virtual glm::vec2 getPosition() const override { return _position; }
    void setPosition(const glm::vec2 &position);
    virtual void setRenderPosition(const glm::vec2 &render_position);

    Collider *getCollider() { return _collider; }
    void setCollider(Collider *collider) { _collider = collider; }

    virtual void takeDamage(float damage) { return; }
};
