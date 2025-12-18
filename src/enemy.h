#pragma once
#include "player.h"
#include "affiliate/sprite_anim.h"
class Enemy : public Actor
{
private:
    enum class State
    {
        Normal,
        Hurt,
        Die
    };
    Player *_target = nullptr;
    SpriteAnim *_anim_normal = nullptr;
    SpriteAnim *_anim_hurt = nullptr;
    SpriteAnim *_anim_die = nullptr;
    SpriteAnim *_anim_current = nullptr;
    State _current_state = State::Normal;

public:
    static Enemy *addEnemyChild(Object *parrent, const glm::vec2 &position, Player *target);
    virtual void init() override;
    virtual void update(float dt) override;
    void aimTarget(Player *target);
    Player *getTarget() const { return _target; }
    void setTarget(Player *target) { _target = target; }
    void checkState();
    void changeState(State new_state);
    void remove();
    void attack();
};
