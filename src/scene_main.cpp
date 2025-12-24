#include "scene_main.h"
#include "player.h"
#include "enemy.h"
#include "world/effect.h"
#include "spwaner.h"
#include "screen/ui_mouse.h"
#include "world/spell.h"
#include "screen/hud_states.h"
#include "screen/hud_text.h"
#include "screen/hud_button.h"
#include "scene_title.h"
#include "raw/timer.h"
#include "raw/bg_star.h"
#include <fstream>
void SceneMain::init()
{
    Scene::init();
    SDL_HideCursor();
    _game.playMusic("assets/bgm/OhMyGhost.ogg");
    _word_size = _game.getScreenSize() * 3.0f;
    _camera_position = _word_size / 2.0f - _game.getScreenSize() / 2.0f;
    _player = new Player();
    _player->init();
    _player->setPosition(_word_size / 2.0f);
    addChild(_player);

    BgStar::addBgStarChild(this, 2000, 0.1f, 0.15f, 0.2f);

    _end_timer = Timer::addTimerChild(this, 3.0f);

    _spwaner = new Spwaner();
    _spwaner->init();
    _spwaner->setTarget(_player);
    addChild(_spwaner);

    _button_pause = HUDButton::addHUDButtonChild(this, _game.getScreenSize() - glm::vec2(230.0f, 30.0f), "assets/UI/A_Pause1.png", "assets/UI/A_Pause2.png", "assets/UI/A_Pause3.png");
    _button_restart = HUDButton::addHUDButtonChild(this, _game.getScreenSize() - glm::vec2(140.0f, 30.0f), "assets/UI/A_Restart1.png", "assets/UI/A_Restart2.png", "assets/UI/A_Restart3.png");
    _button_back = HUDButton::addHUDButtonChild(this, _game.getScreenSize() - glm::vec2(50.0f, 30.0f), "assets/UI/A_Back1.png", "assets/UI/A_Back2.png", "assets/UI/A_Back3.png");

    _hud_states = HUDStates::addHUDStatesChild(this, _player, glm::vec2(30.0f, 30.0f));

    _hud_text_score = HUDText::addHUDTextChild(this, "Score:0", glm::vec2(_game.getScreenSize().x - 120.0f, 30.0f), glm::vec2(200, 50));

    _ui_mouse = UIMouse::addUIMouseChild(this, "assets/UI/29.png", "assets/UI/30.png", 1.0f, AnchorType::CENTER);
}

void SceneMain::update(float dt)
{
    Scene::update(dt);
    updateScore();
    checkButtonPause();
    checkButtonRestart();
    checkButtonBack();
    if (_player && !_player->getActive())
    {
        saveData("assets/score.dat");
        _end_timer->start();
    }
    checkEndTimer();
}

bool SceneMain::handleEvents(SDL_Event &event)
{
    if (Scene::handleEvents(event))
        return true;
    return false;
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

void SceneMain::saveData(const std::string &file_path)
{
    auto score = _game.getHighScore();
    std::ofstream file(file_path, std::ios::binary);
    if (file.is_open())
    {
        file.write(reinterpret_cast<const char *>(&score), sizeof(score));
        file.close();
    }
}

void SceneMain::checkButtonPause()
{
    if (!_button_pause->getIsTrigger())
    {
        return;
    }
    if (_is_pause)
    {
        resume();
    }
    else
    {
        pause();
    }
}

void SceneMain::checkButtonRestart()
{
    if (!_button_restart->getIsTrigger())
    {
        return;
    }
    saveData("assets/score.dat");
    _game.setScore(0);
    auto scene = new SceneMain();
    _game.safeChangeScene(scene);
}

void SceneMain::checkButtonBack()
{
    if (!_button_back->getIsTrigger())
    {
        return;
    }
    saveData("assets/score.dat");
    _game.setScore(0);
    auto scene = new SceneTitle();
    _game.safeChangeScene(scene);
}

void SceneMain::checkEndTimer()
{
    if (!_end_timer->timeOut())
    {
        return;
    }
    pause();
    _button_restart->setRenderPosition(_game.getScreenSize() / 2.0f - glm::vec2(200.0f, 0));
    _button_restart->setScale(4.0f);
    _button_back->setRenderPosition(_game.getScreenSize() / 2.0f + glm::vec2(200.0f, 0));
    _button_back->setScale(4.0f);
    _button_pause->setActive(false);
    _end_timer->stop();
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
