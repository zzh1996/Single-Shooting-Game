cmake_minimum_required(VERSION 3.5)
project(STG)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCE_FILES
        "*.h"
        "*.cpp"
        )

add_executable(STG ${SOURCE_FILES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

target_link_libraries(STG "-lfltk -lfltk_images")

#set(CMAKE_VERBOSE_MAKEFILE on)