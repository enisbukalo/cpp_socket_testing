cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(HEADERS
    headers/SocketServer.h
    headers/MessageQueue.h
    headers/ErrorHandler.h)
set(SOURCES
    src/main.cpp
    src/SocketServer.cpp
    src/MessageQueue.cpp
    src/ErrorHandler.cpp)

project(Server)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(app ${SOURCES} ${HEADERS})

target_include_directories(app PUBLIC headers)