cmake_minimum_required(VERSION 3.23)
project(Stackulator)

add_executable(postfixc)
target_sources(
    postfixc
    PRIVATE
    src/main.cpp
)

add_library(stack)
target_sources(
    stack
    PRIVATE
        src/stack.cpp
    PUBLIC
    FILE_SET libstack
    TYPE HEADERS
    BASE_DIRS
        include
    FILES
        include/stack.h
)
target_include_directories(stack
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(
    postfixc
    PRIVATE
    stack
)
