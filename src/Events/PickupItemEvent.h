#ifndef INC_2DGAMEENGINE_PICKUPITEMEVENT_H
#define INC_2DGAMEENGINE_PICKUPITEMEVENT_H

#include "../ECS/ECS.h"
#include "../EventBus/Event.h"

class PickupItemEvent: public Event {
public:
    Entity item;
    PickupItemEvent(Entity item): item(item) {}
};

#endif
