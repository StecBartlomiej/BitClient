#include "BEncoding.hpp"
#include "Log.hpp"

int main()
{
    BitTorrent::Log::Init();
    std::filesystem::path path("test.txt");

    BitTorrent::Decoder decoder(path);
    auto vec = decoder.Decode();

    return 0;
}

