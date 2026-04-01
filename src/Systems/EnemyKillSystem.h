#ifndef INC_2DGAMEENGINE_ENEMYKILLSYSTEM_H
#define INC_2DGAMEENGINE_ENEMYKILLSYSTEM_H
#include "../Components/LootTableComponent.h"
#include "../ECS/ECS.h"

class LootSystem: public System {
public:
    LootSystem() {
        RequireComponent<LootTableComponent>();
    }

    void Subscribe(std::unique_ptr<EventBus>& eventBus) {
        // Receives an event that enemy is death
        // Flags a boolean flag on the enemy
    }

    void Update() {
        for (const auto entity: GetSystemEntities()) {

        }
    }
};

#endif
