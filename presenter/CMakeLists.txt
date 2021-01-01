add_library(presenter src/Controller.cpp src/BoardPresenter.cpp
                      src/GameOverPresenter.cpp src/ScorePresenter.cpp)
target_include_directories(presenter PUBLIC include)
target_link_libraries(
  presenter
  PUBLIC common
  PRIVATE use_case)
