#pragma once
#include "core/scene.h"
class HUDButton;
class HUDText;
class SceneTitle : public Scene
{
private:
    /* data */
    void renderBackground();
    void updateColor();
    void checkButtonQuit();
    void checkButtonStart();
    void checkButtonCredists();

protected:
    SDL_FColor _boundary_color{0.5, 0.5, 0.5, 1};
    float _color_timer = 0;
    HUDButton *_button_start = nullptr;
    HUDButton *_button_credists = nullptr;
    HUDButton *_button_exit = nullptr;
    HUDText *_credists_text = nullptr;

public:
    virtual void init() override;
    virtual bool handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;
};
