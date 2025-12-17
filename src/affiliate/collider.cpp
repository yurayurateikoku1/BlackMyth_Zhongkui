#include "collider.h"

Collider *Collider::addColliderChild(ObjectScreen *parent, glm::vec2 size, ColliderType type)
{
    auto collider = new Collider();
    collider->init();
    collider->setParrent(parent);
    collider->setSize(size);
    parent->addChild(collider);
    return collider;
}

bool Collider::isColliding(Collider *other)
{
    if (!other)
        return false;
    if (_type == ColliderType::Circle && other->_type == ColliderType::Circle)
    {
        auto point1 = _parrent->getPosition() + _offset + _size / 2.0f;
        auto point2 = other->_parrent->getPosition() + other->_offset + other->_size / 2.0f;
        return glm::length(point1 - point2) < (_size.x + other->_size.x) / 2.0f;
    }
    return false;
}
