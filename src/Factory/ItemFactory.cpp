#include "ItemFactory.h"

#include "../Components/BoxColliderComponent.h"
#include "../Components/ConsumableComponent.h"
#include "../Components/NameComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"

ItemFactory::ItemFactory(const std::unique_ptr<Registry> &registry) : registry(registry.get()) {}

void ItemFactory::Spawn(const Item& item, glm::vec2 position, const int count = 1) const {
    for (int i = 0; i < count; i++) {
        Entity newEntity = this->registry->CreateEntity();
        newEntity.AddComponent<NameComponent>();
        newEntity.AddComponent<SpriteComponent>("", 32, 32, 1);
        newEntity.AddComponent<BoxColliderComponent>(32, 32);
        newEntity.AddComponent<TransformComponent>(position);
        if (item.consumable) {
            newEntity.AddComponent<ConsumableComponent>();
        }
        Logger::Log("Spawned item " + std::to_string(i));
    }
}
