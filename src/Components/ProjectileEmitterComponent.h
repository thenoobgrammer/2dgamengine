#ifndef INC_2DGAMEENGINE_PROJECTILEEMITTERCOMPONENT_H
#define INC_2DGAMEENGINE_PROJECTILEEMITTERCOMPONENT_H

#include "glm/glm.hpp"

struct ProjectileEmitterComponent {
    glm::vec2 velocity;
    int repeatFrequency;
    int duration;
    int hitPercentageDamage;
    int lastEmissionTime;
    bool isFriendly;
    bool shouldEmit;

    ProjectileEmitterComponent(
        glm::vec2 velocity = glm::vec2(0.0, 0.0),
        int repeatFrequency = 0,
        int duration = 10000, // in ms
        int hitPercentageDamage = 10, // in %
        int lastEmissionTime = 0,
        bool isFriendly = false,
        bool shouldEmit = false,
        float speed = 200
        ) {
        this->velocity = velocity;
        this->repeatFrequency = repeatFrequency;
        this->duration = duration;
        this->hitPercentageDamage = hitPercentageDamage;
        this->lastEmissionTime = lastEmissionTime;
        this->isFriendly = isFriendly;
        this->shouldEmit = shouldEmit;
    }
};

#endif //INC_2DGAMEENGINE_PROJECTILEEMITTERCOMPONENT_H