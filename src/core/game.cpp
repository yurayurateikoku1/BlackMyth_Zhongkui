#include "game.h"
#include "../scene_main.h"
#include "actor.h"
#include "../affiliate/sprite.h"
#include <algorithm>
#include "../scene_title.h"
#include "../scene_logo.h"
#include <fstream>
void Game::run()
{
    while (_is_runing)
    {
        auto start = SDL_GetTicksNS();
        if (_next_scene)
        {
            changeScene(_next_scene);
            _next_scene = nullptr;
        }

        handleEnvents();
        updata(_dt);
        render();
        auto end = SDL_GetTicksNS();
        auto elapsed = end - start;
        if (elapsed < _framDelay)
        {
            SDL_DelayNS((_framDelay - elapsed));
            _dt = _framDelay / 1000000000.0f;
        }
        else
        {
            _dt = elapsed / 1.0e9;
        }
    }
}
void Game::init(const std::string &title, int width, int height)
{
    _screen_size = glm::vec2(width, height);
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL Init Failed:%s", SDL_GetError());
        return;
    }
    if (!MIX_Init())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_mixer Init Failed: %s", SDL_GetError());
        return;
    }

    SDL_AudioSpec spec{};
    spec.freq = 48000;
    spec.format = SDL_AUDIO_F32;
    spec.channels = 2;

    _mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec);
    if (_mixer == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_mixer create device failed: %s", SDL_GetError());
    }

    if (!TTF_Init())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_ttf Init failed: %s", SDL_GetError());
    }
    SDL_CreateWindowAndRenderer(title.c_str(), width, height, SDL_WINDOW_RESIZABLE, &_window, &_renderer);
    if (!_window || !_renderer)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window or Renderer create failed: %s", SDL_GetError());
        SDL_SetRenderLogicalPresentation(_renderer, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    }

    _ttf_engine = TTF_CreateRendererTextEngine(_renderer);
    // 创建资源管理器
    _asset_store = new AssetStore(_renderer, _mixer);
    // 创建场景 - 从Logo场景开始
    _current_screne = new SceneLogo();
    _current_screne->init();
}
void Game::handleEnvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            _is_runing = false;
            break;
        default:
            _current_screne->handleEvents(event);
            break;
        }
    }
}
void Game::updata(float dt)
{
    updateMouse();
    _current_screne->update(dt);
}
void Game::render()
{

    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
    _current_screne->render();
    SDL_RenderPresent(_renderer);
}
void Game::clean()
{
    if (_current_screne)
    {
        _current_screne->clean();
        delete _current_screne;
    }

    if (_asset_store)
    {
        _asset_store->clean();
        delete _asset_store;
    }
    if (_ttf_engine)
    {
        TTF_DestroyRendererTextEngine(_ttf_engine);
    }

    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    MIX_StopTrack(_musicTrack, 0);
    MIX_StopTrack(_soundTrack, 0);
    MIX_DestroyTrack(_musicTrack);
    MIX_DestroyTrack(_soundTrack);
    MIX_DestroyAudio(_musicAudio);
    MIX_DestroyAudio(_soundAudio);
    MIX_DestroyMixer(_mixer);
    MIX_Quit();
    TTF_Quit();
    SDL_Quit();
}
void Game::drawGrid(const glm::vec2 &top_left, const glm::vec2 &bottom_right, float grid_width, SDL_FColor fcolor)
{
    SDL_SetRenderDrawColorFloat(_renderer, fcolor.r, fcolor.g, fcolor.b, fcolor.a);
    for (float x = top_left.x; x <= bottom_right.x; x += grid_width)
    {
        SDL_RenderLine(_renderer, x, top_left.y, x, bottom_right.y);
    }
    for (float y = top_left.y; y <= bottom_right.y; y += grid_width)
    {
        SDL_RenderLine(_renderer, top_left.x, y, bottom_right.x, y);
    }
    SDL_SetRenderDrawColorFloat(_renderer, 0, 0, 0, 1);
}
void Game::drawBoundary(const glm::vec2 &top_left, const glm::vec2 &right_bottom, float boundary_width, SDL_FColor fcolor)
{
    SDL_SetRenderDrawColorFloat(_renderer, fcolor.r, fcolor.g, fcolor.b, fcolor.a);
    for (float i = 0; i < boundary_width; i++)
    {
        SDL_FRect rect = {
            top_left.x - i,
            top_left.y - i,
            right_bottom.x - top_left.x + 2 * i,
            right_bottom.y - top_left.y + 2 * i,
        };
        SDL_RenderRect(_renderer, &rect);
    }
    SDL_SetRenderDrawColorFloat(_renderer, 0, 0, 0, 1);
}

