#include "collider.h"

void Collider::render()
{
#ifdef DEBUG_MODE
    ObjectAffiliate::render();
    auto pos = _parrent->getRenderPosition() + _offset;
    _game.renderFillCircle(pos, _size, 0.3f);
#endif
}

Collider *Collider::addColliderChild(ObjectScreen *parent, glm::vec2 size, ColliderType type, AnchorType anchor)
{
    auto collider = new Collider();
    collider->init();
    collider->setAnchor(anchor);
    collider->setParrent(parent);
    collider->setSize(size);
    collider->setType(type);
    collider->setOffsetByAnchor(anchor);
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
