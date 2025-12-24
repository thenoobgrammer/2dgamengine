#ifndef INC_2DGAMEENGINE_ANIMATIONCOMPONENT_H
#define INC_2DGAMEENGINE_ANIMATIONCOMPONENT_H

#include <SDL.h>

struct AnimationComponent {
    int numFrames;
    int numColumns;
    int currentFrame;
    int frameSpeedRate;
    bool isLoop;
    int startTime;

    AnimationComponent(int numFrames = 1, int numColumns = 1, int frameSpeedRate = 1, bool isLoop = true) {
        this->numFrames = numFrames;
        this->numColumns = numColumns;
        this->currentFrame = 0;
        this->frameSpeedRate = frameSpeedRate;
        this->isLoop = isLoop;
        this->startTime = SDL_GetTicks();
    }
};


#endif