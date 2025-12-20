#ifndef INC_2DGAMEENGINE_PROJECTILEEMITTERCOMPONENT_H
#define INC_2DGAMEENGINE_PROJECTILEEMITTERCOMPONENT_H

#include "glm/glm.hpp"

struct ProjectileEmitterComponent {
    glm::vec2 velocity;
    int repeatFrequency;
    int duration;
    int damage;
    int lastEmissionTime;
    bool isFriendly;
    bool shouldEmit;

    ProjectileEmitterComponent(
        glm::vec2 velocity = glm::vec2(0.0, 0.0),
        int repeatFrequency = 0,
        int duration = 10000, // in ms
        int damage = 10,
        int lastEmissionTime = 0,
        bool isFriendly = false,
        bool shouldEmit = false
        ) {
        this->velocity = velocity;
        this->repeatFrequency = repeatFrequency;
        this->duration = duration;
        this->damage = damage;
        this->lastEmissionTime = lastEmissionTime;
        this->isFriendly = isFriendly;
        this->shouldEmit = shouldEmit;
    }
};

#endif //INC_2DGAMEENGINE_PROJECTILEEMITTERCOMPONENT_H