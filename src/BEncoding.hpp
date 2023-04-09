#ifndef BITCLIENT_BENCODING_HPP
#define BITCLIENT_BENCODING_HPP

#include <filesystem>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <any>
#include <boost/variant.hpp>

namespace BitTorrent
{
    using VarType = boost::make_recursive_variant<
            boost::blank,
            std::string,
            int64_t,
            std::vector<boost::recursive_variant_>,
            std::map<std::string, boost::recursive_variant_>
            >::type;

    bool isEmpty(const VarType &varType);

    class TextFile
    {
    public:
        TextFile(const std::filesystem::path &path);
        ~TextFile() { file_.close(); }

        char GetNextChar();
        char GetPreviousChar();
        bool Eof() const { return file_.eof(); }
        void Move(int offset) { file_.seekg(offset, std::ios::cur); }
    private:
        std::ifstream file_;
    };

    class Decoder
    {
    public:
        explicit Decoder(const std::filesystem::path &path): file_{path} {}

        VarType Decode();
    private:
        TextFile file_;
        static constexpr char dictionaryStart = 'd';
        static constexpr char listStart = 'l';
        static constexpr char integerStart = 'i';
        static constexpr char stringDivider = ':';
        static constexpr char typeEnd = 'e';
    };

    struct Printer : boost::static_visitor<std::string>
    {
        template<BOOST_VARIANT_ENUM_PARAMS(typename T)>
        std::string operator()(const boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> &var) const
        {
            return boost::apply_visitor(Printer(), var);
        }

        template<typename T>
        std::string operator()(const std::vector<T> &vec) const
        {
            std::ostringstream oss;
            oss << "{ ";

            typename std::vector<T>::const_iterator it = vec.begin();
            for (; it != vec.end(); ++it)
                oss << Printer()(*it);

            oss << "} ";
            return oss.str();
        }

        template<typename T>
        std::string operator()(const std::map<std::string, T> &map) const
        {
            std::ostringstream oss;
            oss << "[ ";

            typename std::map<std::string, T>::const_iterator it = map.begin();
            for (; it != map.end(); ++it)
            {
                oss << it->first << " => " << Printer()(it->second);
                if (std::next(it) != map.end())
                    oss << "\n";
            }

            oss << "] ";
            return oss.str();
        }

        std::string operator()(int64_t i) const { return " " + std::to_string(i); }

        std::string operator()(const std::string &s) const { return " " + s; }

        std::string operator()(boost::blank blank) const { return ""; }
    };
}

#endif //BITCLIENT_BENCODING_HPP
