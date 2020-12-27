add_executable(use_case_tests main.cpp GameTests.cpp RandomTests.cpp)
target_include_directories(use_case_tests PRIVATE ../src)
target_link_libraries(use_case_tests PRIVATE doctest use_case)

doctest_discover_tests(use_case_tests)
