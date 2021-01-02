add_library(use_case src/Game.cpp)
target_include_directories(use_case PUBLIC include)
target_link_libraries(
  use_case
  PUBLIC common
  PRIVATE entity)

add_subdirectory(tests)
