cmake_minimum_required(VERSION 3.16)
project(BitClient)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(
        src
        lib
)

set(SOURCE
        src/Torrent.cpp
        src/BEncoding.cpp
        src/BEncodingType.hpp
        src/Log.cpp
        src/parser/ConstexprTypes.hpp
    )

add_executable(BitClient main.cpp ${SOURCE})
target_precompile_headers(BitClient PRIVATE <iostream> <vector> <map> <string> <filesystem> <memory> <fstream>)

include(lib/CMakeLists.txt)
target_link_libraries(BitClient PRIVATE spdlog::spdlog)

include(tests/CMakeLists.txt)