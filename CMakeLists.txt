cmake_minimum_required(VERSION 3.14)

project(clean-2048 LANGUAGES CXX)

enable_testing()

include(cmake/CPM.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cpmaddpackage(NAME doctest GITHUB_REPOSITORY onqtam/doctest GIT_TAG 2.4.1)
include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
cpmaddpackage(NAME spdlog GITHUB_REPOSITORY gabime/spdlog VERSION 1.8.0)
cpmaddpackage(NAME yaml-cpp GITHUB_REPOSITORY jbeder/yaml-cpp GIT_TAG
              yaml-cpp-0.6.3)

add_compile_options(-Wall -Werror -Wextra -pedantic)

add_subdirectory(common)
add_subdirectory(console_ui)
add_subdirectory(entity)
add_subdirectory(presenter)
add_subdirectory(qml_ui)
add_subdirectory(qt_view_model)
add_subdirectory(qwidget_ui)
add_subdirectory(storage)
add_subdirectory(use_case)
