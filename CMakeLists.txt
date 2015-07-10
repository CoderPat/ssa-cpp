cmake_minimum_required(VERSION 2.8.4)
project(ssa)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Og -fsanitize=address")

include_directories(
    include
)

set(INCLUDE_FILES
    include/basic_line.hpp
    include/dialogue_line.hpp
    include/script.hpp
    include/srt_time.hpp
    include/subtitle.hpp
    include/subtitle_line.hpp
    include/utils.hpp
)

set(SOURCE_FILES
    src/basic_line.cpp
    src/dialogue_line.cpp
    src/main.cpp
    src/script.cpp
    src/srt_time.cpp
    src/subtitle.cpp
    src/subtitle_line.cpp
    src/utils.cpp
)

add_executable(ssa ${INCLUDE_FILES} ${SOURCE_FILES})
