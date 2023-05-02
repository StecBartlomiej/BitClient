#ifndef BITCLIENT_BENCODING_HPP
#define BITCLIENT_BENCODING_HPP

#include "BEncodingType.hpp"
#include "Log.hpp"

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

        template<typename T>
        constexpr auto Decode() -> DataDictionary<T>;
    private:
        template<typename T>
        void DecodeInternal(DataDictionary<T> dataDictionary);

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


    template<typename T>
    constexpr auto Decoder::Decode() -> DataDictionary<T>
    {
        DataDictionary<T> dataDictionary;
        DecodeInternal(dataDictionary);
        return dataDictionary;
    }

    template<typename T>
    void Decoder::DecodeInternal(DataDictionary<T> dataDictionary)
    {
        char ch = file_.GetNextChar();
        while (ch)
        {
            if (ch == 'i')
            {
                std::ostringstream oss;
                for (char c = file_.GetNextChar(); c != 'e'; c = file_.GetNextChar())
                    oss << c;

            }
            else if (ch == 'l')
            {
                vector.emplace_back("l");
                for (char c = file_.GetNextChar(); c != 'e' && c != file_.Eof(); c = file_.GetNextChar())
                {
                    file_.Move(-1);
                    DecodeInternal(vector);
                }
            }
            else if (ch == 'd')
            {
                vector.emplace_back("d");
                for (char c = file_.GetNextChar(); c != 'e' && c != file_.Eof(); c = file_.GetNextChar())
                {
                    file_.Move(-1);
                    DecodeInternal(vector);
                }
            }
            else if (std::isdigit(ch))
            {
                vector.emplace_back("s");
                std::ostringstream oss;
                for (char c = ch; c != ':'; c = file_.GetNextChar())
                    oss << c;

                int length = std::stoi(oss.str());
                oss.str("");
                oss.clear();

                uint8_t byte;
                std::size_t count = 0;
                while (count <= length)
                {
                    file_.file.read(reinterpret_cast<char*>(&byte), sizeof(byte));
                    if (!(byte & (1<<7)) || (byte & (1<<6))) // if not 0b10
                    {
                        ++count;
                    }
                    if (count > length)
                    {
                        file_.Move(-1);
                        break;
                    }
                    oss << byte;
                }
                vector.emplace_back(oss.str());
            }
            else if (ch == 'e')
            {
                vector.emplace_back("e");
                return;
            }
            else
            {
                LOG_ERROR("Decode: bad type in BEncoding");
                return;
            }
            ch = file_.GetNextChar();
        }
    }
}

#endif //BITCLIENT_BENCODING_HPP
