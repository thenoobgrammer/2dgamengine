#ifndef INC_2DGAMEENGINE_MOVEMENTSYSTEM_H
#define INC_2DGAMEENGINE_MOVEMENTSYSTEM_H

#include "../Components/RigidBodyComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/KeyboardControlledComponent.h"
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
            const auto rigidBody = entity.GetComponent<RigidBodyComponent>();

            if (keyboard.heldKeys.count(SDLK_w) || keyboard.heldKeys.count(SDLK_s)) {
                transform.position.y += rigidBody.velocity.y * deltaTime;
            }
            if (keyboard.heldKeys.count(SDLK_a) || keyboard.heldKeys.count(SDLK_d)) {
                transform.position.x += rigidBody.velocity.x * deltaTime;
            }

            // transform.position.x += rigidBody.velocity.x * deltaTime;
            // transform.position.y += rigidBody.velocity.y * deltaTime;
        }
    }
};


#endif
