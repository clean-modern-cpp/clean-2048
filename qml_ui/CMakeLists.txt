find_package(
  Qt5
  COMPONENTS Core Quick Widgets
  REQUIRED)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(qml_2048 src/main.cpp src/qml.qrc)
target_link_libraries(qml_2048 PRIVATE Qt5::Core Qt5::Quick Qt5::Widgets
                                       qt_view_model)
