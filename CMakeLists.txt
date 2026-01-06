cmake_minimum_required(VERSION 3.30)
project(zeromq-playground)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(cppzmq CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_library(zeromq_logger INTERFACE)
target_include_directories(zeromq_logger INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
)
target_link_libraries(zeromq_logger INTERFACE
    spdlog::spdlog
)

add_subdirectory(patterns/request-reply)

add_executable(main src/main.cpp)
target_link_libraries(main cppzmq)
