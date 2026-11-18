#pragma once

#include "EngineAPI.h"

class ENGINE_API Animation
{
public:
    Animation(int row, int firstColumn, int frameCount,
        float framesPerSecond, bool loop);

    void Play(bool restart = false);
    void Pause();
    void Resume();
    void Stop();
    void Update(float deltaTime);

    int GetRow() const { return row; }
    int GetColumn() const { return firstColumn + currentFrame; }
    int GetCurrentFrame() const { return currentFrame; }
    bool IsPlaying() const { return playing && !paused; }
    bool IsPaused() const { return playing && paused; }
    bool IsFinished() const { return finished; }

private:
    int row = 0;
    int firstColumn = 0;
    int frameCount = 1;
    int currentFrame = 0;
    float fps = 1.0f;
    bool loop = true;
    bool playing = false;
    bool paused = false;
    bool finished = false;
    double accumulatedSeconds = 0.0;
};
