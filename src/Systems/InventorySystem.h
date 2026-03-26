#ifndef INC_2DGAMEENGINE_INVENTORYSYSTEM_H
#define INC_2DGAMEENGINE_INVENTORYSYSTEM_H

#include "../Components/InventoryComponent.h"
#include "../Components/NameComponent.h"
#include "../ECS/ECS.h"
#include "../Events/PickupItemEvent.h"
#include "../Events/PickupItemEvent.h"
#include "../EventBus/EventBus.h"
#include <string>

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

        void Subscribe(std::unique_ptr<EventBus>& eventBus) {
          eventBus->Subscribe<PickupItemEvent>(this, &InventorySystem::onPickupItem);
        }

        void filter(Filter by) {};
        void sort(Sort by) {};
        void add(Entity &item) {};
        void remove(Entity &) {};
        void transfer(Entity &from, Entity &to, Entity &item) {};
        bool isFull(const InventoryComponent &inventory) { return inventory.items.size() >= inventory.maxSlot; };

        void onPickupItem(PickupItemEvent &event) {
            auto item = event.item;
            Logger::Log("Item in contact with " + item.GetComponent<NameComponent>().name);
            auto entities = GetSystemEntities();

            for (auto &entity: GetSystemEntities()) {
                auto &inventory = entity.GetComponent<InventoryComponent>();
                if (isFull(inventory)) {
                    Logger::Log("Your inventory is full");
                } else {
                    inventory.items.push_back(item);
                    Logger::Log("You picked up and item");
                }
            }
        };

        void Update() {}
};

#endif
