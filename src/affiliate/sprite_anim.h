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
    bool _is_loop = true;

public:
    static SpriteAnim *addSpriteAnimChild(ObjectScreen *parrent, const std::string &file_path, float scale = 1.0f, AnchorType anchor = AnchorType::CENTER);

    virtual void update(float dt) override;
    virtual void setTexture(const Texture &texture) override;
    int getCurrentFrame() const { return _current_frame; }
    void setCurrentFrame(int frame) { _current_frame = frame; }
    int getTotalFrames() const { return _total_frames; }
    void setTotalFrames(int frames) { _total_frames = frames; }
    int getFps() const { return _fps; }
    void setFps(int fps) { _fps = fps; }
    void setFrameTime(float time) { _frame_time = time; }
    float getFrameTime() const { return _frame_time; }
    bool getIsLoop() const { return _is_loop; }
    void setIsLoop(bool loop) { _is_loop = loop; }
};
