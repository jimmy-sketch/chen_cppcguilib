cmake_minimum_required(VERSION 3.12)

project(sandbox
    LANGUAGES CXX
    VERSION 1.0.0
)

set(CMAKE_CXX_STANDARD 20)

add_executable(sandbox
    demo.cpp
)

target_include_directories(sandbox PUBLIC
    ../include/
)

target_link_libraries(sandbox PUBLIC
    CGUI
)