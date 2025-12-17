#include "object_affiliate.h"

void ObjectAffiliate::setOffsetByAnchor(AnchorType anchor)
{
    _anchor = anchor;
    switch (anchor)
    {
    case AnchorType::TOP_LEFT:
        _offset = glm::vec2(0, 0);
        break;

    case AnchorType::TOP_CENTER:
        _offset = glm::vec2(_size.x / 2.0f, 0);
        break;

    case AnchorType::TOP_RIGHT:
        _offset = glm::vec2(_size.x, 0);
        break;

    case AnchorType::CENTER_LEFT:
        _offset = glm::vec2(0, _size.y / 2.0f);
        break;

    case AnchorType::CENTER:
        _offset = glm::vec2(_size.x / 2.0f, _size.y / 2.0f);
        break;

    case AnchorType::CENTER_RIGHT:
        _offset = glm::vec2(_size.x, _size.y / 2.0f);
        break;

    case AnchorType::BOTTOM_LEFT:
        _offset = glm::vec2(0, _size.y);
        break;

    case AnchorType::BOTTOM_CENTER:
        _offset = glm::vec2(_size.x / 2.0f, _size.y);
        break;

    case AnchorType::BOTTOM_RIGHT:
        _offset = glm::vec2(_size.x, _size.y);
        break;
    default:
        break;
    }
}

void ObjectAffiliate::setSize(const glm::vec2 &size)
{
    _size = size;
    setOffsetByAnchor(_anchor);
}

void ObjectAffiliate::setScale(float scale)
{
    _size *= scale;
    setOffsetByAnchor(_anchor);
}
