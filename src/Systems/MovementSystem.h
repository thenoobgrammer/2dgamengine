#ifndef INC_2DGAMEENGINE_MOVEMENTSYSTEM_H
#define INC_2DGAMEENGINE_MOVEMENTSYSTEM_H

#include "../Components/RigidBodyComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"

class MovementSystem: public System {
public:
    MovementSystem() {
        RequireComponent<TransformComponent>();
        RequireComponent<RigidBodyComponent>();
    }

    void Update(double deltaTime) {
        // TODO : Loop all entities that the system is interested in
        for (auto entity: GetSystemEntities()) {
            auto& transform = entity.GetComponent<TransformComponent>();
            const auto rigidBody = entity.GetComponent<RigidBodyComponent>();

            transform.position.x += rigidBody.velocity.x * deltaTime;
            transform.position.y += rigidBody.velocity.y * deltaTime;

            // Logger::Log(
            //     "Entity id = " +
            //     std::to_string(entity.GetId()) +
            //     " position is now ("
            //     + std::to_string(transform.position.x)
            //     + "," + std::to_string(transform.position.y)
            //     + ")"
            //     );
        }
    }

};


#endif