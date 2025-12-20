#ifndef INC_2DGAMEENGINE_SPRITECOMPONENT_H
#define INC_2DGAMEENGINE_SPRITECOMPONENT_H

#include <string>
#include <SDL.h>

struct SpriteComponent {
    std::string assetId;
    int width;
    int height;
    int zIndex;
    bool isFixed;
    SDL_Rect srcRect;

    SpriteComponent(const std::string &assetId = "", int width = 0, int height = 0, int zIndex = 0,  bool isFixed = false, int srcRectX =  0, int srcRectY = 0) {
        this->assetId = assetId;
        this->width = width;
        this->height = height;
        this->zIndex = zIndex;
        this->isFixed = isFixed;
        this->srcRect = { srcRectX, srcRectY, width, height };
    };
};


#endif //INC_2DGAMEENGINE_SPRITECOMPONENT_H