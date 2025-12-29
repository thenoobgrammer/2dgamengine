#ifndef INC_2DGAMEENGINE_PROJECTILEEMITSYSTEM_H
#define INC_2DGAMEENGINE_PROJECTILEEMITSYSTEM_H

#include "../Components/BoxColliderComponent.h"
#include "../Components/MouseTrackComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
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
            auto& projectileEmitter = entity.GetComponent<ProjectileEmitterComponent>();
            const auto transform = entity.GetComponent<TransformComponent>();

            if ((projectileEmitter.repeatFrequency != 0 &&
                SDL_GetTicks() - projectileEmitter.lastEmissionTime > projectileEmitter.repeatFrequency)
                || projectileEmitter.shouldEmit) {
                glm::vec2 projectilePosition = transform.position;
                if (entity.HasComponent<SpriteComponent>()) {
                    const auto sprite = entity.GetComponent<SpriteComponent>();
                    projectilePosition.x += (transform.scale.x * sprite.width / 2);
                    projectilePosition.y += (transform.scale.y * sprite.height / 2);
                }
                if (entity.HasComponent<PlayerComponent>()) {
                    auto track = entity.GetComponent<MouseTrackComponent>();

                }
                Entity projectile = registry->CreateEntity();
                projectile.AddComponent<NameComponent>("projectile");
                projectile.AddComponent<TagComponent>(Tag::Projectile);
                projectile.AddComponent<ProjectileComponent>(projectileEmitter.damage);
                projectile.AddComponent<TransformComponent>(projectilePosition, glm::vec2(1.0, 1.0), 0.0);
                projectile.AddComponent<RigidBodyComponent>(projectileEmitter.velocity);
                projectile.AddComponent<SpriteComponent>("bullet-image", 4, 4, 4);
                projectile.AddComponent<BoxColliderComponent>(4, 4);

                // Update projectile emitter component
                projectileEmitter.lastEmissionTime = static_cast<int>(SDL_GetTicks());
                projectileEmitter.shouldEmit = false;
            }
        }
    }
};

#endif //INC_2DGAMEENGINE_PROJECTILEEMITSYSTEM_H