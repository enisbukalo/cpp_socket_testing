cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(SOURCES src/main.cpp)

project(Socket_Testing)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(app ${SOURCES})