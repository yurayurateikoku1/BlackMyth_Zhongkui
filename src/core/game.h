#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_properties.h>
#include <glm/glm.hpp>
#include "asset_store.h"
#include <random>
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

    Scene *getCurrentScene() const { return _current_screne; }
    AssetStore *getAssetStore() const { return _asset_store; }
    glm::vec2 getScreenSize() const { return _screen_size; }

    glm::vec2 getMousePosition() const { return _mouse_position; }
    SDL_MouseButtonFlags getMouseButton() const { return _mouse_buttons; }

    // 画网格
    void drawGrid(const glm::vec2 &top_left, const glm::vec2 &right_bottom, float grid_width, SDL_FColor fcolor);
    // 画边框
    void drawBoundary(const glm::vec2 &top_left, const glm::vec2 &right_bottom, float boundary_width, SDL_FColor fcolor);

    void drawPoints(const std::vector<glm::vec2> &points, const glm::vec2 &render_pos, SDL_FColor fcolor);

    // 渲染纹理
    void renderTexture(const Texture &texture, const glm::vec2 &position, const glm::vec2 &size, const glm::vec2 &mask = glm::vec2(1.0f));
    // 渲染画圆
    void renderFillCircle(const glm::vec2 &position, const glm::vec2 &size, float alpha);
    // 渲染bar
    void renderHBar(const glm::vec2 &position, const glm::vec2 &size, float percent, const SDL_FColor &color);

    // 文字函数
    TTF_Text *createTTF_Text(const std::string &text, const std::string &font_path, int font_size = 16);

    // 随机数函数
    float randomFloat(float min, float max)
    {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(_gen);
    }

    int randomInt(int min, int max)
    {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(_gen);
    }

    glm::vec2 randomVec2(const glm::vec2 &min, const glm::vec2 &max)
    {
        return glm::vec2(randomFloat(min.x, max.x), randomFloat(min.y, max.y));
    }

    glm::ivec2 randomIVec2(const glm::ivec2 &min, const glm::ivec2 &max)
    {
        return glm::ivec2(randomInt(min.x, max.x), randomInt(min.y, max.y));
    }

    void playMusic(const std::string &music_path, bool loop = true);
    void playSound(const std::string &sound_path);
    void stopMusic();
    void stopSound();
    void pauseMusic();
    void pauseSound();
    void resumeMusic();
    void resumeSound();

    void setScore(int score);
    void addScore(int score);
    int getScore() const { return _score; }
    void setHighScore(int high_score) { _high_score = high_score; }
    int getHighScore() const { return _high_score; }

    bool isMouseInRect(const glm::vec2 &top_left, const glm::vec2 &right_bottom);

    void quit() { _is_runing = false; }
    void safeChangeScene(Scene *scene) { _next_scene = scene; }
    void changeScene(Scene *scene);

    std::string loadTextFile(const std::string &file_path);

private:
    Game();
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;
    AssetStore *_asset_store = nullptr; // 资源管理类指针
    Scene *_current_screne = nullptr;   // 当前场景类指针
    Scene *_next_scene = nullptr;
    bool _is_runing = true;
    Uint64 _FPS = 60;
    Uint64 _framDelay = 1000000000 / _FPS; // 帧延迟,ns
    double _dt = 0.0f;                     // 帧间隔
    glm::vec2 _screen_size{0, 0};          // 屏幕大小
    glm::vec2 _mouse_position{0, 0};       // 鼠标位置
    SDL_MouseButtonFlags _mouse_buttons;
    MIX_Mixer *_mixer = nullptr;      // 全局混音器
    MIX_Track *_musicTrack = nullptr; // 专门给 BGM 用的 Track
    MIX_Audio *_musicAudio = nullptr; // 当前音乐 Audio

    MIX_Track *_soundTrack = nullptr;
    MIX_Audio *_soundAudio = nullptr;

    SDL_Window *_window = nullptr;
    SDL_Renderer *_renderer = nullptr;
    TTF_TextEngine *_ttf_engine = nullptr;

    int _score = 0;
    int _high_score = 0;
    // 随机数
    std::mt19937 _gen = std::mt19937(std::random_device{}());
};