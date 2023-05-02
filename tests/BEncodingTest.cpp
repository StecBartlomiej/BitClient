#include <gtest/gtest.h>

#include "BEncoding.hpp"
#include "Log.hpp"

TEST(DecodingTest, Case1)
{
    std::filesystem::path path("test.txt");
    BitTorrent::Decoder decoder(path);

    std::vector<std::string> vec = decoder.Decode();

    std::vector<std::string> result = {
            "d", "s", "created by", "s", "qBittorrent v4.5.0", "s", "creation date", "i", "1681313718", "s",
            "info", "d", "s", "length", "i", "3", "s", "name", "s", "1.txt", "s", "piece length", "i", "16384",
            "s", "pieces", "s", "�y�E8uN�g�W/��*.�", "s", "private","i", "1", "e", "e"
    };
    EXPECT_EQ(vec, result);
}

TEST(DecodingTest, ReadingUTF8)
{
    std::filesystem::path path("test2.txt");
    BitTorrent::Decoder decoder(path);

    std::vector<std::string> vec = decoder.Decode();

    std::vector<std::string> result = { "s", "�y�E8uN�g�W/��*.�" };

    EXPECT_EQ(vec, result);
}

TEST(DecodingTest, ReadingEmpty)
{
    std::filesystem::path path("test1.txt");
    BitTorrent::Decoder decoder(path);

    std::vector<std::string> vec = decoder.Decode();

    std::vector<std::string> result = {};

    EXPECT_EQ(vec, result);
}

