#include "entity/Score.h"

#include <numeric>

namespace entity {

class Score::Impl {
 public:
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

Score::Score() : impl{std::make_unique<Impl>()} {}

Score::~Score() {}

int Score::getScore() const { return impl->getScore(); }
int Score::getBestScore() const { return impl->getBestScore(); }

void Score::update(const common::SwipeAction& action) { impl->update(action); }

}  // namespace entity
