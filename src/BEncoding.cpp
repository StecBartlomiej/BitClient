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

bool BitTorrent::isEmpty(const VarType &varType)
{
    return varType.which() == 0;
}

VarType Decoder::Decode()
{
    char ch = textFile_.GetNextChar();
    if (ch == integerStart)
    {
        std::ostringstream oss;
        for (char c = textFile_.GetNextChar(); c != typeEnd; c = textFile_.GetNextChar())
            oss << c;
        std::string s = oss.str();
        if (s == "vat")
            std::cout << "Co jest\n";
        int a = std::stoi(s);

        return a;
    }
    else if (ch == listStart)
    {
        std::vector<VarType> vec;
        for (char c = textFile_.GetNextChar(); c != typeEnd; c = textFile_.GetNextChar())
        {
            textFile_.Move(-1);
            vec.push_back(Decode());
        }
        return vec;
    }
    else if (ch == dictionaryStart)
    {
        std::map<std::string, VarType> map;
        for (char c = textFile_.GetNextChar(); c != typeEnd; c = textFile_.GetNextChar())
        {
            textFile_.Move(-1);
            VarType key = Decode();
            VarType value = Decode();
            try
            {
                map[boost::get<std::string>(key)] = value;
            }
            catch (boost::bad_get &err)
            {
                std::cerr << "Error " << std::endl;
                break;
            }
        }
        return map;
    }
    else if (std::isdigit(ch))
    {
        std::ostringstream oss;
        for (char c = textFile_.GetPreviousChar(); c != stringDivider; c = textFile_.GetNextChar())
            oss << c;

        int length = std::stoi(oss.str());
        oss.str("");
        oss.clear();
        uint8_t byte;
        std::size_t count = 0;
        while (count <= length)
        {
            textFile_.file.read(reinterpret_cast<char*>(&byte), sizeof(byte));
            if (!(byte & (1<<7)) || (byte & (1<<6))) // if not 0b10
            {
                ++count;
            }
            if (count > length)
            {
                textFile_.Move(-1);
                break;
            }
            oss << byte;
        }
        std::string s = oss.str();
        return s;
    }
    else
        return typeEnd;
}
