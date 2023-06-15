cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(test
    test.cpp
)

target_link_libraries(test PUBLIC
    neural_network
)

target_include_directories(test PUBLIC
    ${PROJECT_SOURCE_DIR}/neural_network/
)
