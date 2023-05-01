#ifndef BITCLIENT_BENCODING_HPP
#define BITCLIENT_BENCODING_HPP

#include <filesystem>
#include <string>
#include <map>
#include <vector>
#include <fstream>

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

        friend std::ostream& operator<<(TextFile &file, std::vector<std::string> &vector);
    public:
        std::fstream file;
    };


    class Decoder
    {
    public:
        explicit Decoder(const std::filesystem::path &path): file_{path} {}

        // TODO - serializes to object
        std::vector<std::string> Decode();
    private:
        void DecodeInternal(std::vector<std::string> &vector);
    private:
        TextFile file_;
    };

    class Encoder
    {
    public:
        explicit Encoder(const std::filesystem::path &path): file_{path} {}

        // TODO - deserialize
//        void Encode()
    private:
        TextFile file_;
    };


}

#endif //BITCLIENT_BENCODING_HPP
