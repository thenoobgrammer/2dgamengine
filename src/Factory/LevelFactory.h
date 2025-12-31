#ifndef INC_2DGAMEENGINE_LEVELFACTORY_H
#define INC_2DGAMEENGINE_LEVELFACTORY_H
#include <string>

#include "../ECS/ECS.h"

class LevelFactory {
  Registry *registry = nullptr;

  public:
  LevelFactory(const std::unique_ptr<Registry> &registry);
  void LoadLevel(int level);
  void LoadTilemapLayer(const std::string& assetId, const std::string& filename, int zIndex, int tileSize, double tileScale, int tileSetCols) const;
};

#endif
