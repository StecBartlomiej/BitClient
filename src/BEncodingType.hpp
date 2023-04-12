#ifndef BITCLIENT_BENCODINGTYPE_HPP
#define BITCLIENT_BENCODINGTYPE_HPP

#include <boost/variant.hpp>
#include <string>
#include <map>
#include <vector>
#include <sstream>

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
            oss << "{";

            typename std::vector<T>::const_iterator it = vec.begin();
            for (; it != vec.end(); ++it)
            {
                oss << Printer()(*it);
                if (std::next(it) != vec.end())
                    oss << ", ";
            }

            oss << "} ";
            return oss.str();
        }

        template<typename T>
        std::string operator()(const std::map<std::string, T> &map) const
        {
            std::ostringstream oss;
            oss << "[";

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

        std::string operator()(int64_t i) const { return std::to_string(i); }

        std::string operator()(const std::string &s) const { return s; }

        std::string operator()(boost::blank blank) const { return ""; }
    };
}

#endif //BITCLIENT_BENCODINGTYPE_HPP
