add_executable(use_case_tests GameTests.cpp)
target_link_libraries(use_case_tests PRIVATE doctest entity common)

doctest_discover_tests(use_case_tests)
