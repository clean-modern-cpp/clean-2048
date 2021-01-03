add_library(use_case src/Facade.cpp)
target_include_directories(use_case PUBLIC include)
target_link_libraries(
  use_case
  PUBLIC common use_case_interface
  PRIVATE entity)

add_subdirectory(tests)
