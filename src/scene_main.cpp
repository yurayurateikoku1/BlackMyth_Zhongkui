#include "scene_main.h"
#include "player.h"
#include "enemy.h"
#include "world/effect.h"
#include "spwaner.h"
#include "screen/ui_mouse.h"
#include "world/spell.h"
#include "screen/hud_states.h"
void SceneMain::init()
{
    SDL_HideCursor();
    _word_size = _game.getScreenSize() * 3.0f;
    _camera_position = _word_size / 2.0f - _game.getScreenSize() / 2.0f;
    _player = new Player();
    _player->init();
    _player->setPosition(_word_size / 2.0f);
    addChild(_player);

    _spwaner = new Spwaner();
    _spwaner->init();
    _spwaner->setTarget(_player);
    addChild(_spwaner);

    _ui_mouse = UIMouse::addUIMouseChild(this, "assets/UI/29.png", "assets/UI/30.png", 1.0f, AnchorType::CENTER);

    _hud_states = HUDStates::addHUDStatesChild(this, _player, glm::vec2(30.0f, 30.0f));
}

void SceneMain::update(float dt)
{
    Scene::update(dt);
}

void SceneMain::handleEvents(SDL_Event &event)
{
    Scene::handleEvents(event);
}

void SceneMain::render()
{
    renderBackground();
    Scene::render();
}

void SceneMain::clean()
{
    Scene::clean();
}

void SceneMain::renderBackground()
{
    auto start = -_camera_position;
    auto end = _word_size - _camera_position;
    _game.drawGrid(start, end, 80, SDL_FColor(0.5, 0.5, 0.5, 1));
    _game.drawBoundary(start, end, 5.0f, SDL_FColor(1, 1, 1, 1));
}