add_executable(console_2048 src/main.cpp)
target_link_libraries(console_2048 PRIVATE console_ui use_case storage)
