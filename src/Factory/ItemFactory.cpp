#include "ItemFactory.h"

#include "../Components/BoxColliderComponent.h"
#include "../Components/ConsumableComponent.h"
#include "../Components/DropAnimationComponent.h"
#include "../Components/ItemComponent.h"
#include "../Components/NameComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"

ItemFactory::ItemFactory(const std::unique_ptr<Registry> &registry) : registry(registry.get()) {}

void ItemFactory::Spawn(const Item& item, glm::vec2 position, int count) const {
    for (int i = 0; i < count; i++) {
        Entity newEntity = this->registry->CreateEntity();
        newEntity.AddComponent<NameComponent>();
        newEntity.AddComponent<SpriteComponent>("", 16, 16, 1);
        newEntity.AddComponent<BoxColliderComponent>(16, 16);
        newEntity.AddComponent<TransformComponent>(position);
        newEntity.AddComponent<ItemComponent>(item.name, item.description);
        float angle = (rand() % 360) * M_PI / 180.0f;
        float speed = 50.0f + rand() % 100;
        auto velocity = glm::vec2(cos(angle) * speed, -speed);
        newEntity.AddComponent<DropAnimationComponent>(velocity);
        if (item.consumable) {
            newEntity.AddComponent<ConsumableComponent>();
        }
    }
}