void Game::drawPoints(const std::vector<glm::vec2> &points, const glm::vec2 &render_pos, SDL_FColor fcolor)
{
    SDL_SetRenderDrawColorFloat(_renderer, fcolor.r, fcolor.g, fcolor.b, fcolor.a);
    for (const auto &point : points)
    {
        auto x = point.x + render_pos.x;
        auto y = point.y + render_pos.y;
        SDL_RenderPoint(_renderer, x, y);
    }
    SDL_SetRenderDrawColorFloat(_renderer, 0, 0, 0, 1);
}

void Game::renderTexture(const Texture &texture, const glm::vec2 &position, const glm::vec2 &size, const glm::vec2 &mask)
{
    SDL_FRect src_rect = {
        texture.src_rect.x,
        texture.src_rect.y + texture.src_rect.h * (1 - mask.y),
        texture.src_rect.w * mask.x,
        texture.src_rect.h * mask.y,
    };
    SDL_FRect dst_rect = {
        position.x,
        position.y + size.y * (1 - mask.y),
        size.x * mask.x,
        size.y * mask.y,
    };
    SDL_RenderTextureRotated(_renderer, texture.texture, &src_rect, &dst_rect, texture.angle, nullptr, texture.is_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Game::renderFillCircle(const glm::vec2 &position, const glm::vec2 &size, float alpha)
{
    auto texture = _asset_store->getImage("assets/UI/circle.png");
    SDL_FRect dst_rect = {
        position.x,
        position.y,
        size.x,
        size.y,
    };
    SDL_SetTextureAlphaModFloat(texture, alpha);
    SDL_RenderTexture(_renderer, texture, NULL, &dst_rect);
}

void Game::renderHBar(const glm::vec2 &position, const glm::vec2 &size, float percent, const SDL_FColor &color)
{
    float clamped_percent = std::clamp(percent, 0.0f, 1.0f);

    // draw border
    SDL_SetRenderDrawColorFloat(_renderer, 0, 0, 0, 1);
    SDL_FRect boundary_rect = {
        position.x,
        position.y,
        size.x,
        size.y};
    SDL_RenderRect(_renderer, &boundary_rect);

    // fill area
    SDL_FRect fill_rect = {
        position.x,
        position.y,
        size.x * clamped_percent,
        size.y};
    SDL_SetRenderDrawColorFloat(_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(_renderer, &fill_rect);

    SDL_SetRenderDrawColorFloat(_renderer, 0, 0, 0, 1);
}

TTF_Text *Game::createTTF_Text(const std::string &text, const std::string &font_path, int font_size)
{
    auto font = _asset_store->getFont(font_path, font_size);
    return TTF_CreateText(_ttf_engine, font, text.c_str(), font_size);
}

void Game::setScore(int score)
{
    _score = score;
    if (score > _high_score)
    {
        _high_score = score;
    }
}

void Game::addScore(int score)
{
    setScore(_score + score);
}

bool Game::isMouseInRect(const glm::vec2 &top_left, const glm::vec2 &right_bottom)
{
    if (_mouse_position.x >= top_left.x && _mouse_position.x <= right_bottom.x && _mouse_position.y >= top_left.y && _mouse_position.y <= right_bottom.y)
    {
        return true;
    }

    return false;
}

Game::Game()
{
}

void Game::updateMouse()
{
    _mouse_buttons = SDL_GetMouseState(&_mouse_position.x, &_mouse_position.y);
    int w, h;
    SDL_GetWindowSize(_window, &w, &h);
    SDL_SetWindowAspectRatio(_window, _screen_size.x / _screen_size.y, _screen_size.x / _screen_size.y);
    _mouse_position *= _screen_size / glm::vec2(w, h);
}

void Game::playMusic(const std::string &music_path, bool loop)
{

    if (!_musicTrack)
    {
        _musicTrack = MIX_CreateTrack(_mixer);
        if (!_musicTrack)
        {
            SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Failed to create music track: %s",
                         SDL_GetError());
            return;
        }
    }

    if (_musicAudio)
    {
        MIX_DestroyAudio(_musicAudio);
        _musicAudio = nullptr;
    }

    _musicAudio = MIX_LoadAudio(_mixer, music_path.c_str(), true);
    if (!_musicAudio)
    {
        SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Failed to load music %s: %s",
                     music_path.c_str(), SDL_GetError());
        return;
    }

    if (!MIX_SetTrackAudio(_musicTrack, _musicAudio))
    {
        SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "MIX_SetTrackAudio failed: %s",
                     SDL_GetError());
        return;
    }
    MIX_SetTrackGain(_musicTrack, 0.05f);
    SDL_PropertiesID props = SDL_CreateProperties();

    if (loop)
    {
        SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, -1);
    }
    else
    {
        SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, 0);
    }
    if (!MIX_PlayTrack(_musicTrack, props))
    {
        SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "MIX_PlayTrack failed: %s",
                     SDL_GetError());
    }
}

