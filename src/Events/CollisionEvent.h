#ifndef INC_2DGAMEENGINE_COLLISIONEVENT_H
#define INC_2DGAMEENGINE_COLLISIONEVENT_H
#include "../ECS/ECS.h"
#include "../EventBus/Event.h"

class CollisionEvent: public Event {
    public:
        Entity a;
        Entity b;
        CollisionEvent(Entity a, Entity b): a(a), b(b) {
          // Logger::Log("Entity a " + std::to_string(a.GetId()) + " Entity b " + std::to_string(b.GetId()));
        }
};

#endif //INC_2DGAMEENGINE_COLLISIONEVENT_H