#include <iostream>
#include "BEncoding.hpp"

using namespace BitTorrent;

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

char TextFile::getNextChar()
{
    char ch;
    file_.get(ch);
    return ch;
}

char TextFile::getPreviousChar()
{
    file_.seekg(-2, std::ios::cur);
    return getNextChar();
}

std::map<std::string, std::any> BEncoding::Decode()
{
    return DecodeDictionary();
}

std::any BEncoding::getNextObject()
{
    std::any object;
    char ch = file_.getNextChar();
    if (ch == dictionaryStart)
        object = DecodeDictionary();
    else if (ch == integerStart)
        object = DecodeInteger();
    else if (ch == listStart)
        ;
    else if (isdigit(ch))
        object = DecodeString();
    else
        object.reset();
    return object;
}

int32_t BEncoding::DecodeInteger()
{
    std::ostringstream oss;
    for (char ch = file_.getNextChar(); ch != typeEnd; ch = file_.getNextChar())
        oss << ch;
    std::cout << oss.str() << std::endl;
    int32_t num = std::stoi(oss.str());
    return num;
}

std::string BEncoding::DecodeString()
{
    std::ostringstream oss;
    char c = file_.getPreviousChar();
    for (c; c != stringDivider; c = file_.getNextChar())
    {
        oss << c;
    }
    std::string s = oss.str();
    std::cout << s << std::endl;
    int length = std::stoi(oss.str());

    oss.clear();
    for (int i = 0; i < length; ++i)
    {
        oss << file_.getNextChar();
    }
    std::cout << oss.str() << std::endl;
    return oss.str();
}

std::map<std::string, std::any> BEncoding::DecodeDictionary()
{
    std::map<std::string, std::any> dictionary;
    for (std::any key = getNextObject(), value = getNextObject(); key.has_value() && value.has_value();
            key = getNextObject(), value = getNextObject())
    {
        dictionary[std::any_cast<std::string>(key)] = value;
    }
    return dictionary;
}

std::vector<std::any> BEncoding::DecodeList()
{
    std::vector<std::any> vec;
    for (std::any object = getNextObject(); object.has_value(); object = getNextObject())
            vec.push_back(object);
    return vec;
}


