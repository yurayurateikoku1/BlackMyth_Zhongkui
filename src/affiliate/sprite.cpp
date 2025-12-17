#include "sprite.h"

Texture::Texture(const std::string &path)
{
    texture = Game::GetInstance().getAssetStore()->getImage(path);
    SDL_GetTextureSize(texture, &src_rect.w, &src_rect.h);
}

Sprite *Sprite::addSpriteChild(ObjectScreen *parrent, const std::string &file_path, float scale)
{
    auto sprite = new Sprite();
    sprite->init();
    sprite->setTexture(file_path);
    sprite->setScale(scale);
    sprite->setParrent(parrent);
    parrent->addChild(sprite);
    return nullptr;
}

void Sprite::render()
{
    if (!_texture.texture || !_parrent || _is_finished)
        return;
    auto pos = _parrent->getRenderPosition() + _offset;
    Game::GetInstance().renderTexture(_texture, pos, _size);
}

void Sprite::setTexture(const Texture &texture)
{
    _texture = texture;
    _size = glm::vec2(texture.src_rect.w, texture.src_rect.h);
}
