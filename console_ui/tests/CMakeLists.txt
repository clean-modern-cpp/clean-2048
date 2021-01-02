add_executable(console_ui_tests main.cpp BoardViewTests.cpp ScoreViewTests.cpp)
target_include_directories(console_ui_tests PRIVATE ../src)
target_link_libraries(console_ui_tests PRIVATE doctest console_ui presenter)

doctest_discover_tests(console_ui_tests)
