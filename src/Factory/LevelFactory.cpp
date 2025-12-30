#include "LevelFactory.h"

#include "../Logger/Logger.h"

#include <fstream>
#include <iosfwd>
#include <iostream>
#include <jsoncpp/json.h>

void LevelFactory::LoadLevel(int level = 0) {
  // TODO:
  //  - 0 is tutorial level
  //  - Level configuration should be inside structured data file
  //  - We already have a function to load the tilesets into the game - use that
  //  - Define a number of enemies per level and how many of each enemies
  std::string filePath = "../assetsv2/levels/level_0.json";
  std::ifstream file(filePath, std::ifstream::binary);

  Json::Value data;
  Json::CharReaderBuilder readerBuilder;
  std::string errs;

  if (Json::parseFromStream(readerBuilder, file, &data, &errs)) {
    Logger::Log("Successfully loaded level from " + filePath);
  }
  Logger::Log("" + data["name"].asString());
  Logger::Log("" + data["tilemap_layers"][0]["asset_id"].asString());
  file.close();
}