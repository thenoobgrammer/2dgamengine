#ifndef INC_2DGAMEENGINE_ENEMYVARIANTCLASS_H
#define INC_2DGAMEENGINE_ENEMYVARIANTCLASS_H

#include "AIBehavior.h"
#include "LootTableElement.h"

#include <vector>

struct EnemyVariantProperty {
    int health;
    int damage;
    float chaseSpeed;
    std::vector<LootTableElement> lootTable;
    AIBehavior behavior;
};

#endif
