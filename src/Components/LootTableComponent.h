#ifndef INC_2DGAMEENGINE_LOOTTABLECOMPONENT_H
#define INC_2DGAMEENGINE_LOOTTABLECOMPONENT_H
#include <vector>

struct LootTableComponent {
    std::vector<DropItem> drops;
    bool shouldDop;

    LootTableComponent() = default;
    LootTableComponent(const std::vector<DropItem> &inventory) :
        drops(inventory), shouldDop(false) {}
};

#endif
