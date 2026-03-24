#include "EnemyFactory.h"

#include "../Components/AIComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/NameComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TagComponent.h"
#include "../Components/TransformComponent.h"
#include "../Game/Game.h"

EnemyFactory::EnemyFactory(const std::unique_ptr<Registry>& registry)
  : registry(registry.get()) {
  enemyDatabase = {
    {EnemyType::Tank, {"tank", "tank", 32, 32, 50, 30.0f, AIBehavior::Chase}},
    {EnemyType::Truck, {"truck", "truck", 32, 32, 50, 20.0f, AIBehavior::Chase}}
  };
}

void EnemyFactory::Spawn(EnemyType type, glm::vec2 position = glm::vec2(0), const int count = 1) {
  if (enemyDatabase.find(type) == enemyDatabase.end()) {
    Logger::Err("Unknown enemy type");
    return;
  }
  const auto& data = enemyDatabase[type];

  for (int i = 0; i < count; i++) {
    glm::vec2 spawnPos = position + glm::vec2(rand() % 1000, rand() % 1000);
    Logger::Log("Spawning " + std::to_string(count));
    Entity entity = this->registry->CreateEntity();
    entity.AddComponent<NameComponent>(data.name);
    entity.AddComponent<TagComponent>(Tag::Enemy);
    entity.AddComponent<TransformComponent>(spawnPos, glm::vec2(1.0, 1.0), 0.0);
    entity.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
    entity.AddComponent<SpriteComponent>(data.spriteId, data.spriteWidth, data.spriteHeight, 1);
    entity.AddComponent<BoxColliderComponent>(data.spriteWidth, data.spriteHeight);
    entity.AddComponent<HealthComponent>(data.health);
    entity.AddComponent<AIComponent>(data.chaseSpeed, data.behavior);
  }
}