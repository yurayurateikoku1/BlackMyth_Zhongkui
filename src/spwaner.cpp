#include "spwaner.h"
#include "enemy.h"
#include "world/effect.h"
#include "core/scene.h"
void Spwaner::update(float dt)
{
    if (!_target || !_target->getActive())
        return;
    _timer += dt;
    if (_timer >= _interval)
    {
        _timer = 0.0f;
        for (int i = 0; i < _num; ++i)
        {
            auto position = _game.randomVec2(_game.getCurrentScene()->getCameraPosition(), _game.getCurrentScene()->getCameraPosition() + _game.getScreenSize());
            Enemy *enemy = Enemy::addEnemyChild(nullptr, position, _target);
            Effect::addEffectChild(_game.getCurrentScene(), "assets/effect/184_3.png", position, 1.0f, enemy);
        }
    }
}
