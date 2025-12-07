#include "game.h"
#include "../screne_main.h"
#include "actor.h"
void Game::run()
{
    while (_is_runing)
    {
        auto start = SDL_GetTicksNS();
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
    // 创建资源管理器
    _asset_store = new AssetStore(_renderer, _mixer);
    // 创建场景
    _current_screne = new ScreneMain();
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

    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
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
Game::Game()
{
}
