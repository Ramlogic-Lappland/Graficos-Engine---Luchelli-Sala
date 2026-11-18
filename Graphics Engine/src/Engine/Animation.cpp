#include "Animation.h"

#include <cmath>
#include <cstdint>

Animation::Animation(int row, int firstColumn, int frameCount,float framesPerSecond, bool loop) : row(row), firstColumn(firstColumn), frameCount(frameCount),fps(framesPerSecond), loop(loop)
{
}

void Animation::Play(bool restart)
{
    if (restart)
    {
        currentFrame = 0;
        accumulatedSeconds = 0.0;
        finished = false;
    }

    if (finished && !restart)
        return;

    playing = true;
    paused = false;
}

void Animation::Pause()
{
    if (playing)
        paused = true;
}

void Animation::Resume()
{
    if (playing)
        paused = false;
}

void Animation::Stop()
{
    playing = false;
    paused = false;
    finished = false;
    currentFrame = 0;
    accumulatedSeconds = 0.0;
}

void Animation::Update(float deltaTime)
{
    if (!playing || paused || deltaTime <= 0.0f || fps <= 0.0f || frameCount <= 0)
        return;

    const double frameDuration = 1.0 / static_cast<double>(fps);
    accumulatedSeconds += static_cast<double>(deltaTime);

    if (accumulatedSeconds < frameDuration)
        return;

    // Advance multiple frames if rendering stays still
    const double steps = std::floor(accumulatedSeconds / frameDuration);
    accumulatedSeconds = std::fmod(accumulatedSeconds, frameDuration);

    if (loop)
    {
        const int advance = static_cast<int>(std::fmod(steps, static_cast<double>(frameCount)));
        currentFrame = (currentFrame + advance) % frameCount;
    }
    else
    {
        const int remaining = frameCount - 1 - currentFrame;
        if (steps >= static_cast<double>(remaining))
        {
            currentFrame = frameCount - 1;
            playing = false;
            finished = true;
            accumulatedSeconds = 0.0;
        }
        else
        {
            currentFrame += static_cast<int>(steps);
        }
    }
}
