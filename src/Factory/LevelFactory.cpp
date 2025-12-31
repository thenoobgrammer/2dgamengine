#include "LevelFactory.h"

#include "../Logger/Logger.h"

#include <fstream>
#include <iosfwd>
#include <iostream>
#include <jsoncpp/json.h>

#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../Game/Game.h"

LevelFactory::LevelFactory(const std::unique_ptr<Registry> &registry) : registry(registry.get()) {}

void LevelFactory::LoadLevel(int level = 0) {
  // TODO:
  //  - 0 is tutorial level
  //  - Level configuration should be inside structured data file
  //  - We already have a function to load the tilesets into the game - use that
  //  - Define a number of enemies per level and how many of each enemies
  std::string filePath = "../assetsv2/levels/level_" + std::to_string(level) + ".json";
  std::ifstream file(filePath, std::ifstream::binary);

  Json::Value data;
  Json::CharReaderBuilder readerBuilder;
  std::string errs;

  if (Json::parseFromStream(readerBuilder, file, &data, &errs)) {
    Logger::Log("Successfully loaded level from " + filePath);
  }
  for (auto tmpl : data["tilemap_layers"]) {
    auto assetId = tmpl["asset_id"].asString();
    auto filename = tmpl["filepath"].asString();
    auto zindex = tmpl["z_index"].asInt();
    auto tilesize = tmpl["tile_size"].asInt();
    auto tilescale = tmpl["tile_scale"].asInt();
    auto tilesetcols = tmpl["tileset_columns"].asInt();

    LoadTilemapLayer(assetId, filename, zindex, tilesize, tilescale, tilesetcols);
  }

  file.close();
}

void LevelFactory::LoadTilemapLayer(const std::string& assetId, const std::string& filename, int zIndex, int tileSize, double tileScale, int tileSetCols) const {
  std::fstream mapFile;
  mapFile.open("../assetsv2/maps/" + filename);

  std::string line;
  int y = 0;
  int maxX = 0;

  while (std::getline(mapFile, line)) {
    std::stringstream ss(line);
    std::string tileIdStr;
    int x = 0;

    while (std::getline(ss, tileIdStr, ',')) {
      int tileId = std::stoi(tileIdStr);
      if (tileId >= 0) {
        int srcRectX = (tileId % tileSetCols) * tileSize;
        int srcRectY = (tileId / tileSetCols) * tileSize;

        Entity tile = registry->CreateEntity();
        tile.AddComponent<TransformComponent>(
            glm::vec2(x * tileScale * tileSize, y * tileScale * tileSize),
            glm::vec2(tileScale, tileScale),
            0.0
        );
        tile.AddComponent<SpriteComponent>(assetId, tileSize, tileSize, zIndex, false, srcRectX, srcRectY);
      }
      x++;
    }
    if (x > maxX) maxX = x;
    y++;
  }

  mapFile.close();
  Game::mapWidth = maxX * tileSize * tileScale;
  Game::mapHeight = y * tileSize * tileScale;
}