#include "entity/Score.h"

#include <numeric>

namespace entity {

class Score::Impl {
 public:
  Impl(int score, int bestScore) : score{score}, bestScore{bestScore} {}

  int getScore() const { return score; }
  int getBestScore() const { return bestScore; }

  void update(const common::SwipeAction& action) {
    score += std::accumulate(action.mergeActions.cbegin(),
                             action.mergeActions.cend(), 0,
                             [](int sum, const auto& mergeAction) {
                               return sum + mergeAction.toValue;
                             });
    bestScore = std::max(bestScore, score);
  }

 private:
  int score = 0;
  int bestScore = 0;
};

Score::Score() : Score{0, 0} {}

Score::Score(int score, int bestScore)
    : impl{std::make_unique<Impl>(score, bestScore)} {}

Score::~Score() = default;

Score::Score(Score&&) = default;
Score& Score::operator=(Score&&) = default;

int Score::getScore() const { return impl->getScore(); }
int Score::getBestScore() const { return impl->getBestScore(); }

void Score::update(const common::SwipeAction& action) { impl->update(action); }

}  // namespace entity
