#include "screne.h"

void Screne::setCameraPosition(const glm::vec2 &camera_position)
{
    _camera_position = camera_position;
    _camera_position = glm::clamp(_camera_position, glm::vec2(-30), _word_size - _game.getScreenSize() + glm::vec2(30));
}