#pragma once
#include "core/actor.h"
#include "affiliate/sprite_anim.h"
#include "world/effect.h"
class Player : public Actor
{
private:
    /* data */
    SpriteAnim *_sprite_idle = nullptr;
    SpriteAnim *_sprite_move = nullptr;
    bool _is_moving = false;
    Effect *_effect = nullptr;

public:
    virtual void init() override;
    virtual void handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

    void keyboradControl();

    void syncCamera();

    void checkState();
    void changeState(bool is_moving);
    void checkIsDead();
};
