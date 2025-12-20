#ifndef INC_2DGAMEENGINE_DAMAGEEVENT_H
#define INC_2DGAMEENGINE_DAMAGEEVENT_H

#include "../ECS/ECS.h"
#include "../EventBus/Event.h"

class DamageEvent: public Event {
  public:
    Entity target;
    int damage;
    DamageEvent(Entity target, int damage): target(target), damage(damage) {}
};

#endif // INC_2DGAMEENGINE_DAMAGEEVENT_H
