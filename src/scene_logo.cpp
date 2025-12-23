#include "scene_logo.h"
#include "scene_title.h"
#include "core/object_screen.h"
#include "affiliate/sprite.h"

void SceneLogo::init()
{
    Scene::init();
    _timer = 0.0f;

    auto screen_size = _game.getScreenSize();

    // 创建一个ObjectScreen容器来持有Logo sprite
    _logo_container = new ObjectScreen();
    _logo_container->init();
    _logo_container->setRenderPosition(screen_size / 2.0f);
    addChild(_logo_container);

    // 在容器中添加sprite
    _logo_sprite = Sprite::addSpriteChild(_logo_container, "assets/UI/pixel_empire_a.png", 2.0f, AnchorType::CENTER);

    auto logo_texture = _game.getAssetStore()->getImage("assets/UI/pixel_empire_a.png");
    float logo_width, logo_height;
    SDL_GetTextureSize(logo_texture, &logo_width, &logo_height);

    float scale = std::min(screen_size.x / logo_width, screen_size.y / logo_height) * 0.5f;
    _logo_sprite->setSize(glm::vec2(logo_width * scale, logo_height * scale));
}

void SceneLogo::update(float dt)
{
    Scene::update(dt);
    _timer += dt;

    if (_timer >= _duration)
    {
        auto scene = new SceneTitle();
        _game.safeChangeScene(scene);
    }
}

void SceneLogo::render()
{
    Scene::render();
}

void SceneLogo::clean()
{
    Scene::clean();
}
