#include "EnemyFactory.h"

#include "../Components/AIComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/NameComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TagComponent.h"
#include "../Components/TransformComponent.h"

EnemyFactory::EnemyFactory(const std::unique_ptr<Registry>& registry)
  : registry(registry.get()) {
  enemyDatabase = {
    {EnemyType::Tank, {"tank-a", "tank-image", 32, 32, 50, 30.0f, AIBehavior::Chase}},
    {EnemyType::Truck, {"truck", "truck-image", 32, 32, 50, 20.0f, AIBehavior::Chase}}
  };
}

void EnemyFactory::Spawn(EnemyType type, glm::vec2 position = glm::vec2(0.0, 0.0)) {
  if (enemyDatabase.find(type) == enemyDatabase.end()) {
    Logger::Err("Unknown enemy type");
    return;
  }

  const auto& data = enemyDatabase[type];

  Entity entity = this->registry->CreateEntity();
  entity.AddComponent<NameComponent>(data.name);
  entity.AddComponent<TagComponent>(Tag::Enemy);
  entity.AddComponent<TransformComponent>(position, glm::vec2(1.0, 1.0), 0.0);
  entity.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
  entity.AddComponent<SpriteComponent>(data.spriteId, data.spriteWidth, data.spriteHeight, 1);
  entity.AddComponent<BoxColliderComponent>(data.spriteWidth, data.spriteHeight);
  entity.AddComponent<HealthComponent>(data.health);
  entity.AddComponent<AIComponent>(data.chaseSpeed, data.behavior);
}
