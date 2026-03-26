#ifndef INC_2DGAMEENGINE_INVENTORYCOMPONENT_H
#define INC_2DGAMEENGINE_INVENTORYCOMPONENT_H
#include "../ECS/ECS.h"

struct InventoryComponent {
    std::vector<Entity> items;
    int maxSlot;

    InventoryComponent(std::vector<Entity> items = nullptr, int maxSlot = 20) {
        this->items = items;
        this->maxSlot = maxSlot;
    }
};

#endif