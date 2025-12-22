#pragma once
#include "../core/object_screen.h"
class Sprite;
class HUDSkill : public ObjectScreen
{
public:
    static HUDSkill *addHUDSkillChild(Object *parent, const std::string &file_path, const glm::vec2 &position, float scale = 1.0f, AnchorType = AnchorType::CENTER);
    virtual void render() override;
    Sprite *getIcon() const { return _icon; }
    void setIcon(Sprite *icon) { _icon = icon; }
    float getPercentage() const { return _percentage; }
    void setPercentage(float percentage);

protected:
    Sprite *_icon = nullptr;
    float _percentage = 1.0f;

private:
};
