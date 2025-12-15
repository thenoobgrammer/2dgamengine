#ifndef INC_2DGAMEENGINE_DAMAGESYSTEM_H
#define INC_2DGAMEENGINE_DAMAGESYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"

class DamageSystem: public System {
    public:
        DamageSystem() {
            RequireComponent<BoxColliderComponent>();
        }

        void Subscribe(std::unique_ptr<EventBus>& eventBus) {
            eventBus->Subscribe<CollisionEvent>(this, &DamageSystem::onCollision);
        }

        void onCollision(CollisionEvent& event) {
            Logger::Log("DamageSystem::onCollision " + std::to_string(event.a.GetId()) + " and " + std::to_string(event.b.GetId()));
            event.a.Kill();
            event.b.Kill();
        }

        void Update() {

        }
};

#endif //INC_2DGAMEENGINE_DAMAGESYSTEM_H