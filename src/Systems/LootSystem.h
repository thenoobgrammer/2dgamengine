#ifndef INC_2DGAMEENGINE_ENEMYKILLSYSTEM_H
#define INC_2DGAMEENGINE_ENEMYKILLSYSTEM_H
#include "../Components/LootTableComponent.h"
#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/DropLootEvent.h"
#include "../Factory/ItemFactory.h"
#include <random>

class LootSystem: public System {
public:
    ItemFactory* itemFactory;

    LootSystem() {
        RequireComponent<LootTableComponent>();
    }

    void Subscribe(std::unique_ptr<EventBus>& eventBus, const std::unique_ptr<ItemFactory>& itemFactory) {
        this->itemFactory = itemFactory.get();
        eventBus->Subscribe<DropLootEvent>(this, &LootSystem::onDropLoot);
    }

    void onDropLoot(DropLootEvent& event) {
        for (const auto entity: GetSystemEntities()) {
            auto& lootTable = entity.GetComponent<LootTableComponent>();

            for (const DropItem& drop: lootTable.drops) {
                if (lootTable.shouldDop) {
                    float roll = rand() % 100 / 100.0f;
                    if (roll <= drop.dropRate) {
                        itemFactory->Spawn(drop.item, event.dropPosition);
                    }
                }
            }
        }
    }

    void Update(const std::unique_ptr<Registry>& registry) {}
};

#endif
