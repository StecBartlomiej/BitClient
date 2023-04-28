#ifndef BITCLIENT_BENCODING_HPP
#define BITCLIENT_BENCODING_HPP

#include "BEncodingType.hpp"

#include <filesystem>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <boost/variant.hpp>

namespace BitTorrent
{

    class TextFile
    {
    public:
        TextFile(const std::filesystem::path &path);
        ~TextFile() { file.close(); }

        char GetNextChar();
        char GetPreviousChar();
        bool Eof() const { return file.eof(); }
        void Move(int offset) { file.seekg(offset, std::ios::cur); }

    public:
        std::ifstream file;
    };

    std::vector<std::string> Split(const std::filesystem::path &path);
    void Parse(TextFile &file, std::vector<std::string> &vector);

    class Decoder
    {
    public:
        explicit Decoder(const std::filesystem::path &path): textFile_{path} {}

        VarType Decode();
    private:
        TextFile textFile_;
        static constexpr char dictionaryStart = 'd';
        static constexpr char listStart = 'l';
        static constexpr char integerStart = 'i';
        static constexpr char stringDivider = ':';
        static constexpr char typeEnd = 'e';
    };
}

#endif //BITCLIENT_BENCODING_HPP
