#include "asset_store.h"

AssetStore::AssetStore(SDL_Renderer *renderer, MIX_Mixer *mixer)
    : _renderer(renderer), _mixer(mixer)
{
}

void AssetStore::clean()
{
    for (auto &texture : _textures)
    {
        SDL_DestroyTexture(texture.second);
    }
    _textures.clear();
    for (auto &sound : _sounds)
    {
        MIX_DestroyAudio(sound.second);
    }
    _sounds.clear();
    for (auto &music : _musics)
    {
        MIX_DestroyAudio(music.second);
    }
    _musics.clear();
    for (auto &font : _fonts)
    {
        TTF_CloseFont(font.second);
    }
    _fonts.clear();
}

void AssetStore::loadImage(const std::string &file_path)
{
    SDL_Texture *texture = IMG_LoadTexture(_renderer, file_path.c_str());
    if (texture == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed load image: %s", file_path.c_str());
        return;
    }
    _textures.emplace(file_path, texture);
}

void AssetStore::loadSound(const std::string &file_path)
{
    MIX_Audio *sound = MIX_LoadAudio(_mixer, file_path.c_str(), true);
    if (sound == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed load sound: %s", file_path.c_str());
        return;
    }
    _sounds.emplace(file_path, sound);
}

void AssetStore::loadMusic(const std::string &file_path)
{
    MIX_Audio *music = MIX_LoadAudio(_mixer, file_path.c_str(), true);
    if (music == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed load music: %s", file_path.c_str());
        return;
    }
    _musics.emplace(file_path, music);
}

void AssetStore::loadFont(const std::string &file_path, float font_size)
{
    TTF_Font *font = TTF_OpenFont(file_path.c_str(), font_size);
    if (font == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed load font: %s", file_path.c_str());
        return;
    }
    _fonts.emplace(file_path + std::to_string(font_size), font);
}

SDL_Texture *AssetStore::getImage(const std::string &file_path)
{
    auto iter = _textures.find(file_path);
    if (iter == _textures.end())
    {
        loadImage(file_path);
        iter = _textures.find(file_path);
    }
    if (iter == _textures.end())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to get image: %s", file_path.c_str());
        return nullptr;
    }
    return iter->second;
}

MIX_Audio *AssetStore::getSound(const std::string &file_path)
{
    auto iter = _sounds.find(file_path);
    if (iter == _sounds.end())
    {
        loadSound(file_path);
        iter = _sounds.find(file_path);
    }
    if (iter == _sounds.end())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to get sound: %s", file_path.c_str());
        return nullptr;
    }
    return iter->second;
}

MIX_Audio *AssetStore::getMusic(const std::string &file_path)
{
    auto iter = _musics.find(file_path);
    if (iter == _musics.end())
    {
        loadMusic(file_path);
        iter = _musics.find(file_path);
    }
    if (iter == _musics.end())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to get music: %s", file_path.c_str());
        return nullptr;
    }
    return iter->second;
}

TTF_Font *AssetStore::getFont(const std::string &file_path, float font_size)
{
    auto iter = _fonts.find(file_path + std::to_string(font_size));
    if (iter == _fonts.end())
    {
        loadFont(file_path, font_size);
        iter = _fonts.find(file_path + std::to_string(font_size));
    }
    if (iter == _fonts.end())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to get font: %s", (file_path + std::to_string(font_size)).c_str());
        return nullptr;
    }
    return iter->second;
}
