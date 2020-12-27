add_executable(board_tests BoardTests.cpp)
target_link_libraries(board_tests PRIVATE doctest entity)

doctest_discover_tests(board_tests)
