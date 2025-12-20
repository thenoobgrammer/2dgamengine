#ifndef INC_2DGAMEENGINE_PROJECTILECOMPONENT_H
#define INC_2DGAMEENGINE_PROJECTILECOMPONENT_H

struct ProjectileComponent {
  int damage;
  ProjectileComponent(int damage = 0) : damage(damage) {}
};

#endif // INC_2DGAMEENGINE_PROJECTILECOMPONENT_H
