#pragma once
#include "../core/object_affiliate.h"

struct Texture
{
    /* data */
    SDL_Texture *texture = nullptr;
    SDL_FRect src_rect;
    float angle = 0.0f;
    bool is_flip = false;
    Texture() = default;
    Texture(const std::string &path);
};

class Sprite : public ObjectAffiliate
{
protected:
    /* data */
    Texture _texture;
    bool _is_finished = false;
    glm::vec2 _percentage{1.0f}; // 决定图片原始区域的比例

public:
    static Sprite *addSpriteChild(ObjectScreen *parrent, const std::string &file_path, float scale = 1.0f, AnchorType anchor = AnchorType::CENTER);
    virtual void render() override;
    Sprite() = default;
    Sprite(const std::string &file_path);

    Texture getTexture() const { return _texture; }
    virtual void setTexture(const Texture &texture);

    void setAngle(float angle) { _texture.angle = angle; }
    void setFlip(bool flip) { _texture.is_flip = flip; }
    bool getFlip() const { return _texture.is_flip; }
    float getAngle() const { return _texture.angle; }
    bool getIsFinished() const { return _is_finished; }
    void setIsFinished(bool finished) { _is_finished = finished; }
    void setPercentage(const glm::vec2 &percentage) { _percentage = percentage; }
    glm::vec2 getPercentage() const { return _percentage; }
};
