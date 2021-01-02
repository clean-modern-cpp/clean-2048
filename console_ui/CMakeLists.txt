add_library(console_ui src/Application.cpp)
target_include_directories(console_ui PUBLIC include)
target_link_libraries(console_ui PRIVATE spdlog presenter)

add_executable(console_2048 main.cpp)
target_link_libraries(console_2048 PRIVATE console_ui use_case storage)

add_subdirectory(tests)
