#pragma once
#include "../core/object_affiliate.h"

class Collider : public ObjectAffiliate
{
protected:
    /* data */
    enum class ColliderType
    {
        Circle, //_size的x轴为直径，默认y=x;
        Rectangle
    };
    ColliderType _type = ColliderType::Circle;

public:
    static Collider *addColliderChild(ObjectScreen *parent, glm::vec2 size, ColliderType type = ColliderType::Circle);
    bool isColliding(Collider *other);
    ColliderType getType() const { return _type; };
    void setType(ColliderType type) { _type = type; };
};
