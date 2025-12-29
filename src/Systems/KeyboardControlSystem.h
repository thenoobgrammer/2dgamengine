#ifndef INC_2DGAMEENGINE_KEYBOARDMOVEMENTSYSTEM_H
#define INC_2DGAMEENGINE_KEYBOARDMOVEMENTSYSTEM_H

#include "../Components/KeyboardControlledComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../EventBus/EventBus.h"
#include "../Events/KeyPressedEvent.h"
#include <memory>

class KeyboardControlSystem : public System {
    public:
        KeyboardControlSystem() {
            RequireComponent<KeyboardControlledComponent>();
            RequireComponent<SpriteComponent>();
            RequireComponent<RigidBodyComponent>();
            RequireComponent<ProjectileEmitterComponent>();
        }

        void Subscribe(std::unique_ptr<EventBus>& eventBus) {
            eventBus->Subscribe<KeyPressedEvent>(this, &KeyboardControlSystem::onKeypress);
        }

        void onKeypress(KeyPressedEvent &keyEvent) {
            for (auto entity: GetSystemEntities()) {
                const auto keyboardcontrol = entity.GetComponent<KeyboardControlledComponent>();
                auto& sprite = entity.GetComponent<SpriteComponent>();
                auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
                auto& projectile = entity.GetComponent<ProjectileEmitterComponent>();

                switch (keyEvent.symbol) {
                    case SDLK_UP:
                    case SDLK_w:
                        rigidbody.velocity=keyboardcontrol.upVeolcity;
                        rigidbody.direction=glm::vec2(0, -1);
                        sprite.srcRect.y = sprite.height * 0;
                        break;
                    case SDLK_RIGHT:
                    case SDLK_d:
                        rigidbody.velocity=keyboardcontrol.rightVeolcity;
                        rigidbody.direction=glm::vec2(1, 0);
                        sprite.srcRect.y = sprite.height * 1;
                        break;
                    case SDLK_DOWN:
                    case SDLK_s:
                        rigidbody.velocity=keyboardcontrol.downVeolcity;
                        rigidbody.direction=glm::vec2(0, 1);
                        sprite.srcRect.y = sprite.height * 2;
                        break;
                    case SDLK_LEFT:
                    case SDLK_a:
                        rigidbody.velocity=keyboardcontrol.leftVeolcity;
                        rigidbody.direction=glm::vec2(-1, 0);
                        sprite.srcRect.y = sprite.height * 3;
                        break;
                    case SDLK_LCTRL:
                        rigidbody.velocity = glm::vec2(0);
                        break;
                    case SDLK_SPACE:
                        projectile.shouldEmit = true;
                        projectile.velocity = rigidbody.direction * 400.0f;
                        break;
                }
            }
        }

        void Update() {}

};

#endif //INC_2DGAMEENGINE_KEYBOARDMOVEMENTSYSTEM_H