add_library(presenter src/BoardPresenter.cpp src/Controller.cpp)
target_include_directories(presenter PUBLIC include)
target_link_libraries(presenter PRIVATE use_case common)
