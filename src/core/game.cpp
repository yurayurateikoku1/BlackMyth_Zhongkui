#include "game.h"
#include "../screne_main.h"
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

    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    MIX_DestroyMixer(_mixer);
    MIX_Quit();
    TTF_Quit();
    SDL_Quit();
}
Game::Game()
{
}
