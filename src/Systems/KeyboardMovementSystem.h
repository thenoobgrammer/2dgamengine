#ifndef INC_2DGAMEENGINE_KEYBOARDMOVEMENTSYSTEM_H
#define INC_2DGAMEENGINE_KEYBOARDMOVEMENTSYSTEM_H

#include <memory>
#include "../EventBus/EventBus.h"
#include "../Events/KeyPressedEvent.h"

class KeyboardMovementSystem : public System {
    public:
        KeyboardMovementSystem() {
        }
        void Subscribe(std::unique_ptr<EventBus>& eventBus) {
            eventBus->Subscribe<KeyPressedEvent>(this, &KeyboardMovementSystem::onKeypress);
        }
        void Update() {}
        void onKeypress(KeyPressedEvent &keyEvent) {
            Logger::Log("Key " + std::to_string(keyEvent.symbol) + " was pressed");

        }

};

#endif //INC_2DGAMEENGINE_KEYBOARDMOVEMENTSYSTEM_H