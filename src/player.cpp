#include "player.h"
#include "core/scene.h"
#include "affiliate/sprite_anim.h"
#include "affiliate/collider.h"
#include "raw/states.h"
void Player::init()
{
    Actor::init();
    _max_speed = 500.0f;
    _sprite_idle = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ZhongKui-idle.png", 1.0f);
    _sprite_move = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ZhongKui-move.png", 1.0f);
    _sprite_move->setActive(false);

    _collider = Collider::addColliderChild(this, _sprite_idle->getSize());
    _states = States::addStatesChild(this);

    _effect = Effect::addEffectChild(nullptr, "assets/effect/1764.png", glm::vec2(0), 2.0f);
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
    checkState();
    syncCamera();
    checkIsDead();
    // IsAlive();
}

void Player::render()
{
    Actor::render();
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

void Player::syncCamera()
{
    _game.getCurrentScene()->setCameraPosition(_position - _game.getScreenSize() / 2.0f);
}

void Player::checkState()
{

    if (_velocity.x < 0)
    {
        _sprite_idle->setFlip(true);
        _sprite_move->setFlip(true);
    }
    else if (_velocity.x > 0)
    {
        _sprite_idle->setFlip(false);
        _sprite_move->setFlip(false);
    }
    bool new_is_moving = glm::length(_velocity) > 0.1f;
    if (new_is_moving != _is_moving)
    {
        _is_moving = new_is_moving;
        changeState(_is_moving);
    }
}

void Player::changeState(bool is_moving)
{
    if (is_moving)
    {
        _sprite_idle->setActive(false);
        _sprite_move->setActive(true);
        _sprite_move->setCurrentFrame(_sprite_idle->getCurrentFrame());
        _sprite_move->setFrameTime(_sprite_idle->getFrameTime());
    }
    else
    {
        _sprite_idle->setActive(true);
        _sprite_move->setActive(false);
        _sprite_idle->setCurrentFrame(_sprite_move->getCurrentFrame());
        _sprite_idle->setFrameTime(_sprite_move->getFrameTime());
    }
}

void Player::checkIsDead()
{
    if (!_states->getIsAlive())
    {
        _game.getCurrentScene()->safeAddChild(_effect);
        _effect->setPosition(getPosition());
        setActive(false);
    }
}
