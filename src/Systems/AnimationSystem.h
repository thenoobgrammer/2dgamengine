#ifndef INC_2DGAMEENGINE_ANIMATIONSYSTEM_H
#define INC_2DGAMEENGINE_ANIMATIONSYSTEM_H

#include <SDL.h>
#include <windows.h>
#include "../Components/AnimationComponent.h"
#include "../Components/SpriteComponent.h"
#include "../ECS/ECS.h"

#include "../Components/DropAnimationComponent.h"

class AnimationSystem: public System {
    public:
        AnimationSystem() {
            RequireComponent<SpriteComponent>();
            // RequireComponent<AnimationComponent>();
        }

        void Update(double deltaTime) {
            // for (auto entity: GetSystemEntities()) {
            //     auto& animation = entity.GetComponent<AnimationComponent>();
            //     auto& sprite = entity.GetComponent<SpriteComponent>();
            //
            //     animation.currentFrame = ((SDL_GetTicks() - animation.startTime) * animation.frameSpeedRate / 1000) % animation.numFrames;
            //
            //     int col = animation.currentFrame % animation.numColumns;
            //     int row = animation.currentFrame / animation.numColumns;
            //
            //     sprite.srcRect.x = col * sprite.width;
            //     sprite.srcRect.y = row * sprite.height;
            // }

            for (auto entity: GetSystemEntities()) {
                if (entity.HasComponent<DropAnimationComponent>()) {
                    auto& animation = entity.GetComponent<DropAnimationComponent>();
                    auto& transform = entity.GetComponent<TransformComponent>();

                    if (!animation.settled) {
                        animation.velocity.y +=  animation.gravity * deltaTime;
                        animation.velocity.x *= animation.friction;
                        transform.position += animation.velocity * static_cast<float>(deltaTime);
                        if (glm::length(animation.velocity) < 5.0f) {
                            animation.settled = true;
                        }
                    }
                }
            }
        }
};

#endif