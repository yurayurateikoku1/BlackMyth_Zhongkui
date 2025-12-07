#pragma once
#include <unordered_map>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_properties.h>
#include <iostream>
#include <string>
class AssetStore
{
private:
    /* data */
    SDL_Renderer *_renderer = nullptr;
    MIX_Mixer *_mixer = nullptr;
    std::unordered_map<std::string, SDL_Texture *> _textures;
    std::unordered_map<std::string, MIX_Audio *> _sounds;
    std::unordered_map<std::string, MIX_Audio *> _musics;
    std::unordered_map<std::string, TTF_Font *> _fonts;

public:
    AssetStore(SDL_Renderer *renderer, MIX_Mixer *mixer);
    ~AssetStore() = default;

    void clean();
    void loadImage(const std::string &file_path);
    void loadSound(const std::string &file_path);
    void loadMusic(const std::string &file_path);
    void loadFont(const std::string &file_path, float font_size);

    SDL_Texture *getImage(const std::string &file_path);
    MIX_Audio *getSound(const std::string &file_path);
    MIX_Audio *getMusic(const std::string &file_path);
    TTF_Font *getFont(const std::string &file_path, float font_size);
};
