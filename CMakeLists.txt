cmake_minimum_required(VERSION 3.24)
project(BitClient)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

set(SOURCE
        src/Torrent.cpp
    )

add_executable(BitClient main.cpp ${SOURCE})