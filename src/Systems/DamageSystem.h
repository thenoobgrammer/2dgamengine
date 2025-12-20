#ifndef INC_2DGAMEENGINE_DAMAGESYSTEM_H
#define INC_2DGAMEENGINE_DAMAGESYSTEM_H

#include "../Components/BoxColliderComponent.h"
#include "../Components/NameComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/TagComponent.h"
#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"
#include "../Events/DamageEvent.h"

class DamageSystem: public System {
    private:
        EventBus* eventBus = nullptr;
    public:
        DamageSystem() {
            RequireComponent<BoxColliderComponent>();
        }

        void Subscribe(std::unique_ptr<EventBus>& eventBus) {
            this->eventBus = eventBus.get();
            eventBus->Subscribe<CollisionEvent>(this, &DamageSystem::onCollision);
        }

        void onCollision(CollisionEvent& event) {
            Entity projectile;
            Entity target;

            bool aIsProjectile = event.a.HasComponent<TagComponent>() &&
                event.a.GetComponent<TagComponent>().tag == Tag::Projectile;
            bool bIsProjectile = event.b.HasComponent<TagComponent>() &&
                event.b.GetComponent<TagComponent>().tag == Tag::Projectile;

            if (event.a.HasComponent<NameComponent>()) {
                std::string aName = event.a.GetComponent<NameComponent>().name;
                Logger::Log("A name " + aName);
            }
            if (event.b.HasComponent<NameComponent>()) {
                std::string bName = event.b.GetComponent<NameComponent>().name;
                Logger::Log("B name " + bName);
            }

            if (aIsProjectile && event.b.HasComponent<HealthComponent>()) {
                projectile = event.a;
                target = event.b;
            } else if (bIsProjectile && event.a.HasComponent<HealthComponent>()) {
                projectile = event.b;
                target = event.a;
            } else {
                return;
            }

            eventBus->Emit<DamageEvent>(
                target,
                projectile.GetComponent<ProjectileComponent>().damage);

            projectile.Kill();
        }

        void Update() {

        }
};

#endif //INC_2DGAMEENGINE_DAMAGESYSTEM_H