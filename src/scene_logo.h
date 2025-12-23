#pragma once
#include "core/scene.h"

class Sprite;
class ObjectScreen;

class SceneLogo : public Scene
{
private:
    float _timer = 0.0f;
    float _duration = 1.0f;
    ObjectScreen *_logo_container = nullptr;
    Sprite *_logo_sprite = nullptr;

public:
    virtual void init() override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;
};
