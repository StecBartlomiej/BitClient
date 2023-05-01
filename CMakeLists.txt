cmake_minimum_required(VERSION 3.16)
project(BitClient)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(
        src
        lib
)

set(SOURCE
        src/Torrent.cpp
        src/BEncoding.cpp
        src/Log.cpp
    )



include(lib/CMakeLists.txt)


add_executable(BitClient main.cpp ${SOURCE})
target_link_libraries(BitClient PRIVATE spdlog)