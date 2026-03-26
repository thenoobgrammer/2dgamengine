#ifndef INC_2DGAMEENGINE_ITEM_H
#define INC_2DGAMEENGINE_ITEM_H

#include <string>

struct ItemComponent {
    enum ItemType {
        Consumable,
        Weapon,
        Shield,
        Armor,
        Quest,
        WorldItem
    };

    std::string name;
    std::string description;
    ItemType type;

    ItemComponent(std::string name = "",  std::string description = "", ItemType type = WorldItem) {
        this->name = name;
        this->description = description;
        this->type = type;
    }
};


#endif