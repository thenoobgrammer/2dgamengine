#ifndef INC_2DGAMEENGINE_LOOTTABLEELEMENT_H
#define INC_2DGAMEENGINE_LOOTTABLEELEMENT_H

#include "Item.h"

struct DropItem {
    Item item;
    float dropRate;
    int count;
};

#endif
