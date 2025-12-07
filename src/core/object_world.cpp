#include "object_world.h"
#include "screne.h"
void ObjectWorld::update(float dt)
{
    ObjectScreen::update(dt);
    _render_position = _game.getCurrentScrene()->world2Srceen(_position);
}
void ObjectWorld::setPosition(const glm::vec2 &position)
{
    _position = position;
    _render_position = _game.getCurrentScrene()->world2Srceen(position);
}

void ObjectWorld::setRenderPosition(const glm::vec2 &render_position)
{
    _render_position = render_position;
    _position = _game.getCurrentScrene()->srceen2World(render_position);
}
