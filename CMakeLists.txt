cmake_minimum_required(VERSION 3.30)
project(opcua_client C)

set(CMAKE_C_STANDARD 23)

add_executable(opcua_client src/main.c
        src/opcua_client.c
        src/opcua_client.h
        src/socket_server.c
        src/socket_server.h)
target_link_libraries(${PROJECT_NAME} open62541)
