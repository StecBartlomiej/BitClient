#ifndef BITCLIENT_BENCODING_HPP
#define BITCLIENT_BENCODING_HPP

#include <filesystem>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <variant>

namespace BitTorrent::BEncoding
{
    /// TODO - add option to write/read
    class TextFile
    {
    public:
        TextFile(const std::filesystem::path &path);
        ~TextFile();

        char getNextChar();
    private:
        std::ifstream file_;
    };

    struct Object
    {
        std::variant<std::string, int32_t, std::map<std::string, Object>, std::vector<Object>> data;
    };

    std::map<std::string, Object> Decode(std::filesystem::path &path);

    std::map<std::string, Object> DecodeDictionary(TextFile &file);
    int32_t DecodeInteger(TextFile &file);
    std::string DecodeString(TextFile &file, int length);
}

#endif //BITCLIENT_BENCODING_HPP
