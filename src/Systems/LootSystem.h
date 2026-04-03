#ifndef INC_2DGAMEENGINE_ENEMYKILLSYSTEM_H
#define INC_2DGAMEENGINE_ENEMYKILLSYSTEM_H
#include "../Components/LootTableComponent.h"
#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/DropLootEvent.h"
#include "../Factory/ItemFactory.h"


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
                Logger::Log("entity: " + std::to_string(entity.GetId()) + " should drop: " + std::to_string(lootTable.shouldDop));
                if (lootTable.shouldDop) {
                    itemFactory->Spawn(drop.item, event.dropPosition, 1);
                }
            }
        }
    }

    void Update(const std::unique_ptr<Registry>& registry) {}
};

#endif
