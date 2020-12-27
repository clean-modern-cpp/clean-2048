add_library(console_ui src/Application.cpp src/BoardView.cpp)
target_include_directories(console_ui PUBLIC include)
target_link_libraries(console_ui PRIVATE presenter use_case common)

add_executable(console_2048 main.cpp)
target_link_libraries(console_2048 PRIVATE console_ui)

add_subdirectory(tests)
