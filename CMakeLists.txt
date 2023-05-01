cmake_minimum_required(VERSION 3.16)
project(BitClient)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(
        src
        lib
)

set(SOURCE
        main.cpp
        src/Torrent.cpp
        src/BEncoding.cpp
        src/Log.cpp
    )

add_executable(BitClient ${SOURCE})
target_precompile_headers(BitClient PRIVATE <iostream> <vector> <map> <string> <filesystem> <memory> <fstream>)

include(lib/CMakeLists.txt)
target_link_libraries(BitClient PRIVATE spdlog::spdlog)