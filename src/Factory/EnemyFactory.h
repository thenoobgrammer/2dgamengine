#ifndef INC_2DGAMEENGINE_ENEMY_H
#define INC_2DGAMEENGINE_ENEMY_H
#include "../Components/AIComponent.h"
#include "../ECS/ECS.h"
#include "glm/vec2.hpp"

enum class EnemyType {
  Tank,
  Truck
};

struct EnemyData {
  std::string name;
  std::string spriteId;
  int spriteWidth;
  int spriteHeight;
  int health;
  float chaseSpeed;
  AIBehavior behavior;
};

class EnemyFactory {
  Registry *registry = nullptr;
  std::unordered_map<EnemyType, EnemyData> enemyDatabase;

  public:
    EnemyFactory(const std::unique_ptr<Registry> &registry);
    void Spawn(EnemyType type, glm::vec2 position);
};

#endif
