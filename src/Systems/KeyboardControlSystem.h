#ifndef INC_2DGAMEENGINE_KEYBOARDMOVEMENTSYSTEM_H
#define INC_2DGAMEENGINE_KEYBOARDMOVEMENTSYSTEM_H

#include "../Components/KeyboardControlledComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../EventBus/EventBus.h"
#include "../Events/KeyPressedEvent.h"
#include "../Events/KeyUpEvent.h"
#include "../Events/PickupItemEvent.h"
#include "SDL_keycode.h"
#include <memory>
#include <unordered_set>


class KeyboardControlSystem : public System {
    private:
        EventBus* eventBus = nullptr;
    public:
        KeyboardControlSystem() {
            RequireComponent<KeyboardControlledComponent>();
            RequireComponent<SpriteComponent>();
            RequireComponent<RigidBodyComponent>();
            RequireComponent<ProjectileEmitterComponent>();
        }

        void Subscribe(std::unique_ptr<EventBus>& eventBus) {
            this->eventBus = eventBus.get();
            eventBus->Subscribe<KeyPressedEvent>(this, &KeyboardControlSystem::onKeypress);
            eventBus->Subscribe<KeyUpEvent>(this, &KeyboardControlSystem::onKeyUp);
        }

        void onKeypress(KeyPressedEvent &keyEvent) {
            for (auto entity: GetSystemEntities()) {
                auto& keyboard = entity.GetComponent<KeyboardControlledComponent>();
                auto& sprite = entity.GetComponent<SpriteComponent>();
                auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
                auto& projectile = entity.GetComponent<ProjectileEmitterComponent>();

                switch (keyEvent.symbol) {
                    case SDLK_w:
                        keyboard.heldKeys.insert(SDLK_w);
                        rigidbody.velocity=keyboard.upVeolcity;
                        rigidbody.direction=glm::vec2(0, -1);
                        sprite.srcRect.y = sprite.height * 0;
                        break;
                    case SDLK_d:
                        keyboard.heldKeys.insert(SDLK_d);
                        rigidbody.velocity=keyboard.rightVeolcity;
                        rigidbody.direction=glm::vec2(1, 0);
                        sprite.srcRect.y = sprite.height * 1;
                        break;
                    case SDLK_s:
                        keyboard.heldKeys.insert(SDLK_s);
                        rigidbody.velocity=keyboard.downVeolcity;
                        rigidbody.direction=glm::vec2(0, 1);
                        sprite.srcRect.y = sprite.height * 2;
                        break;
                    case SDLK_a:
                        keyboard.heldKeys.insert(SDLK_a);
                        rigidbody.velocity=keyboard.leftVeolcity;
                        rigidbody.direction=glm::vec2(-1, 0);
                        sprite.srcRect.y = sprite.height * 3;
                        break;
                    case SDLK_LCTRL:
                        rigidbody.velocity = glm::vec2(0);
                        break;
                    case SDLK_SPACE:
                        projectile.shouldEmit = true;
                        projectile.velocity = glm::vec2(1.0) * 400.0f;
                        break;
                    case SDLK_e:
                        eventBus->Emit<PickupItemEvent>(entity);
                        break;
                }
            }
        }

        void onKeyUp(KeyUpEvent &keyEvent) {
            for (auto entity: GetSystemEntities()) {
                auto& sprite = entity.GetComponent<SpriteComponent>();
                auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
                auto& keyboard = entity.GetComponent<KeyboardControlledComponent>();

                switch (keyEvent.symbol) {
                    case SDLK_w:
                        keyboard.heldKeys.erase(SDLK_w);
                        rigidbody.velocity=glm::vec2(0);
                        rigidbody.direction=glm::vec2(0);
                        break;
                    case SDLK_d:
                        keyboard.heldKeys.erase(SDLK_d);
                        rigidbody.velocity=glm::vec2(0);
                        rigidbody.direction=glm::vec2(0);
                        break;
                    case SDLK_s:
                        keyboard.heldKeys.erase(SDLK_s);
                        rigidbody.velocity=glm::vec2(0);
                        rigidbody.direction=glm::vec2(0);
                        break;
                    case SDLK_a:
                        keyboard.heldKeys.erase(SDLK_a);
                        rigidbody.velocity=glm::vec2(0);
                        rigidbody.direction=glm::vec2(0);
                        break;
                }
            }
        }

        void Update() {}

};

#endif //INC_2DGAMEENGINE_KEYBOARDMOVEMENTSYSTEM_H
