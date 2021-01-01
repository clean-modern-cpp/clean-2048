add_library(storage src/Storage.cpp)
target_include_directories(storage PUBLIC include)
target_link_libraries(storage PRIVATE yaml-cpp use_case)

add_subdirectory(tests)
