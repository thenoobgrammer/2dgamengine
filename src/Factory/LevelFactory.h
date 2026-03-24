#ifndef INC_2DGAMEENGINE_LEVELFACTORY_H
#define INC_2DGAMEENGINE_LEVELFACTORY_H
#include "EnemyFactory.h"

#include <string>

#include "../ECS/ECS.h"

class LevelFactory {
  Registry *registry = nullptr;
  EnemyFactory *enemy_factory = nullptr;

  public:
  LevelFactory(const std::unique_ptr<Registry> &registry, const std::unique_ptr<EnemyFactory> &enemy_factory);
  void LoadLevel(int level);
  void LoadTilemapLayer(const std::string& assetId, const std::string& filename, int zIndex, int tileSize, double tileScale, int tileSetCols) const;
  void LoadTilemapLayer2(const std::string& assetId, const std::string& filename, int zIndex, int tileSize, double tileScale, int tileSetCols) const;
};

#endif
