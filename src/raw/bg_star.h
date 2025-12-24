#pragma once
#include "../core/object.h"

class BgStar : public Object
{
private:
    /* data */
protected:
    std::vector<glm::vec2> _star_far;
    std::vector<glm::vec2> _star_mid;
    std::vector<glm::vec2> _star_near;
    float _scale_far = 0.2f;
    float _scale_mid = 0.4f;
    float _scale_near = 0.6f;
    SDL_FColor _color_far{0, 0, 0, 1};
    SDL_FColor _color_mid{0, 0, 0, 1};
    SDL_FColor _color_near{0, 0, 0, 1};

    float _timer = 0.0f;
    int _num = 2000;

public:
    static BgStar *addBgStarChild(Object *parent, int num, float scale_far, float scale_mid, float scale_nearr);

    virtual void update(float dt) override;
    virtual void render() override;
    float getScaleFar() const { return _scale_far; };
    float getScaleMid() const { return _scale_mid; };
    float getScaleNear() const { return _scale_near; };
    void setScaleFar(float scale_far) { _scale_far = scale_far; };
    void setScaleMid(float scale_mid) { _scale_mid = scale_mid; };
    void setScaleNear(float scale_near) { _scale_near = scale_near; };
};
