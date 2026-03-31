#ifndef INC_2DGAMEENGINE_ENEMY_H
#define INC_2DGAMEENGINE_ENEMY_H
#include "../Components/AIComponent.h"
#include "../ECS/ECS.h"
#include "glm/vec2.hpp"

enum class EnemyType {
    Tank,
    Truck,
    Skeleton,
    None
};

struct LootTableElement {
    std::string item;
    float dropRate;
};

struct EnemyVariantProperty {
    int health;
    int damage;
    float chaseSpeed;
    std::vector<LootTableElement> lootTable;
    AIBehavior behavior;
};

struct EnemyData {
    std::string name;
    std::string spriteId;
    int spriteWidth;
    int spriteHeight;
    std::unordered_map<std::string, EnemyVariantProperty> variants;
};

class EnemyFactory {
    Registry *registry = nullptr;
    std::unordered_map<EnemyType, EnemyData> enemyDatabase;
    std::unordered_map<EnemyType, EnemyData> enemyDatabaseV2;


  public:
    EnemyFactory(const std::unique_ptr<Registry> &registry);
    void Spawn(EnemyType type, std::string variant, glm::vec2 position, int count);
    void LoadEnemies();
    static EnemyType EnemyTypeFromString(const std::string& str);

};

#endif
