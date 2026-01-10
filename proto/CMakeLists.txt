find_package(Protobuf REQUIRED)

set(PROTO_FILES payload.proto)

add_library(proto_messages ${PROTO_FILES})
target_link_libraries(proto_messages PUBLIC protobuf::libprotobuf)
target_include_directories(proto_messages PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

protobuf_generate(TARGET proto_messages LANGUAGE cpp)
