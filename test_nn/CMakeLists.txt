cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(test01
    test01.cpp
)

target_link_libraries(test01 PUBLIC
    nn_moj
)

target_include_directories(test01 PUBLIC
    ${PROJECT_SOURCE_DIR}/nn_moj/
)
