find_package(
  Qt5
  COMPONENTS Core Quick Widgets
  REQUIRED)

set(CMAKE_AUTORCC ON)

add_executable(qml_2048 src/main.cpp src/qml.qrc)
target_link_libraries(
  qml_2048
  PRIVATE Qt5::Core
          Qt5::Quick
          Qt5::Widgets
          qt_view_model
          presenter
          router
          storage
          use_case)

add_executable(qml_simulator src/main_simulator.cpp src/qml.qrc)
target_link_libraries(
  qml_simulator PRIVATE Qt5::Core Qt5::Quick Qt5::Widgets qt_view_model
                        presenter use_case_interface)
