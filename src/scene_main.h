#pragma once
#include "core/scene.h"
class Player;
class Spwaner;
class SceneMain : public Scene
{
private:
    /* data */
    void renderBackground();

    Player *_player = nullptr;
    Spwaner *_spwaner = nullptr;

public:
    SceneMain(/* args */) = default;
    ~SceneMain() = default;
    virtual void init() override;
    virtual void handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;
};
