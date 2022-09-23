cmake_minimum_required(VERSION 3.10)
project(fileopt-client)

add_executable(${PROJECT_NAME}
    src/client.cpp
    src/client.hpp
)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt-header-only)