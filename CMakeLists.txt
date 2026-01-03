cmake_minimum_required(VERSION 3.30)
project(zeromq-playground)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CXX_STANDARD_REQUIRED 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(cppzmq)

add_subdirectory(patterns/request-reply)

add_executable(main src/main.cpp)

target_link_libraries(main cppzmq)