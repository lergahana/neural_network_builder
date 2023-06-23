cmake_minimum_required(VERSION 3.16)

project(neural_network_builder VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

add_subdirectory(neural_network)
add_subdirectory(test_neural_network)
add_subdirectory(interface)
add_subdirectory(QuickQanava)
