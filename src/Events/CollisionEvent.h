#ifndef INC_2DGAMEENGINE_COLLISIONEVENT_H
#define INC_2DGAMEENGINE_COLLISIONEVENT_H
#include "../ECS/ECS.h"
#include "../EventBus/Event.h"

class CollisionEvent: public Event {
    public:
        Entity a;
        Entity b;
        CollisionEvent(Entity a, Entity b): a(a), b(b) {}
};

#endif //INC_2DGAMEENGINE_COLLISIONEVENT_H