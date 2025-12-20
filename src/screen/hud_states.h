#pragma once
#include "../core/object_screen.h"
class Sprite;
class Actor;
class HUDStates : public ObjectScreen
{
protected:
    Actor *_target = nullptr;
    Sprite *_health_bar = nullptr;
    Sprite *_health_bar_bg = nullptr;
    Sprite *_health_icon = nullptr;
    Sprite *_mana_bar = nullptr;
    Sprite *_mana_bar_bg = nullptr;
    Sprite *_mana_icon = nullptr;

    float _health_percentage = 1.0f;
    float _mana_percentage = 1.0f;

public:
    virtual void init() override;
    virtual void update(float dt) override;

    static HUDStates *addHUDStatesChild(Object *parent, Actor *target, const glm::vec2 &render_position);

    Sprite *getHealthBar() const
    {
        return _health_bar;
    }
    void setTarget(Actor *target) { _target = target; }
    Actor *getTarget() const { return _target; }

    Sprite *getHealthBarBg() const { return _health_bar_bg; }
    Sprite *getHealthIcon() const { return _health_icon; }
    Sprite *getManaBar() const { return _mana_bar; }
    Sprite *getManaBarBg() const { return _mana_bar_bg; }
    Sprite *getManaIcon() const { return _mana_icon; }

    float getHealthPercentage() const { return _health_percentage; }
    float getManaPercentage() const { return _mana_percentage; }
    void setHealthPercentage(float percentage) { _health_percentage = percentage; }
    void setManaPercentage(float percentage) { _mana_percentage = percentage; }

private:
    void updateHealthBar();
    void updateManaBar();
};
