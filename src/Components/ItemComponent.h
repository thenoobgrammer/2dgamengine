#ifndef INC_2DGAMEENGINE_ITEMCOMPONENT_H
#define INC_2DGAMEENGINE_ITEMCOMPONENT_H

#include "elements/ItemType.h"
#include <string>

struct ItemComponent {
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