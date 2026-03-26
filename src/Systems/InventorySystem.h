#ifndef INC_2DGAMEENGINE_INVENTORYSYSTEM_H
#define INC_2DGAMEENGINE_INVENTORYSYSTEM_H

#include "../Components/InventoryComponent.h"
#include "../ECS/ECS.h"

class InventorySystem: public System {
    enum Filter {
        ByItemType
    };

    enum Sort {
        Alphabetically,
        ByStats
    };

    public:
        InventorySystem() {
            RequireComponent<InventoryComponent>();
        };

        void filter(Filter by) {};
        void sort(Sort by) {};
        void add(Entity &item) {};
        void remove(Entity &) {};
        void transfer(Entity &from, Entity &to, Entity &item) {};
        bool isFull(const InventoryComponent &inventory) { return inventory.items.size() >= inventory.maxSlot; };

        void Update() {
            auto entities = GetSystemEntities();

            for (auto i = entities.begin(); i != entities.end(); i++) {
                Entity a = *i;
                auto inventory = a.GetComponent<InventoryComponent>();
            }
        }
};

#endif