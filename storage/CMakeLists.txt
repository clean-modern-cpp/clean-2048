add_library(storage src/Storage.cpp)
target_include_directories(storage PUBLIC include)
target_link_libraries(
  storage
  PUBLIC use_case_interface
  PRIVATE yaml-cpp)

add_subdirectory(tests)
