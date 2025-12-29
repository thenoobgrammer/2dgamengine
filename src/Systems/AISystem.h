#ifndef INC_2DGAMEENGINE_AISYSTEM_H
#define INC_2DGAMEENGINE_AISYSTEM_H

#include "../Components/AIComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/TagComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"

class AISystem: public System {
  public:
    AISystem() {
      RequireComponent<TransformComponent>();
      RequireComponent<RigidBodyComponent>();
    }
    ~AISystem() = default;

    void Update() {
      TransformComponent playerTransform;

      for (auto entity: GetSystemEntities()) {
        if (entity.HasComponent<TagComponent>() && entity.GetComponent<TagComponent>().tag == Tag::Player) {
           playerTransform = entity.GetComponent<TransformComponent>();
        }
      }

      for (auto entity: GetSystemEntities()) {
        if (!entity.HasComponent<AIComponent>()) continue;

        const auto& ai = entity.GetComponent<AIComponent>();
        auto& transform = entity.GetComponent<TransformComponent>();
        auto& rigidBody = entity.GetComponent<RigidBodyComponent>();

        if (ai.behavior == AIBehavior::Chase) {
          const int directionX = (playerTransform.position.x < transform.position.x) ? -1 : 1;
          const int directionY = (playerTransform.position.y < transform.position.y) ? -1 : 1;
          rigidBody.velocity.x = directionX * ai.chaseSpeed;
          rigidBody.velocity.y = directionY * ai.chaseSpeed;


          float deltaX = playerTransform.position.x - transform.position.x;
          float deltaY = playerTransform.position.y - transform.position.y;
          float angleRadians = std::atan2(deltaY, deltaX);
          float angleDegrees = angleRadians * 180.0f / M_PI;
          transform.rotation = angleDegrees;

        } else if (ai.behavior == AIBehavior::Idle) {
          rigidBody.velocity.x = 0;
          rigidBody.velocity.y = 0;
        }
      }
    }
};

#endif
