#include "bg_star.h"
#include "../core/scene.h"
BgStar *BgStar::addBgStarChild(Object *parent, int num, float scale_far, float scale_mid, float scale_near)
{
    BgStar *bg_star = new BgStar();
    bg_star->init();
    bg_star->_num = num;
    bg_star->setScaleFar(scale_far);
    bg_star->setScaleMid(scale_mid);
    bg_star->setScaleNear(scale_near);
    bg_star->_star_far.reserve(num);
    bg_star->_star_mid.reserve(num);
    bg_star->_star_near.reserve(num);
    auto extra = Game::GetInstance().getCurrentScene()->getWorldSize() - Game::GetInstance().getScreenSize();
    for (auto i = 0; i < num; i++)
    {
        /* code */
        bg_star->_star_far.push_back(Game::GetInstance().randomVec2(glm::vec2(0, 0), Game::GetInstance().getScreenSize() + extra * scale_far));
        bg_star->_star_mid.push_back(Game::GetInstance().randomVec2(glm::vec2(0, 0), Game::GetInstance().getScreenSize() + extra * scale_mid));
        bg_star->_star_near.push_back(Game::GetInstance().randomVec2(glm::vec2(0, 0), Game::GetInstance().getScreenSize() + extra * scale_near));
    }
    if (parent)
    {
        parent->addChild(bg_star);
    }
    return bg_star;
}

void BgStar::update(float dt)
{
    _timer += dt;
    _color_far = {0.5f + 0.5f * sinf(_timer * 0.9f), 0.5f + 0.5f * sinf(_timer * 0.8f), 0.5f + 0.5f * sinf(_timer * 0.7f), 1};
    _color_mid = {0.5f + 0.5f * sinf(_timer * 0.8f), 0.5f + 0.5f * sinf(_timer * 0.7f), 0.5f + 0.5f * sinf(_timer * 0.6f), 1};
    _color_near = {0.5f + 0.5f * sinf(_timer * 0.7f), 0.5f + 0.5f * sinf(_timer * 0.6f), 0.5f + 0.5f * sinf(_timer * 0.5f), 1};
}

void BgStar::render()
{
    _game.drawPoints(_star_far, -_game.getCurrentScene()->getCameraPosition() * _scale_far, _color_far);
    _game.drawPoints(_star_mid, -_game.getCurrentScene()->getCameraPosition() * _scale_mid, _color_mid);
    _game.drawPoints(_star_near, -_game.getCurrentScene()->getCameraPosition() * _scale_near, _color_near);
}
