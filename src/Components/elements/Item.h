#ifndef INC_2DGAMEENGINE_ITEM_H
#define INC_2DGAMEENGINE_ITEM_H
#include <string>

struct Item {
    std::string name;
    std::string description;
    bool consumable = false;
};

#endif
