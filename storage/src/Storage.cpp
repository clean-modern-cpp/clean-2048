#include "storage/Storage.h"

#include <yaml-cpp/yaml.h>

#include <filesystem>
#include <fstream>
#include <string>

namespace storage::key {

const std::string row = "row";
const std::string col = "col";
const std::string pos = "pos";
const std::string value = "value";

}  // namespace storage::key

namespace YAML {

template <>
struct convert<common::Position> {
  static Node encode(const common::Position& pos) {
    Node node;
    node[storage::key::row] = pos.row;
    node[storage::key::col] = pos.col;
    return node;
  }
  static bool decode(const Node& node, common::Position& pos) {
    pos.row = node[storage::key::row].as<common::Index>();
    pos.col = node[storage::key::col].as<common::Index>();
    return true;
  }
};

template <>
struct convert<common::NewAction> {
  static Node encode(const common::NewAction& action) {
    Node node;
    node[storage::key::pos] = action.pos;
    node[storage::key::value] = action.value;
    return node;
  }
  static bool decode(const Node& node, common::NewAction& action) {
    action.pos = node[storage::key::pos].as<common::Position>();
    action.value = node[storage::key::value].as<common::Value>();
    return true;
  }
};

}  // namespace YAML

namespace storage {

const std::string fileName = "game.yaml";

namespace key {

const std::string bestScore = "bestScore";
const std::string score = "score";
const std::string isGameOver = "isGameOver";
const std::string rows = "rows";
const std::string cols = "cols";
const std::string newActions = "newActions";

}  // namespace key

use_case::GameData Storage::loadGame() {
  try {
    YAML::Node node = YAML::LoadFile(fileName);
    use_case::GameData gameData;
    gameData.bestScore = node[key::bestScore].as<int>();
    gameData.score = node[key::score].as<int>();
    gameData.isGameOver = node[key::isGameOver].as<bool>();
    gameData.rows = node[key::rows].as<common::Index>();
    gameData.cols = node[key::cols].as<common::Index>();
    gameData.newActions = node[key::newActions].as<common::NewActions>();
    return gameData;
  } catch (const std::exception& e) {
    return {};
  }
}

void Storage::saveGame(const use_case::GameData& gameData) {
  YAML::Node node;
  node[key::bestScore] = gameData.bestScore;
  node[key::score] = gameData.score;
  node[key::isGameOver] = gameData.isGameOver;
  node[key::rows] = gameData.rows;
  node[key::cols] = gameData.cols;
  node[key::newActions] = gameData.newActions;
  std::ofstream ofs{fileName};
  ofs << node;
}

void Storage::clear() { std::filesystem::remove(fileName); }

}  // namespace storage
