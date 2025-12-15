#include "player.h"
#include "core/scene.h"
void Player::init()
{
    Actor::init();
}

void Player::handleEvents(SDL_Event &event)
{
    Actor::handleEvents(event);
}

void Player::update(float dt)
{
    Actor::update(dt);
    keyboradControl();
    move(dt);
    _velocity *= 0.9f;
    syncCamera();
}

void Player::render()
{
    Actor::render();
    _game.drawBoundary(_render_position, _render_position + glm::vec2(20, 20), 5.0f, {1.0, 0.0, 0.0, 1.0});
}

void Player::clean()
{
    Actor::clean();
}

void Player::keyboradControl()
{

    auto currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_W])
    {
        /* code */
        _velocity.y = -_max_speed;
    }
    if (currentKeyStates[SDL_SCANCODE_S])
    {
        _velocity.y = _max_speed;
    }

    if (currentKeyStates[SDL_SCANCODE_A])
    {
        /* code */
        _velocity.x = -_max_speed;
    }
    if (currentKeyStates[SDL_SCANCODE_D])
    {
        _velocity.x = _max_speed;
    }
}

void Player::move(float dt)
{
    setPosition(_position + _velocity * dt);
    _position = glm::clamp(_position, glm::vec2(0, 0), _game.getCurrentScene()->getWorldSize());
}

void Player::syncCamera()
{
    _game.getCurrentScene()->setCameraPosition(_position - _game.getScreenSize() / 2.0f);
}
