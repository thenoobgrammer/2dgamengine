#ifndef INC_2DGAMEENGINE_COLLISIONSYSTEM_H
#define INC_2DGAMEENGINE_COLLISIONSYSTEM_H

#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../ECS/ECS.h"
#include "../Events/CollisionEvent.h"
#include "../EventBus/EventBus.h"

class CollisionSystem: public System {
    public:
        CollisionSystem() {
            RequireComponent<TransformComponent>();
            RequireComponent<BoxColliderComponent>();
            RequireComponent<SpriteComponent>();
        }

        void Update(std::unique_ptr<EventBus>& eventBus) {
            auto entities = GetSystemEntities();

            for (auto i = entities.begin(); i != entities.end(); i++) {
                Entity a = *i;
                auto aTransform = a.GetComponent<TransformComponent>();
                auto aCollider = a.GetComponent<BoxColliderComponent>();

                for (auto j = i; j != entities.end(); j++) {
                    Entity b = *j;

                    if (a == b)
                        continue;

                    auto bTransform = b.GetComponent<TransformComponent>();
                    auto bCollider = b.GetComponent<BoxColliderComponent>();

                    const bool collisionHappened = CheckAABBCollision(
                        aTransform.position.x + aCollider.offset.x,
                        aTransform.position.y + aCollider.offset.y,
                        aCollider.width,
                        aCollider.height,
                        bTransform.position.x + bCollider.offset.x,
                        bTransform.position.y + bCollider.offset.y,
                        bCollider.width,
                        bCollider.height
                    );

                    if (collisionHappened) {
                        Logger::Log("Collision detected");
                        eventBus->Emit<CollisionEvent>(a, b);
                    }
                }
            }
        }

        void RenderCollisionBox(SDL_Renderer* renderer) {
            for (auto entity: GetSystemEntities()) {
                auto& collider = entity.GetComponent<BoxColliderComponent>();
                auto& transform = entity.GetComponent<TransformComponent>();

                SDL_Rect collisionBox = {
                    static_cast<int>(transform.position.x + collider.offset.x),
                    static_cast<int>(transform.position.y + collider.offset.y),
                    (collider.width),
                    (collider.height)
                };

                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &collisionBox);
            }
        }

    static bool CheckAABBCollision(double aX, double aY, double aW, double aH, double bX, double bY, double bW, double bH) {
        return (
            aX < bX + bW &&
            aX + aW > bX &&
            aY < bY + bH &&
            aY + aH > bY
        );
    }
};

#endif //INC_2DGAMEENGINE_COLLISIONSYSTEM_H