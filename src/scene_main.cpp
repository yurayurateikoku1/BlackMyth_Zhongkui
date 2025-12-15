#include "scene_main.h"
#include "player.h"
void SceneMain::init()
{
    _word_size = _game.getScreenSize() * 3.0f;
    _camera_position = _word_size / 2.0f - _game.getScreenSize() / 2.0f;
    _player = new Player();
    _player->init();
    _player->setPosition(_word_size / 2.0f);
    addChild(_player);
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
    Scene::render();
    renderBackground();
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