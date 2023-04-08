#include "BEncoding.hpp"

using namespace BitTorrent::BEncoding;

namespace
{
    char dictionaryStart = 'd';
    char listStart = 'l';
    char integerStart = 'i';
    char stringDivider = ':';
    char typeEnd = 'e';
}

TextFile::TextFile(const std::filesystem::path &path): file_{path.string()}
{
    /// TODO - improve error logging
    if (!file_.is_open())
        printf("Error: cannot open file from path: %s", path.string().c_str());
}

TextFile::~TextFile()
{
    file_.close();
}

char TextFile::getNextChar()
{
    char ch;
    file_.get(ch);
    return ch;
}

std::map<std::string, Object> BitTorrent::BEncoding::Decode(std::filesystem::path &path)
{
    TextFile file(path);
    std::map<std::string, Object> dictionary;
    char ch;
}

int32_t BitTorrent::BEncoding::DecodeInteger(TextFile &file)
{
    std::ostringstream oss;
    for (char ch = file.getNextChar(); ch != typeEnd; ch = file.getNextChar())
        oss << ch;
    int32_t num = std::stoi(oss.str());
    return num;
}

std::string BitTorrent::BEncoding::DecodeString(TextFile &file, int length)
{
    std::ostringstream oss;
    for (int i = 0; i < length; ++i)
    {
        oss << file.getNextChar();
    }
    return oss.str();
}

std::map<std::string, Object> BitTorrent::BEncoding::DecodeDictionary(TextFile &file)
{
    std::map<std::string, Object> dictionary;
    char ch = file.getNextChar();
    while (ch != typeEnd)
    {
        std::string key;
        if (isdigit(ch))
        {
            std::ostringstream oss;
            oss << ch;
            for (char c = file.getNextChar(); c != stringDivider; c = file.getNextChar())
            {
                oss << c;
            }
            key = DecodeString(file, std::stoi(oss.str()));
        }

        Object value;
        if (ch == integerStart)
            value.data = DecodeInteger(file);
//        else if (isdigit(ch))
//            value.data = DecodeString(file)
    }
}