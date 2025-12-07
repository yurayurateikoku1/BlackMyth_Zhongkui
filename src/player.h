#pragma once
#include "core/actor.h"
class Player : public Actor
{
private:
    /* data */
public:
    virtual void init() override;
    virtual void handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

    void keyboradControl();
    void move(float dt);
    void syncCamera();
};
