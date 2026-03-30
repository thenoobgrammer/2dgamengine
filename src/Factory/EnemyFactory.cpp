#include "EnemyFactory.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "../Components/AIComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/InventoryComponent.h"
#include "../Components/NameComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TagComponent.h"
#include "../Components/TransformComponent.h"
#include "reader.h"

// EnemyFactory::EnemyFactory(const std::unique_ptr<Registry>& registry)
//   : registry(registry.get()) {
//   enemyDatabase = {
//     {EnemyType::Tank, {"tank", "tank", 32, 32, 50, 30.0f, AIBehavior::Chase}},
//     {EnemyType::Truck, {"truck", "truck", 32, 32, 50, 20.0f, AIBehavior::Chase}},
//     {EnemyType::Skeleton, {"name", "truck", 32, 32, 50, 20.0f, AIBehavior::Chase}}
//   };
// }

void EnemyFactory::Spawn(EnemyType type, std::string variant, glm::vec2 position = glm::vec2(0), const int count = 1) {
  if (enemyDatabaseV2.find(type) == enemyDatabaseV2.end()) {
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
    entity.AddComponent<HealthComponent>(data.variants.at(variant).health);
    entity.AddComponent<AIComponent>(data.variants.at(variant).chaseSpeed, data.variants.at(variant).behavior);
  }
}

void EnemyFactory::LoadEnemies() {
    std::string enemiesDir = "../assetsv2/entities/";

    for (const auto &entry: std::filesystem::directory_iterator(enemiesDir)) {
        Logger::Log("Loaded file: " +  entry.path().string());
        std::string path = entry.path().string();
        std::ifstream file(path, std::ifstream::binary);

        Json::Value data;
        Json::CharReaderBuilder readerBuilder;
        std::string errs;

        if (Json::parseFromStream(readerBuilder, file, &data, &errs)) {
            Logger::Log("Successfully loaded enemy from " + path);
        }

        const auto type = data["type"].asString();
        const auto variants = data["variants"];
        const auto sprite_id = data["sprite_id"].asString();
        const int sprite_width = data["sprite_width"].asInt();
        const int sprite_height = data["sprite_height"].asInt();

        EnemyData enemy = { type, sprite_id, sprite_width, sprite_height, {} };

        if (variants.isObject()) {
            for (auto variantKey : variants.getMemberNames()) {
                const auto name = data["name"].asString();
                const int health = variants[variantKey]["health"].asInt();
                const int damage = variants[variantKey]["damage"].asInt();
                const float chaseSpeed = variants[variantKey]["chaseSpeed"].asFloat();
                const auto lootTableJson = variants[variantKey]["lootTable"];

                std::vector<LootTableElement> lootTable;
                for (const auto loot : lootTableJson) {
                    lootTable.push_back({
                        loot["item"].asString(),
                        loot["dropRate"].asFloat()
                    });
                }

                enemy.variants.emplace(variantKey, EnemyVariantProperty{ health, damage, chaseSpeed, lootTable, AIBehavior::Chase });
            }
        }

        enemyDatabaseV2.emplace(EnemyTypeFromString(type), enemy);
    }
}

EnemyType EnemyTypeFromString(const std::string& str) {
    if (str == "skeleton" || str == "Skeleton") return EnemyType::Skeleton;
    return EnemyType::None;
}

