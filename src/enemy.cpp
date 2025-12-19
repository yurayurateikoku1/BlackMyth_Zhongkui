#include "enemy.h"
#include "affiliate/sprite_anim.h"
#include "core/scene.h"
#include "raw/states.h"
Enemy *Enemy::addEnemyChild(Object *parrent, const glm::vec2 &position, Player *target)
{
    auto enemy = new Enemy();
    enemy->init();
    enemy->setPosition(position);
    enemy->setTarget(target);
    if (parrent)
        parrent->addChild(enemy);
    return enemy;
}
void Enemy::init()
{
    Actor::init();
    _max_speed = 100.0f;
    _anim_normal = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghost-Sheet.png", 2.0f);
    _anim_hurt = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghostHurt-Sheet.png", 2.0f);
    _anim_die = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghostDead-Sheet.png", 2.0f);
    _anim_hurt->setActive(false);
    _anim_die->setActive(false);
    _anim_die->setIsLoop(false);
    _anim_current = _anim_normal;

    _collider = Collider::addColliderChild(this, _anim_current->getSize());
    _states = States::addStatesChild(this);
    setType(ObjectType::ENEMY);
}

void Enemy::update(float dt)
{
    Actor::update(dt);
    if (!_target || !_target->getActive()) // 先判空再判活跃
        return;
    aimTarget(_target);
    move(dt);
    attack();
    checkState();
    remove();
}

void Enemy::aimTarget(Player *target)
{
    if (target == nullptr)
        return;
    auto direction = target->getPosition() - this->getPosition();
    direction = glm::normalize(direction);
    _velocity = direction * _max_speed;
}

void Enemy::checkState()
{
    State new_state;
    if (_states->getHealth() <= 0)
        new_state = State::Die;
    else if (_states->getInvincible())
        new_state = State::Hurt;
    else
        new_state = State::Normal;
    if (new_state != _current_state)
        changeState(new_state);
}

void Enemy::changeState(State new_state)
{
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
    if (!_collider || !_target || !_target->getCollider())
        return;
    if (_collider->isColliding(_target->getCollider()))
    {
        if (_states && _target->getStates())
        {
            _target->takeDamage(_states->getDamage());
        }
    }
}