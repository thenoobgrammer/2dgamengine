#ifndef INC_2DGAMEENGINE_LIFETIMECOMPONENT_H
#define INC_2DGAMEENGINE_LIFETIMECOMPONENT_H

struct LifeTimeComponent {
  int lifeTime;
  int destroyAt;

  LifeTimeComponent(int lifeTime = 0) : lifeTime(lifeTime) {
    destroyAt = SDL_GetTicks() + lifeTime;
  }
};

#endif
