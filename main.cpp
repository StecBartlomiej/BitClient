#include <iostream>
#include "BEncoding.hpp"
#include <boost/regex.hpp>
#include <bitset>

int main()
{
    std::filesystem::path path("test.txt");

    BitTorrent::Decoder decoder(path);
    BitTorrent::VarType map = decoder.Decode();
    std::cout << BitTorrent::Printer()(map) << std::endl;

//    std::ifstream file(path);
//    std::size_t count = 1;
//    std::uint8_t byte;
//    while (count <= 20)
//    {
//        file.read(reinterpret_cast<char*>(&byte), sizeof(byte));
//        if (!(byte & (1<<7)) || (byte & (1<<6))) // if not 0b10
//        {
//            std::cerr << byte << "  " << count << std::endl;
//            ++count;
//        }
//    }
//    std::cout << "Count: " << std::dec << count << std::endl;
    return 0;
}

