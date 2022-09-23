cmake_minimum_required(VERSION 3.10)
project(fileopt-server)

add_executable(${PROJECT_NAME}
    src/server.cpp
    src/server.hpp
)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt-header-only)