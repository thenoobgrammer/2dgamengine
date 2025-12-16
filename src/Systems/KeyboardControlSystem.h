#ifndef INC_2DGAMEENGINE_KEYBOARDMOVEMENTSYSTEM_H
#define INC_2DGAMEENGINE_KEYBOARDMOVEMENTSYSTEM_H

#include <memory>
#include "../EventBus/EventBus.h"
#include "../Events/KeyPressedEvent.h"
#include  "../Components/RigidBodyComponent.h"
#include  "../Components/KeyboardControlledComponent.h"
#include  "../Components/SpriteComponent.h"

class KeyboardControlSystem : public System {
    public:
        KeyboardControlSystem() {
            RequireComponent<KeyboardControlledComponent>();
            RequireComponent<SpriteComponent>();
            RequireComponent<RigidBodyComponent>();
        }
        void Subscribe(std::unique_ptr<EventBus>& eventBus) {
            eventBus->Subscribe<KeyPressedEvent>(this, &KeyboardControlSystem::onKeypress);
        }

        void onKeypress(KeyPressedEvent &keyEvent) {
            for (auto entity: GetSystemEntities()) {
                const auto keyboardcontrol = entity.GetComponent<KeyboardControlledComponent>();
                auto& sprite = entity.GetComponent<SpriteComponent>();
                auto& rigidbody = entity.GetComponent<RigidBodyComponent>();

                switch (keyEvent.symbol) {
                    case SDLK_UP:
                        rigidbody.velocity=keyboardcontrol.upVeolcity;
                        sprite.srcRect.y = sprite.height * 0;
                        break;
                    case SDLK_RIGHT:
                        rigidbody.velocity=keyboardcontrol.rightVeolcity;
                        sprite.srcRect.y = sprite.height * 1;
                        break;
                    case SDLK_DOWN:
                        rigidbody.velocity=keyboardcontrol.downVeolcity;
                        sprite.srcRect.y = sprite.height * 2;
                        break;
                    case SDLK_LEFT:
                        rigidbody.velocity=keyboardcontrol.leftVeolcity;
                        sprite.srcRect.y = sprite.height * 3;
                        break;
                }
            }
        }

        void Update() {}

};

#endif //INC_2DGAMEENGINE_KEYBOARDMOVEMENTSYSTEM_H