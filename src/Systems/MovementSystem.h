#ifndef INC_2DGAMEENGINE_MOVEMENTSYSTEM_H
#define INC_2DGAMEENGINE_MOVEMENTSYSTEM_H

#include "../Components/KeyboardControlledComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"
#include "SDL_keycode.h"

class MovementSystem: public System {
public:
    MovementSystem() {
        RequireComponent<TransformComponent>();
        RequireComponent<RigidBodyComponent>();
    }

    void Update(double deltaTime) {
        for (auto entity: GetSystemEntities()) {
            auto& transform = entity.GetComponent<TransformComponent>();
            auto& keyboard = entity.GetComponent<KeyboardControlledComponent>();
            auto& rigidBody = entity.GetComponent<RigidBodyComponent>();

            glm::vec2 direction(0.0, 0.0);

            if (entity.HasComponent<PlayerComponent>()) {
                if (keyboard.heldKeys.count(SDLK_w)) direction.y -= 1.0;
                if (keyboard.heldKeys.count(SDLK_s)) direction.y += 1.0;
                if (keyboard.heldKeys.count(SDLK_a)) direction.x -= 1.0;
                if (keyboard.heldKeys.count(SDLK_d)) direction.x += 1.0;

                if (glm::length(direction) > 0) {
                    rigidBody.velocity = glm::normalize(direction) * glm::length(rigidBody.velocity);
                } else {
                    rigidBody.velocity = glm::vec2(0);
                }
            }

            transform.position.x += rigidBody.velocity.x * deltaTime;
            transform.position.y += rigidBody.velocity.y * deltaTime;
        }
    }
};


#endif
