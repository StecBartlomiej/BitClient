#include "BEncoding.hpp"
#include <iostream>
#include "BEncoding.hpp"

using namespace BitTorrent;


TextFile::TextFile(const std::filesystem::path &path): file{path.string()}
{
    /// TODO - improve error logging
    if (!file.is_open())
        printf("Error: cannot open file from path: %s", path.string().c_str());
}

char TextFile::GetNextChar()
{
    char ch;
    file.get(ch);
    return ch;
}

char TextFile::GetPreviousChar()
{
    Move(-1);
    return GetNextChar();
}

std::ostream &operator<<(TextFile &file, std::vector<std::string> &vector)
{
    for (std::string_view x : vector)
    {
        file.file << x;
    }
    return file.file;
}


std::vector<std::string> Decoder::Decode()
{
    std::vector<std::string> vector;

    DecodeInternal(vector);

    for (std::string_view x: vector)
        std::cout << x << std::endl;

    return vector;
}

void Decoder::DecodeInternal(std::vector<std::string> &vector)
{
    char ch = file_.GetNextChar();
    while (ch)
    {
        if (ch == 'i')
        {
            vector.emplace_back(std::to_string('i'));
            std::ostringstream oss;
            for (char c = file_.GetNextChar(); c != 'e'; c = file_.GetNextChar())
                oss << c;
            vector.emplace_back(oss.str());
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
            for (char c = file_.GetPreviousChar(); c != ':'; c = file_.GetNextChar())
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
            std::cerr << "Error: BitTorrent::Parser bad type" << std::endl;
        ch = file_.GetNextChar();
    }
}
