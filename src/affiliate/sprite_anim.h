#pragma once
#include "sprite.h"
class SpriteAnim : public Sprite
{
private:
    /* data */
    int _current_frame = 0;
    int _total_frames = 0;
    int _fps = 10;
    float _float_timer = 0.0f;
    float _frame_time = 0.0f;

public:
    static SpriteAnim *addSpriteAnimChild(ObjectScreen *parrent, const std::string &file_path, float scale = 1.0f);

    virtual void update(float dt) override;
    virtual void setTexture(const Texture &texture) override;
    int getCurrentFrame() { return _current_frame; }
    void setCurrentFrame(int frame) { _current_frame = frame; }
    int getTotalFrames() { return _total_frames; }
    void setTotalFrames(int frames) { _total_frames = frames; }
    int getFps() { return _fps; }
    void setFps(int fps) { _fps = fps; }
};
