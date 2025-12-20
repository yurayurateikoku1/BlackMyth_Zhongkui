#pragma once
#include "../core/object_affiliate.h"

class AffiliateBar : public ObjectAffiliate
{
protected:
    float _percentage = 1.0f;
    SDL_FColor _color_high{0, 1, 0, 1};    // green
    SDL_FColor _color_mid{1, 0.65f, 0, 1}; // yellow
    SDL_FColor _color_low{1, 0, 0, 1};     // read
public:
    static AffiliateBar *addAffiliateBarChild(ObjectScreen *parent, glm::vec2 size = {0, 0}, AnchorType anchor = AnchorType::BOTTOM_CENTER);
    virtual void render() override;
    float getPercentage() const { return _percentage; }
    void setPercentage(float percentage) { _percentage = percentage; }
    SDL_FColor getColoHigh() const { return _color_high; }
    SDL_FColor getColoMid() const { return _color_mid; }
    SDL_FColor getColoLow() const { return _color_low; }
    void setColoHigh(const SDL_FColor &color) { _color_high = color; }
    void setColoMid(const SDL_FColor &color) { _color_mid = color; }
    void setColoLow(const SDL_FColor &color) { _color_low = color; }
};
