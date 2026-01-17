cmake_minimum_required(VERSION 3.30)
project(zeromq-playground)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(cppzmq CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_subdirectory(proto)
add_subdirectory(utils)
add_subdirectory(patterns/request-reply)
add_subdirectory(patterns/publish-subscribe)
add_subdirectory(patterns/pipeline)
