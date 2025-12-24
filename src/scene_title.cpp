#include "scene_title.h"
#include "screen/hud_text.h"
#include "screen/hud_button.h"
#include <cmath>
#include "scene_main.h"
#include <fstream>
void SceneTitle::renderBackground()
{
    _game.drawBoundary(glm::vec2(30.0f), _game.getScreenSize() - glm::vec2(30.0f), 10.0f, _boundary_color);
}

void SceneTitle::updateColor()
{
    _boundary_color.r = 0.5f + 0.5f * sinf(_color_timer * 0.9f);
    _boundary_color.g = 0.5f + 0.5f * sinf(_color_timer * 0.8f);
    _boundary_color.b = 0.5f + 0.5f * sinf(_color_timer * 0.7f);
}

void SceneTitle::checkButtonQuit()
{
    if (_button_exit->getIsTrigger())
    {
        _game.quit();
    }
}

void SceneTitle::checkButtonStart()
{
    if (_button_start->getIsTrigger())
    {
        auto scene = new SceneMain();
        _game.safeChangeScene(scene);
    }
}

void SceneTitle::checkButtonCredists()
{
    if (_button_credists->getIsTrigger())
    {
        _credists_text->setActive(true);
    }
}

void SceneTitle::init()
{
    Scene::init();
    loadData("assets/score.dat");
    SDL_ShowCursor();
    _game.playMusic("assets/bgm/Spooky music.mp3");
    auto size = glm::vec2(_game.getScreenSize().x / 2.0f, _game.getScreenSize().y / 3.0f);
    HUDText::addHUDTextChild(this, "Black Myth: ZhongKui", _game.getScreenSize() / 2.0f - glm::vec2(0, 100), size, "assets/font/VonwaonBitmap-16px.ttf", 64);
    auto score_text = "Max Score: " + std::to_string(_game.getHighScore());
    HUDText::addHUDTextChild(this, score_text, _game.getScreenSize() / 2.0f + glm::vec2(0, 100), glm::vec2(200, 50), "assets/font/VonwaonBitmap-16px.ttf", 32);

    _button_start = HUDButton::addHUDButtonChild(this, _game.getScreenSize() / 2.0f + glm::vec2(-200, 200), "assets/UI/A_Start1.png", "assets/UI/A_Start2.png", "assets/UI/A_Start3.png", 2.0f, AnchorType::CENTER);
    _button_credists = HUDButton::addHUDButtonChild(this, _game.getScreenSize() / 2.0f + glm::vec2(0, 200), "assets/UI/A_Credits1.png", "assets/UI/A_Credits2.png", "assets/UI/A_Credits3.png", 2.0f, AnchorType::CENTER);
    _button_exit = HUDButton::addHUDButtonChild(this, _game.getScreenSize() / 2.0f + glm::vec2(200, 200), "assets/UI/A_Quit1.png", "assets/UI/A_Quit2.png", "assets/UI/A_Quit3.png", 2.0f, AnchorType::CENTER);

    auto text = _game.loadTextFile("assets/credits.txt");
    _credists_text = HUDText::addHUDTextChild(this, text, _game.getScreenSize() / 2.0f, glm::vec2(500, 500), "assets/font/VonwaonBitmap-16px.ttf", 16);
    _credists_text->setBgSizeByText(50.0f);
    _credists_text->setActive(false);
}

bool SceneTitle::handleEvents(SDL_Event &event)
{
    if (_credists_text->getActive())
    {
        if (event.type == SDL_EVENT_MOUSE_BUTTON_UP)
        {
            _credists_text->setActive(false);
            return true;
        }
    }
    if (Scene::handleEvents(event))
        return true;
    return false;
}

void SceneTitle::update(float dt)
{
    _color_timer += dt;
    updateColor();
    if (_credists_text->getActive())
    {
        return;
    }
    Scene::update(dt);
    checkButtonQuit();
    checkButtonStart();
    checkButtonCredists();
}

void SceneTitle::render()
{
    renderBackground();
    Scene::render();
}

void SceneTitle::clean()
{
    Scene::clean();
}

void SceneTitle::loadData(const std::string &file_path)
{
    int score = 0;
    std::ifstream file(file_path, std::ios::binary);
    if (file.is_open())
    {
        file.read(reinterpret_cast<char *>(&score), sizeof(score));
        file.close();
    }
    _game.setHighScore(score);
}
