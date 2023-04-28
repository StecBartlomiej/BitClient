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

std::vector<std::string> BitTorrent::Split(const std::filesystem::path &path)
{
    TextFile file{path};

    std::vector<std::string> vector;

    BitTorrent::Parse(file, vector);

    for (auto x : vector)
        std::cout << x << std::endl;

    return vector;

}

void BitTorrent::Parse(TextFile &file, std::vector<std::string> &vector)
{
    char ch = file.GetNextChar();
    while (ch)
    {
        if (ch == 'i')
        {
            vector.emplace_back("i");
            std::ostringstream oss;
            for (char c = file.GetNextChar(); c != 'e'; c = file.GetNextChar())
                oss << c;
            vector.emplace_back(oss.str());
        }
        else if (ch == 'l')
        {
            vector.emplace_back("l");
            for (char c = file.GetNextChar(); c != 'e' && c != file.Eof(); c = file.GetNextChar())
            {
                file.Move(-1);
                Parse(file, vector);
            }
        }
        else if (ch == 'd')
        {
            vector.emplace_back("d");
            for (char c = file.GetNextChar(); c != 'e' && c != file.Eof(); c = file.GetNextChar())
            {
                file.Move(-1);
                Parse(file, vector);
            }
        }
        else if (std::isdigit(ch))
        {
            vector.emplace_back("s");
            std::ostringstream oss;
            for (char c = file.GetPreviousChar(); c != ':'; c = file.GetNextChar())
                oss << c;

            int length = std::stoi(oss.str());
            oss.str("");
            oss.clear();

            uint8_t byte;
            std::size_t count = 0;
            while (count <= length)
            {
                file.file.read(reinterpret_cast<char*>(&byte), sizeof(byte));
                if (!(byte & (1<<7)) || (byte & (1<<6))) // if not 0b10
                {
                    ++count;
                }
                if (count > length)
                {
                    file.Move(-1);
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
        ch = file.GetNextChar();
    }
}