add_library(presenter src/BoardPresenter.cpp src/Controller.cpp
                      src/ScorePresenter.cpp)
target_include_directories(presenter PUBLIC include)
target_link_libraries(
  presenter
  PUBLIC common
  PRIVATE use_case)
