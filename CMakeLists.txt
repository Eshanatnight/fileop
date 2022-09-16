cmake_minimum_required(VERSION 3.10)
project(fileopt)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(Client
    src/client.cpp
    src/client.hpp)

add_executable(Server
    src/server.cpp
    src/server.hpp
)

find_package(fmt REQUIRED)
target_link_libraries(Client fmt::fmt)
target_link_libraries(Server fmt::fmt)