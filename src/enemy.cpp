#include "enemy.h"
#include "affiliate/sprite_anim.h"
#include "core/scene.h"
void Enemy::init()
{
    Actor::init();
    _max_speed = 100.0f;
    _anim_normal = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghost-Sheet.png", 3.0f);
    _anim_hurt = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghostHurt-Sheet.png", 3.0f);
    _anim_die = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghostDead-Sheet.png", 3.0f);
    _anim_hurt->setActive(false);
    _anim_die->setActive(false);
    _anim_die->setIsLoop(false);
    _anim_current = _anim_normal;

    _collider = Collider::addColliderChild(this, _anim_current->getSize());
}

void Enemy::update(float dt)
{
    Actor::update(dt);
    aimTarget(_target);
    move(dt);
    attack();
}

void Enemy::aimTarget(Player *target)
{
    if (target == nullptr)
        return;
    auto direction = target->getPosition() - this->getPosition();
    direction = glm::normalize(direction);
    _velocity = direction * _max_speed;
}

void Enemy::changeState(State new_state)
{
    if (_current_state == new_state)
        return;
    _anim_current->setActive(false);
    switch (new_state)
    {
    case State::Normal:
        _anim_current = _anim_normal;
        _anim_current->setActive(true);
        break;
    case State::Hurt:
        _anim_current = _anim_hurt;
        _anim_current->setActive(true);
        break;
    case State::Die:
        _anim_current = _anim_die;
        _anim_current->setActive(true);
        break;
    }
    _current_state = new_state;
}

void Enemy::remove()
{
    if (_anim_die->getIsFinished())
    {
        _need_remove = true;
    }
}

void Enemy::attack()
{
    if (!_collider || _target->getCollider() == nullptr)
        return;
    if (_collider->isColliding(_target->getCollider()))
    {
        SDL_Log("Circle vs Circle");
    }
}
