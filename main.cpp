#include <iostream>
#include "BEncoding.hpp"

int main()
{
    std::filesystem::path path("test.txt");
    BitTorrent::BEncoding file(path);
    auto map = file.Decode();
    return 0;
}

