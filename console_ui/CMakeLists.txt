add_library(console_ui src/Application.cpp)
target_include_directories(console_ui PUBLIC include)
target_link_libraries(console_ui PRIVATE spdlog presenter)

add_subdirectory(tests)
