#include "storage/Storage.h"

#include <yaml-cpp/yaml.h>

#include <fstream>

namespace storage {

const std::string scoreFileName = "score.yaml";
const std::string boardFileName = "board.yaml";

const std::string scorePropertyName = "score";
const std::string bestScorePropertyName = "bestScore";

const std::string rowsPropertyName = "rows";
const std::string colsPropertyName = "cols";
const std::string valuesPropertyName = "values";

use_case::ScoreStorage Storage::loadScore() {
  YAML::Node scoreNode = YAML::LoadFile(scoreFileName);
  use_case::ScoreStorage scoreStorage;
  scoreStorage.score = scoreNode[scorePropertyName].as<int>();
  scoreStorage.bestScore = scoreNode[bestScorePropertyName].as<int>();
  return scoreStorage;
}

use_case::BoardStorage Storage::loadBoard() {
  YAML::Node boardNOde = YAML::LoadFile(boardFileName);
  use_case::BoardStorage boardStorage;
  boardStorage.rows = boardNOde[rowsPropertyName].as<common::Index>();
  boardStorage.cols = boardNOde[colsPropertyName].as<common::Index>();
  boardStorage.values = boardNOde[valuesPropertyName].as<common::Values>();
  return boardStorage;
}

void Storage::saveScore(const use_case::ScoreStorage& scoreStorage) {
  YAML::Node scoreNode;
  scoreNode[scorePropertyName] = scoreStorage.score;
  scoreNode[bestScorePropertyName] = scoreStorage.bestScore;
  std::ofstream ofs{scoreFileName};
  ofs << scoreNode;
}

void Storage::saveBoard(const use_case::BoardStorage& boardStorage) {
  YAML::Node boardNode;
  boardNode[rowsPropertyName] = boardStorage.rows;
  boardNode[colsPropertyName] = boardStorage.cols;
  boardNode[valuesPropertyName] = boardStorage.values;
  std::ofstream ofs{boardFileName};
  ofs << boardNode;
}

}  // namespace storage
