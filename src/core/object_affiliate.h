#pragma once
#include "object_screen.h"

class ObjectAffiliate : public Object
{
protected:
    /* data */
    ObjectScreen *_parrent = nullptr;        // 父节点
    glm::vec2 _offset = glm::vec2(0, 0);     // 偏移量
    glm::vec2 _size = glm::vec2(0, 0);       // 尺寸
    AnchorType _anchor = AnchorType::CENTER; // 锚点

public:
    void setOffsetByAnchor(AnchorType anchor);
    virtual void init() override {}
    ObjectScreen *getParrent() { return _parrent; }
    void setParrent(ObjectScreen *parrent) { _parrent = parrent; }
    glm::vec2 getOffset() { return _offset; }
    void setOffset(const glm::vec2 &offset) { _offset = offset; }
    glm::vec2 getSize() { return _size; }
    void setSize(const glm::vec2 &size);
    void setScale(float scale);
    AnchorType getAnchor() const { return _anchor; }
    void setAnchor(AnchorType anchor) { _anchor = anchor; };
};
