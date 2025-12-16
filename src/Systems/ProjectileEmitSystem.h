#ifndef INC_2DGAMEENGINE_PROJECTILEEMITSYSTEM_H
#define INC_2DGAMEENGINE_PROJECTILEEMITSYSTEM_H

#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../ECS/ECS.h"
#include <SDL.h>

class ProjectileEmitSystem: public System {
public:
    ProjectileEmitSystem() {
        RequireComponent<TransformComponent>();
        RequireComponent<ProjectileEmitterComponent>();
    }

    void Update(std::unique_ptr<Registry>& registry) {
        for (auto entity: GetSystemEntities()) {
            auto projectileEmitter = entity.GetComponent<ProjectileEmitterComponent>();
            auto transform = entity.GetComponent<TransformComponent>();

            if (SDL_GetTicks() - projectileEmitter.lastEmissionTime > projectileEmitter.repeatFrequency) {
                Entity projectile = registry->CreateEntity();
                projectile.AddComponent<TransformComponent>(transform.position, glm::vec2(1.0, 1.0), 0.0);
                projectile.AddComponent<RigidBodyComponent>(projectileEmitter.velocity);
                projectile.AddComponent<SpriteComponent>("bullet-image", 4, 4, 4);
                projectile.AddComponent<BoxColliderComponent>(4, 4);

                // Update projectile emitter component
                projectileEmitter.lastEmissionTime = static_cast<int>(SDL_GetTicks());
            }
        }
    }
};

#endif //INC_2DGAMEENGINE_PROJECTILEEMITSYSTEM_H