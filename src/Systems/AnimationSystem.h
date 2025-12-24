#ifndef INC_2DGAMEENGINE_ANIMATIONSYSTEM_H
#define INC_2DGAMEENGINE_ANIMATIONSYSTEM_H

#include "../Components/AnimationComponent.h"
#include "../Components/SpriteComponent.h"
#include "../ECS/ECS.h"
#include <SDL.h>

class AnimationSystem: public System {
    public:
        AnimationSystem() {
            RequireComponent<SpriteComponent>();
            RequireComponent<AnimationComponent>();
        }

        void Update() {
            for (auto entity: GetSystemEntities()) {
                auto& animation = entity.GetComponent<AnimationComponent>();
                auto& sprite = entity.GetComponent<SpriteComponent>();

                animation.currentFrame = ((SDL_GetTicks() - animation.startTime) * animation.frameSpeedRate / 1000) % animation.numFrames;

                int col = animation.currentFrame % animation.numColumns;
                int row = animation.currentFrame / animation.numColumns;

                sprite.srcRect.x = col * sprite.width;
                sprite.srcRect.y = row * sprite.height;
            }
        }
};

#endif