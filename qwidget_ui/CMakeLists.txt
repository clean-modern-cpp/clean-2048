find_package(
  Qt5
  COMPONENTS Core Widgets
  REQUIRED)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

add_executable(qwidget_2048 src/main.cpp src/MainWindow.cpp src/BoardView.cpp
                            src/CellView.cpp src/CellView.ui src/MainWindow.ui)
target_include_directories(qwidget_2048 PRIVATE src)
target_link_libraries(qwidget_2048 PRIVATE Qt5::Core Qt5::Widgets spdlog
                                           qt_view_model)
