#ifndef INC_2DGAMEENGINE_INVENTORYSYSTEM_H
#define INC_2DGAMEENGINE_INVENTORYSYSTEM_H

#include "../Components/PlayerComponent.h"
#include "../Components/InventoryComponent.h"
#include "../ECS/ECS.h"
#include "../Events/PickupItemEvent.h"
#include "../EventBus/EventBus.h"

class InventorySystem: public System {
    enum Filter {
        ByItemType
    };

    enum Sort {
        Alphabetically,
        ByStats
    };
    private:
        EventBus *eventBus = nullptr;
    public:
        InventorySystem() {
            RequireComponent<InventoryComponent>();
        };

        void Subscribe(std::unique_ptr<EventBus>& eventBus) {
            this->eventBus = eventBus.get();
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
            auto entities = GetSystemEntities();

            for (auto &entity: GetSystemEntities()) {
                auto &inventory = entity.GetComponent<InventoryComponent>();
                if (entity.HasComponent<PlayerComponent>() && !isFull(inventory)) {
                    inventory.items.push_back(item);
                }
            }
        };

        void Update() {}
};

#endif
