#include "sprite_anim.h"

SpriteAnim *SpriteAnim::addSpriteAnimChild(ObjectScreen *parrent, const std::string &file_path, float scale, AnchorType anchor)
{
    auto sprite_anim = new SpriteAnim();
    sprite_anim->init();
    sprite_anim->setTexture(Texture(file_path));
    sprite_anim->setScale(scale);
    sprite_anim->setOffsetByAnchor(anchor);
    sprite_anim->setParrent(parrent);
    parrent->addChild(sprite_anim);
    return sprite_anim;
}

void SpriteAnim::update(float dt)
{
    if (_is_finished)
        return;
    _frame_time += dt;
    if (_frame_time >= 1.0f / _fps)
    {
        _current_frame++;
        if (_current_frame >= _total_frames)
        {
            _current_frame = 0;
            if (!_is_loop)
            {
                _is_finished = true;
            }
        }
        _frame_time = 0.0f;
    }
    _texture.src_rect.x = _current_frame * _texture.src_rect.w;
}

void SpriteAnim::setTexture(const Texture &texture)
{
    _texture = texture;
    _total_frames = texture.src_rect.w / texture.src_rect.h;
    _texture.src_rect.w = texture.src_rect.h;
    _size = glm::vec2(_texture.src_rect.w, _texture.src_rect.h);
}
