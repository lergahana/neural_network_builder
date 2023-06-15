cmake_minimum_required(VERSION 3.16)

project(zadnji VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(neural_network)
add_subdirectory(test_neural_network)
add_subdirectory(nn_moj)
add_subdirectory(test_nn)
add_subdirectory(gui)
add_subdirectory(QuickQanava)
