cmake_minimum_required(VERSION 3.20)
project(grpc_calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/generated
)

add_executable(server
    src/server/server.cpp
    generated/calculator.pb.cc
    generated/calculator.grpc.pb.cc
)

add_executable(client
    src/client/client.cpp
    generated/calculator.pb.cc
    generated/calculator.grpc.pb.cc
)

target_link_libraries(server
    gRPC::grpc++
    protobuf::libprotobuf
)

target_link_libraries(client
    gRPC::grpc++
    protobuf::libprotobuf
)
