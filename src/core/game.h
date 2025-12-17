#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_properties.h>
#include <glm/glm.hpp>
#include "asset_store.h"
class Scene;
struct Texture;
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

    // 画网格
    void drawGrid(const glm::vec2 &top_left, const glm::vec2 &right_bottom, float grid_width, SDL_FColor fcolor);
    //
    glm::vec2 getScreenSize() const { return _screen_size; }
    // 画边框
    void drawBoundary(const glm::vec2 &top_left, const glm::vec2 &right_bottom, float boundary_width, SDL_FColor fcolor);

    Scene *getCurrentScene() const { return _current_screne; }
    AssetStore *getAssetStore() const { return _asset_store; }

    // 渲染纹理
    void renderTexture(const Texture &texture, const glm::vec2 &position, const glm::vec2 &size);
    // 画圆
    void renderFillCircle(const glm::vec2 &position, const glm::vec2 &size, float alpha);

private:
    Game();
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;
    AssetStore *_asset_store = nullptr; // 资源管理类指针
    Scene *_current_screne = nullptr;   // 当前场景类指针
    bool _is_runing = true;
    Uint64 _FPS = 60;
    Uint64 _framDelay = 1000000000 / _FPS; // 帧延迟,ns
    double _dt = 0.0f;                     // 帧间隔
    glm::vec2 _screen_size{0, 0};          // 屏幕大小
    MIX_Mixer *_mixer = nullptr;
    SDL_Window *_window = nullptr;
    SDL_Renderer *_renderer = nullptr;
};