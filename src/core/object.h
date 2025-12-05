#pragma once
#include "game.h"
class Object
{
private:
    /* data */
    Game &_game = Game::GetInstance();

public:
    Object(/* args */) = default;
    virtual ~Object() = default;
    virtual void init() {}
    virtual void handleEvents(SDL_Event &event) {}
    virtual void update(float dt) {}
    virtual void render() {}
    virtual void clean() {}
};
