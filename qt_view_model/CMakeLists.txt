find_package(
  Qt5
  COMPONENTS Core Widgets
  REQUIRED)

set(CMAKE_AUTOMOC ON)

add_library(
  qt_view_model
  include/qt_view_model/BoardViewModel.h
  include/qt_view_model/GameOverViewModel.h
  include/qt_view_model/ScoreViewModel.h
  src/BoardViewModel.cpp
  src/GameOverViewModel.cpp
  src/ScoreViewModel.cpp)
target_include_directories(qt_view_model PUBLIC include)
target_link_libraries(qt_view_model PUBLIC Qt5::Core Qt5::Widgets spdlog common
                                           presenter)
