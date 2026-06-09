#ifndef INC_2DGAMEENGINE_DROPANIMATIONCOMPONENT_H
#define INC_2DGAMEENGINE_DROPANIMATIONCOMPONENT_H

struct DropAnimationComponent {
    glm::vec2 velocity;
    float gravity = 300.0f;
    float friction = 0.9f;
    float time = 0.0f;
    bool settled = false;
    glm::vec2 dropPosition;

    DropAnimationComponent() = default;
    DropAnimationComponent(glm::vec2 velocity) : velocity(velocity), dropPosition() {}
};

#endif
