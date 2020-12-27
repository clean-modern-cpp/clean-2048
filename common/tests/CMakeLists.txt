add_executable(common_tests ModelTests.cpp)
target_link_libraries(common_tests PRIVATE doctest common)

doctest_discover_tests(common_tests)
