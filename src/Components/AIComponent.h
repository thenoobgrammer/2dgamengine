#ifndef INC_2DGAMEENGINE_AICOMPONENT_H
#define INC_2DGAMEENGINE_AICOMPONENT_H

enum class AIBehavior {
  Idle,
  Chase,
  Patrol,
  Flee
};

struct AIComponent {
  AIBehavior behavior;
  float chaseSpeed;

  AIComponent(float chaseSpeed = 0.0f, AIBehavior behavior = AIBehavior::Idle) {
    this->chaseSpeed = chaseSpeed;
    this->behavior = behavior;
  };
};

#endif
