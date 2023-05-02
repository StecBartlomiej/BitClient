#ifndef BITCLIENT_BENCODINGTYPE_HPP
#define BITCLIENT_BENCODINGTYPE_HPP

#include <type_traits>
#include <map>
#include <vector>
#include <string>

namespace BitTorrent
{
    enum class DataType { INT, STRING, VECTOR};

    template<typename T>
    struct TrivialDataType
    {
        static_assert(std::is_integral<T>::value || std::is_same<std::string, T>::value, "Must be int or string");
        constexpr explicit TrivialDataType(T data);

        const T data;
        const DataType dataType;
    };

    template<typename T>
    struct DataList
    {
        std::vector<T> list;
        constexpr static DataType dataType = DataType::VECTOR;
    };

    template<typename T>
    struct DataDictionary
    {
        static_assert(std::is_same<TrivialDataType<T>, T>::value || std::is_same<DataList<T>, T>::value);
        std::map<std::string, T> map;
    };

    // ======================
    // Definitions
    // ======================
    template<typename T>
    TrivialDataType(T) -> TrivialDataType<T>;

    template<typename T>
    DataDictionary(T) -> DataDictionary<T>;

    template<typename T>
    constexpr TrivialDataType<T>::TrivialDataType(T data): dataType{std::is_integral<T>::value ? DataType::INT: DataType::STRING}
    {
        switch (dataType)
        {
            case DataType::INT:
                this->data = data;
                break;
            case DataType::STRING:
                this->data = std::move(data);
                break;
        }
    }
}

#endif //BITCLIENT_BENCODINGTYPE_HPP
