cmake_minimum_required(VERSION 3.2)
project(BitClient)

set(CMAKE_CXX_STANDARD 17)

include_directories(src
        lib)

set(SOURCE
        src/Torrent.cpp
        src/BEncoding.cpp
    )

add_executable(BitClient main.cpp ${SOURCE})

target_link_libraries(BitClient -static)