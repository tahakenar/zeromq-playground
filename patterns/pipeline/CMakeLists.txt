add_library(ventilator src/ventilator.cpp)
target_include_directories(ventilator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(ventilator PUBLIC cppzmq utils proto_messages)

add_executable(ventilator_main src/ventilator_main.cpp)
target_link_libraries(ventilator_main PRIVATE ventilator)

add_library(worker src/worker.cpp)
target_include_directories(worker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(worker PUBLIC cppzmq utils proto_messages)

add_executable(worker_main src/worker_main.cpp)
target_link_libraries(worker_main PRIVATE worker)

add_library(sink src/sink.cpp)
target_include_directories(sink PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(sink PUBLIC cppzmq utils proto_messages)

add_executable(sink_main src/sink_main.cpp)
target_link_libraries(sink_main PRIVATE sink)
