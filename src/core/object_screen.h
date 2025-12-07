#pragma once
#include "object.h"

class ObjectScreen : public Object
{
protected:
    /* data */
    glm::vec2 _render_position{0, 0}; // 渲染屏幕位置
public:
    glm::vec2 getRenderPosition() const { return _render_position; }
    virtual void setRenderPosition(const glm::vec2 &render_position) { _render_position = render_position; }
};
