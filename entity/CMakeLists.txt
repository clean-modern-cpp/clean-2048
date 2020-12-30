add_library(entity src/Board.cpp src/Score.cpp)
target_include_directories(entity PUBLIC include)
target_link_libraries(entity PUBLIC common)

add_subdirectory(tests)
