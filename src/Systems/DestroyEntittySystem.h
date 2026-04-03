#ifndef INC_2DGAMEENGINE_DESTROYENTITYSYSTEM_H
#define INC_2DGAMEENGINE_DESTROYENTITYSYSTEM_H

#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"

class DestroyEntitySystem: public System {
public:
    void Subscribe(std::unique_ptr<EventBus>& eventBus) {
        eventBus->Subscribe(this, &DestroyEntitySystem::HandleDestroyEntityEvent);
    }

    void Update() {}

#endif