void Game::playSound(const std::string &sound_path)
{
    if (!_mixer)
        return;

    if (!_soundTrack)
    {
        _soundTrack = MIX_CreateTrack(_mixer);
        if (!_soundTrack)
        {
            SDL_LogError(SDL_LOG_CATEGORY_AUDIO,
                         "Create sound track failed: %s",
                         SDL_GetError());
            return;
        }
    }

    if (_soundAudio)
    {
        MIX_DestroyAudio(_soundAudio);
        _soundAudio = nullptr;
    }

    _soundAudio = MIX_LoadAudio(_mixer, sound_path.c_str(), true);
    if (!_soundAudio)
    {
        SDL_LogError(SDL_LOG_CATEGORY_AUDIO,
                     "Load sound failed: %s",
                     SDL_GetError());
        return;
    }

    MIX_SetTrackAudio(_soundTrack, _soundAudio);

    MIX_PlayTrack(_soundTrack, 0);
}

void Game::stopMusic()
{
    if (_musicTrack)
    {
        MIX_StopTrack(_musicTrack, 0);
    }
}

void Game::stopSound()
{
    if (_soundTrack)
    {
        MIX_StopTrack(_soundTrack, 0);
    }
}

void Game::pauseMusic()
{
    if (_musicTrack)
    {
        MIX_PauseTrack(_musicTrack);
    }
}

void Game::pauseSound()
{
    if (_soundTrack)
    {
        MIX_PauseTrack(_soundTrack);
    }
}

void Game::resumeMusic()
{
    if (_musicTrack)
    {
        MIX_ResumeTrack(_musicTrack);
    }
}

void Game::resumeSound()
{
    if (_soundTrack)
    {
        MIX_ResumeTrack(_soundTrack);
    }
}

void Game::changeScene(Scene *scene)
{
    if (_current_screne)
    {
        _current_screne->clean();
        delete _current_screne;
    }
    _current_screne = scene;
    if (_current_screne)
    {
        _current_screne->init();
    }
}

std::string Game::loadTextFile(const std::string &file_path)
{
    std::ifstream file(file_path);
    std::string line;
    std::string text;
    while (std::getline(file, line))
    {
        text += line + '\n';
    }

    return text;
}
