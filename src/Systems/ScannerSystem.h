#ifndef INC_2DGAMEENGINE_SCANNERSYSTEM_H
#define INC_2DGAMEENGINE_SCANNERSYSTEM_H
#include "../Components/ItemComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"

class ScannerSystem: public System {
public:
    void Update(std::unique_ptr<Registry>& registry, std::unique_ptr<EventBus>& eventBus) {
        Signature signature;
        signature.set(Component<ItemComponent>::GetId());
        signature.set(Component<TransformComponent>::GetId());

        std::vector<Entity> items = registry->GetEntitiesWithComponents(signature);

        for (auto& entity : GetSystemEntities()) {
            if (entity.HasComponent<PlayerComponent>()) {
                auto& player = entity.GetComponent<PlayerComponent>();
                auto& playerTransform = entity.GetComponent<TransformComponent>();
                for (auto item : items) {
                    auto& itemTransform = item.GetComponent<TransformComponent>();
                    if (glm::distance(playerTransform.position, itemTransform.position) <= player.pickupRadius) {
                        eventBus->Emit<LootEvent>(item);
                    }
                }
            }
        }
    }
};

#endif
