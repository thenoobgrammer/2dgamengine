#ifndef INC_2DGAMEENGINE_RIGIDBODYCOMPONENT_H
#define INC_2DGAMEENGINE_RIGIDBODYCOMPONENT_H

#include "glm/glm.hpp"


struct RigidBodyComponent {
    glm::vec2 velocity;
    glm::vec2 direction;

    RigidBodyComponent(glm::vec2 velocity = glm::vec2(0.0,  0.0), glm::vec2 direction = glm::vec2(1.0,  0.0)) {
        this->velocity = velocity;
        this->direction = direction;
    }
};


#endif //INC_2DGAMEENGINE_RIGIDBODYCOMPONENT_H