#ifndef INC_2DGAMEENGINE_KEYBOARDCONTROLLEDCOMPONENT_H
#define INC_2DGAMEENGINE_KEYBOARDCONTROLLEDCOMPONENT_H

#include <glm/glm.hpp>

struct KeyboardControlledComponent {
    glm::vec2 upVeolcity;
    glm::vec2 rightVeolcity;
    glm::vec2 downVeolcity;
    glm::vec2 leftVeolcity;

    KeyboardControlledComponent(
        glm::vec2 upVeolcity = glm::vec2(0.0f, 0.0f),
        glm::vec2 rightVeolcity = glm::vec2(0.0f, 0.0f),
        glm::vec2 downVeolcity = glm::vec2(0.0f, 0.0f),
        glm::vec2 leftVeolcity = glm::vec2(0.0f, 0.0f)
    ) {
        this->upVeolcity = upVeolcity;
        this->rightVeolcity = rightVeolcity;
        this->downVeolcity = downVeolcity;
        this->leftVeolcity = leftVeolcity;
    }
};

#endif //INC_2DGAMEENGINE_KEYBOARDCONTROLLEDCOMPONENT_H