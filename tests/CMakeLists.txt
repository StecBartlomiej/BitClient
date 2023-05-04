include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(TEST_SOURCE
        tests/main.cpp
        tests/BEncodingTest.cpp
        tests/ConstexprTypesTest.cpp
        )


set(TEST_TXT_FILES
        tests/test.txt
        tests/test1.txt
        tests/test2.txt
        )

file(COPY ${TEST_TXT_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(BitTorrent_tests ${SOURCE} ${TEST_SOURCE})


target_link_libraries(
        BitTorrent_tests
        GTest::gtest_main
        spdlog::spdlog
)

include(GoogleTest)
gtest_discover_tests(BitTorrent_tests)