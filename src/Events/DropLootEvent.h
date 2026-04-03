#ifndef INC_2DGAMEENGINE_DROPLOOTEVENT_H
#define INC_2DGAMEENGINE_DROPLOOTEVENT_H

#include <utility>

#include "../EventBus/Event.h"

class DropLootEvent: public Event {
    public:
        std::vector<DropItem> inventory;
        glm::vec2 dropPosition;
        DropLootEvent(std::vector<DropItem> inventory, glm::vec2 lastPosition) : inventory(std::move(inventory)), dropPosition(lastPosition) {}
};

#endif
