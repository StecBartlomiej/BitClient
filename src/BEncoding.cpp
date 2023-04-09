#include <iostream>
#include "BEncoding.hpp"

using namespace BitTorrent;


TextFile::TextFile(const std::filesystem::path &path): file_{path.string()}
{
    /// TODO - improve error logging
    if (!file_.is_open())
        printf("Error: cannot open file from path: %s", path.string().c_str());
}

char TextFile::GetNextChar()
{
    char ch;
    file_.get(ch);
    return ch;
}

char TextFile::GetPreviousChar()
{
    Move(-2);
    return GetNextChar();
}

bool BitTorrent::isEmpty(const VarType &varType)
{
    return varType.which() == 0;
}

// TODO - fix bug
VarType Decoder::Decode()
{
    char ch = file_.GetNextChar();
    if (ch == integerStart)
    {
        std::ostringstream oss;
        for (char c = file_.GetNextChar(); c != typeEnd; c = file_.GetNextChar())
            oss << c;
        std::string s = oss.str();
        return std::stoi(s);
    }
    else if (ch == listStart)
    {
        std::vector<VarType> vec;
        for (char c = file_.GetNextChar(); c != typeEnd; c = file_.GetNextChar())
        {
            file_.Move(-2);
            vec.push_back(Decode());
        }
        return vec;
    }
    else if (ch == dictionaryStart)
    {
        std::map<std::string, VarType> map;
        for (char c = file_.GetNextChar(); std::to_string(c) != std::to_string(typeEnd); c = file_.GetNextChar())
        {
            file_.Move(-2);
            VarType key = Decode();
            VarType value = Decode();
            try
            {
                map[boost::get<std::string>(key)] = value;
            }
            catch (boost::bad_get &err)
            {
                std::cerr << "ERRor" << std::endl;
                break;
            }
        }
        return map;
    }
    else if (std::isdigit(ch))
    {
        std::ostringstream oss;
        for (char c = file_.GetPreviousChar(); c != stringDivider; c = file_.GetNextChar())
            oss << c;

        int length = std::stoi(oss.str());
        oss.str("");
        oss.clear();
        for (int i = 0; i < length; ++i)
            oss << file_.GetNextChar();
        return oss.str();
    }
    else
        return typeEnd;
}
