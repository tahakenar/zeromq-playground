add_library(pub src/pub.cpp)
target_include_directories(pub PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(pub PUBLIC cppzmq utils proto_messages)

add_executable(pub_main src/pub_main.cpp)
target_link_libraries(pub_main PRIVATE pub)

add_library(sub src/sub.cpp)
target_include_directories(sub PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(sub PUBLIC cppzmq utils proto_messages)

add_executable(sub_main src/sub_main.cpp)
target_link_libraries(sub_main PRIVATE sub)
