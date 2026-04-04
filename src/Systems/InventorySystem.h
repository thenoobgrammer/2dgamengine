#ifndef INC_2DGAMEENGINE_INVENTORYSYSTEM_H
#define INC_2DGAMEENGINE_INVENTORYSYSTEM_H

#include "../Components/InventoryComponent.h"
#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/LootEvent.h"

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
        }

        void Subscribe(std::unique_ptr<EventBus>& eventBus) {
            eventBus->Subscribe<LootEvent>(this, &InventorySystem::onLoot);
        }

        void filter(Filter by) {};
        void sort(Sort by) {};
        void add(Entity &item) {};
        void remove(Entity &) {};
        void transfer(Entity &from, Entity &to, Entity &item) {};
        bool isFull(const InventoryComponent &inventory) { return inventory.items.size() >= inventory.maxSlot; };

        void onLoot(LootEvent &event) {
            for (auto &entity: GetSystemEntities()) {
                auto &inventory = entity.GetComponent<InventoryComponent>();
                if (!isFull(inventory)) {
                    Logger::Log("Inventory is not full");
                    inventory.items.push_back(event.drop);
                    event.drop.Kill();
                }
            }
        }

        void Update() {}
};

#endif
