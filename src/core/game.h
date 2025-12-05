#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_properties.h>
#include <glm/glm.hpp>

class Screne;
class Game
{
public:
    static Game &GetInstance()
    {
        static Game instance;
        return instance;
    }
    void run();
    void init(const std::string &title, int width, int height);
    void handleEnvents();
    void updata(float dt);
    void render();
    void clean();

private:
    Game();
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;
    Screne *_current_screne = nullptr;
    bool _is_runing = true;
    Uint64 _FPS = 60;
    Uint64 _framDelay = 1000000000 / _FPS; // 帧延迟,ns
    double _dt = 0.0f;                     // 帧间隔
    glm::vec2 _screen_size = glm::vec2{0}; // 屏幕大小
    MIX_Mixer *_mixer = nullptr;
    SDL_Window *_window = nullptr;
    SDL_Renderer *_renderer = nullptr;
};