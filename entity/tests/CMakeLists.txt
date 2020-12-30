add_executable(entity_tests main.cpp BoardTests.cpp ScoreTests.cpp)
target_link_libraries(entity_tests PRIVATE doctest entity)

doctest_discover_tests(entity_tests)
