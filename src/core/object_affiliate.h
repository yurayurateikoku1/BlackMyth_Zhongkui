#pragma once
#include "object_screen.h"

class ObjectAffiliate : public Object
{
protected:
    /* data */
    ObjectScreen *_parrent = nullptr;    // 父节点
    glm::vec2 _offset = glm::vec2(0, 0); // 偏移量
    glm::vec2 _size = glm::vec2(0, 0);   // 尺寸
    virtual void init() override {}

public:
    ObjectScreen *getParrent() { return _parrent; }
    void setParrent(ObjectScreen *parrent) { this->_parrent = parrent; }
    glm::vec2 getOffset() { return _offset; }
    void setOffset(glm::vec2 offset) { this->_offset = offset; }
    glm::vec2 getSize() { return _size; }
    void setSize(glm::vec2 size) { this->_size = size; }
};
