add_executable(storage_tests StorageTests.cpp)
target_link_libraries(storage_tests PRIVATE doctest storage use_case)

doctest_discover_tests(storage_tests)
