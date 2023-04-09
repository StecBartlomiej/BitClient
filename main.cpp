#include <iostream>
#include "BEncoding.hpp"

int main()
{
    std::filesystem::path path("test.txt");
    BitTorrent::Decoder decoder(path);
    BitTorrent::VarType map = decoder.Decode();
    std::cout << BitTorrent::Printer()(map) << std::endl;
    return 0;
}

