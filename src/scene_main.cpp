#include "scene_main.h"
#include "player.h"
#include "enemy.h"
#include "world/effect.h"
#include "spwaner.h"
#include "screen/ui_mouse.h"
#include "world/spell.h"
#include "screen/hud_states.h"
#include "screen/hud_text.h"
void SceneMain::init()
{
    SDL_HideCursor();
    _game.playMusice("assets/bgm/OhMyGhost.ogg");
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

    _hud_states = HUDStates::addHUDStatesChild(this, _player, glm::vec2(30.0f, 30.0f));

    _hud_text_score = HUDText::addHUDTextChild(this, "Score:0", glm::vec2(_game.getScreenSize().x - 120.0f, 30.0f), glm::vec2(200, 50));

    _ui_mouse = UIMouse::addUIMouseChild(this, "assets/UI/29.png", "assets/UI/30.png", 1.0f, AnchorType::CENTER);
}

void SceneMain::update(float dt)
{
    Scene::update(dt);
    updateScore();
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

void SceneMain::updateScore()
{
    _hud_text_score->setText("Score:" + std::to_string(_game.getScore()));
}
