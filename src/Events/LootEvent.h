#ifndef INC_2DGAMEENGINE_PICKUPITEMEVENT_H
#define INC_2DGAMEENGINE_PICKUPITEMEVENT_H

#include "../ECS/ECS.h"
#include "../EventBus/Event.h"

class LootEvent: public Event {
public:
    Entity drop;
    LootEvent(Entity item): drop(item) {}
};

#endif
