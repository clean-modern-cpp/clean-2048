#include "storage/Storage.h"

#include <yaml-cpp/yaml.h>

#include <filesystem>
#include <fstream>
#include <string>

namespace YAML {

template <>
struct convert<common::NewAction> {
  static Node encode(const common::NewAction& newAction) {
    Node node(NodeType::Sequence);
    node.push_back(newAction.pos.row);
    node.push_back(newAction.pos.col);
    node.push_back(newAction.value);
    return node;
  }
  static bool decode(const Node& node, common::NewAction& newAction) {
    if (!node.IsSequence() || node.size() != 3) {
      return false;
    }
    newAction.pos.row = node[0].as<common::Index>();
    newAction.pos.col = node[1].as<common::Index>();
    newAction.value = node[2].as<common::Value>();
    return true;
  }
};

}  // namespace YAML

namespace storage {

const std::string scoreFileName = "score.yaml";
const std::string boardFileName = "board.yaml";

namespace key {

const std::string score = "score";
const std::string bestScore = "bestScore";
const std::string rows = "rows";
const std::string cols = "cols";
const std::string newActions = "newActions";

}  // namespace key

constexpr int initialScore = 0;
constexpr int initialBestScore = 0;

constexpr int initialRows = 4;
constexpr int initialCols = 4;

use_case::ScoreData Storage::loadScore() {
  try {
    YAML::Node scoreNode = YAML::LoadFile(scoreFileName);
    use_case::ScoreData scoreData;
    scoreData.score = scoreNode[key::score].as<int>();
    scoreData.bestScore = scoreNode[key::bestScore].as<int>();
    return scoreData;
  } catch (const std::exception&) {
    return {initialScore, initialBestScore};
  }
}

use_case::BoardData Storage::loadBoard() {
  try {
    YAML::Node boardNode = YAML::LoadFile(boardFileName);
    use_case::BoardData boardData;
    boardData.rows = boardNode[key::rows].as<common::Index>();
    boardData.cols = boardNode[key::cols].as<common::Index>();
    boardData.newActions = boardNode[key::newActions].as<common::NewActions>();
    return boardData;
  } catch (const std::exception&) {
    return {initialRows, initialCols, {}};
  }
}

void Storage::saveScore(const use_case::ScoreData& scoreData) {
  YAML::Node scoreNode;
  scoreNode[key::score] = scoreData.score;
  scoreNode[key::bestScore] = scoreData.bestScore;
  std::ofstream ofs{scoreFileName};
  ofs << scoreNode;
}

void Storage::saveBoard(const use_case::BoardData& boardData) {
  YAML::Node boardNode;
  boardNode[key::rows] = boardData.rows;
  boardNode[key::cols] = boardData.cols;
  boardNode[key::newActions] = boardData.newActions;
  std::ofstream ofs{boardFileName};
  ofs << boardNode;
}

void Storage::clear() {
  std::filesystem::remove(scoreFileName);
  std::filesystem::remove(boardFileName);
}

}  // namespace storage
