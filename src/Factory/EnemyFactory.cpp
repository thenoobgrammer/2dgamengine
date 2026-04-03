#include "EnemyFactory.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "../Components/AIComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/InventoryComponent.h"
#include "../Components/LootTableComponent.h"
#include "../Components/NameComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TagComponent.h"
#include "../Components/TransformComponent.h"
#include "reader.h"

EnemyFactory::EnemyFactory(const std::unique_ptr<Registry>& registry)
  : registry(registry.get()) {
    LoadEnemies();
}

void EnemyFactory::Spawn(EnemyType type, std::string variant, glm::vec2 position = glm::vec2(0), const int count = 1) {
    if (enemyDatabase.find(type) == enemyDatabase.end()) {
        Logger::Err("Unknown enemy type");
        return;
    }
    const auto& data = enemyDatabase[type];

    for (int i = 0; i < count; i++) {
        glm::vec2 spawnPos = position + glm::vec2(rand() % 1000, rand() % 1000);

        Entity entity = this->registry->CreateEntity();

        entity.AddComponent<NameComponent>(data.name);
        entity.AddComponent<TagComponent>(Tag::Enemy);
        entity.AddComponent<TransformComponent>(spawnPos, glm::vec2(1.0, 1.0), 0.0);
        entity.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
        entity.AddComponent<SpriteComponent>(data.variants.at(variant).spriteId, data.variants.at(variant).spriteWidth, data.variants.at(variant).spriteHeight, 1);
        entity.AddComponent<BoxColliderComponent>(data.variants.at(variant).spriteWidth, data.variants.at(variant).spriteHeight);
        entity.AddComponent<HealthComponent>(data.variants.at(variant).health);
        entity.AddComponent<LootTableComponent>(data.variants.at(variant).lootTable);
        // entity.AddComponent<AIComponent>(data.variants.at(variant).chaseSpeed, data.variants.at(variant).behavior);
    }
}

void EnemyFactory::LoadEnemies() {
    std::string enemiesDir = std::string(ASSETS_PATH) + "assets/entities/";

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
        EnemyData enemy = { type, {} };

        if (variants.isObject()) {
            for (auto variantKey : variants.getMemberNames()) {
                const auto name = data["name"].asString();
                const int health = variants[variantKey]["health"].asInt();
                const int damage = variants[variantKey]["damage"].asInt();
                const auto sprite_id = variants[variantKey]["spriteId"].asString();
                const int sprite_width = variants[variantKey]["spriteWidth"].asInt();
                const int sprite_height = variants[variantKey]["spriteHeight"].asInt();
                const float chaseSpeed = variants[variantKey]["chaseSpeed"].asFloat();
                const auto dropTableJson = variants[variantKey]["dropTable"];

                std::vector<DropItem> dropTable;
                for (const auto& drop : dropTableJson) {
                    Item item = {
                        drop["item"].asString(),
                        drop["description"].asString(),
                        drop["consumable"].asBool(),
                    };
                    dropTable.push_back({ item, drop["dropRate"].asFloat() });
                }

                enemy.variants.emplace(variantKey, EnemyVariantProperty{ health, damage, chaseSpeed, sprite_id, sprite_width, sprite_height, dropTable, AIBehavior::Chase });
            }
        }

        enemyDatabase.emplace(EnemyTypeFromString(type), enemy);

        file.close();
    }
}

EnemyType EnemyFactory::EnemyTypeFromString(const std::string& str) {
    if (str == "skeleton" || str == "Skeleton") return EnemyType::Skeleton;
    return EnemyType::None;
}