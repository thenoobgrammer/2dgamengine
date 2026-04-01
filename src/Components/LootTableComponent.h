#ifndef INC_2DGAMEENGINE_LOOTTABLECOMPONENT_H
#define INC_2DGAMEENGINE_LOOTTABLECOMPONENT_H
#include <vector>

struct LootTableComponent {
    std::vector<LootTableElement> items;

    LootTableComponent() = default;
    LootTableComponent(const std::vector<LootTableElement> &items) : items(items) {}
};

#endif
