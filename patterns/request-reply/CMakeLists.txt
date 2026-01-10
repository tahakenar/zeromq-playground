add_library(req src/req.cpp)
target_include_directories(req PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(req PUBLIC cppzmq utils proto_messages)

add_executable(req_main src/req_main.cpp)
target_link_libraries(req_main PRIVATE req)

add_library(rep src/rep.cpp)
target_include_directories(rep PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(rep PUBLIC cppzmq utils proto_messages)

add_executable(rep_main src/rep_main.cpp)
target_link_libraries(rep_main PRIVATE rep)
