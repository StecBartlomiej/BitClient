#include "BEncoding.hpp"
#include <boost/regex.hpp>
#include <bitset>

int main()
{
    std::filesystem::path path("test.txt");

    BitTorrent::Decoder decoder(path);

    auto vec = decoder.Decode();

    return 0;
}

