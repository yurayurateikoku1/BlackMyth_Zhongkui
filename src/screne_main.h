#pragma once
#include "core/screne.h"

class ScreneMain : public Screne
{
private:
    /* data */
public:
    ScreneMain(/* args */) = default;
    ~ScreneMain() = default;
    virtual void init() override;
    virtual void handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;
};
