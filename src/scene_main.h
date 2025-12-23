#pragma once
#include "core/scene.h"
class Player;
class Spwaner;
class UIMouse;
class HUDStates;
class HUDText;
class HUDButton;
class SceneMain : public Scene
{
private:
    /* data */
    void renderBackground();

    void updateScore();

    Player *_player = nullptr;
    Spwaner *_spwaner = nullptr;
    UIMouse *_ui_mouse = nullptr;
    HUDStates *_hud_states = nullptr;
    HUDText *_hud_text_score = nullptr;

    HUDButton *_button_pause = nullptr;
    HUDButton *_button_restart = nullptr;
    HUDButton *_button_back = nullptr;

public:
    SceneMain(/* args */) = default;
    ~SceneMain() = default;
    virtual void init() override;
    virtual bool handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

    void checkButtonPause();
    void checkButtonRestart();
    void checkButtonBack();
};
