#include <gtest/gtest.h>
#include "Log.hpp"

int main(int argc, char **argv) {
    BitTorrent::Log::Init();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
