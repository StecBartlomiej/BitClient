#ifndef BITCLIENT_BENCODING_HPP
#define BITCLIENT_BENCODING_HPP

#include <filesystem>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <variant>
#include <any>

namespace BitTorrent
{
    /// TODO - add option to write/read
    class TextFile
    {
    public:
        TextFile(const std::filesystem::path &path);
        ~TextFile() { file_.close(); }

        char getNextChar();
        char getPreviousChar();
        bool eof() const { return file_.eof(); }
    private:
        std::ifstream file_;
    };

    class BEncoding
    {
    public:
        BEncoding(const std::filesystem::path &path): file_{path} {}

        std::map<std::string, std::any> Decode();

    private:
        std::any getNextObject();
        std::map<std::string, std::any> DecodeDictionary();
        std::vector<std::any> DecodeList();
        int32_t DecodeInteger();
        std::string DecodeString();
    private:
        TextFile file_;
        static constexpr char dictionaryStart = 'd';
        static constexpr char listStart = 'l';
        static constexpr char integerStart = 'i';
        static constexpr char stringDivider = ':';
        static constexpr char typeEnd = 'e';
    };

    struct Object
    {
        std::variant<std::string, int32_t, std::map<std::string, Object>, std::vector<Object>> data;
    };


    std::map<std::string, Object> DecodeFile(std::filesystem::path &path);

    std::string DecodeString(TextFile &file);

    int32_t DecodeInteger(TextFile &file);

    std::map<std::string, Object> DecodeDictionary(TextFile &file);

    std::vector<Object> DecodeList(TextFile &file);
}

#endif //BITCLIENT_BENCODING_HPP
