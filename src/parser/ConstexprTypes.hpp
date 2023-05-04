#ifndef BITCLIENT_CONSTEXPRTYPES_HPP
#define BITCLIENT_CONSTEXPRTYPES_HPP

/**
 * BEncoding has 4 recusive types:
 * 1. int
 * 2. string
 * 3. vector
 * 4. map
 */

#include <cinttypes>
#include <vector>


template<class InputIt, class UnaryPredicate>
constexpr InputIt find_if(InputIt first, InputIt last, UnaryPredicate p)
{
    for (; first != last; ++first)
    {
        if (p(*first))
            return first;
    }
    return last;
}


class static_string
{
public:
    template<std::size_t N>
    constexpr explicit static_string(const char (&str)[N]): m_size{N}, m_data{str} {}

    constexpr static_string() = default;

    constexpr std::size_t size() const { return m_size; }

    constexpr const char *c_str() const { return m_data; }

private:
    std::size_t m_size{0};
    const char *m_data = nullptr;
};


template<typename Value, std::size_t Size = 5>
class static_vector
{
public:
    using storage_t = std::array<Value, Size>;
    using iterator = storage_t::iterator;
    using const_iterator = storage_t::const_iterator;

    /// TODO - complete

    [[nodiscard]] constexpr std::size_t size() const { return m_size; }

    [[nodiscard]] constexpr bool empty() const { return m_size == 0; }

    constexpr void push_back(Value value)
    {
        if (m_size >= Size)
            throw std::runtime_error("Vector is full");
        else
            m_data[m_size++] = std::move(value);
    }

    constexpr Value operator[](std::size_t i) const
    {
        if (i >= m_size)
            throw std::runtime_error("Index past size of vector");
        else
            return m_data[i];
    };

    [[nodiscard]] constexpr const_iterator begin() const { return m_data.begin(); }
    [[nodiscard]] constexpr const_iterator cbegin() const { return m_data.cbegin(); }
    [[nodiscard]] constexpr const_iterator rbegin() const { return m_data.rbegin(); }

    [[nodiscard]] constexpr const_iterator end() const { return m_data.begin() + m_size; }
    [[nodiscard]] constexpr const_iterator cend() const { return m_data.cbegin() + m_size; }
    [[nodiscard]] constexpr const_iterator rend() const { return m_data.rbegin() + m_size; }

private:
    storage_t m_data{};
    std::size_t m_size{0};
};

template<typename Key, typename Value, std::size_t Size = 5>
class static_map
{
public:
    using storage_t = std::array<std::pair<Key, Value>, Size>;
    using iterator = storage_t::iterator;
    using const_iterator = storage_t::const_iterator;

    constexpr void insert(Key key, Value value)
    {
        if (m_size >= Size)
            throw std::runtime_error("Index past end of map");
        else
        {
            m_data[m_size++] = std::make_pair(key, value);
        }
    }

    constexpr std::size_t size() const { return m_size; }

    [[nodiscard]] constexpr const_iterator begin() const { return m_data.begin(); }
    [[nodiscard]] constexpr const_iterator cbegin() const { return m_data.cbegin(); }
    [[nodiscard]] constexpr const_iterator rbegin() const { return m_data.rbegin(); }

    [[nodiscard]] constexpr const_iterator  end() const { return m_data.begin() + m_size; }
    [[nodiscard]] constexpr const_iterator cend() const { return m_data.cbegin() + m_size; }
    [[nodiscard]] constexpr const_iterator rend() const { return m_data.rbegin() + m_size; }

private:
    storage_t m_data{};
    std::size_t m_size{0};
};

#endif //BITCLIENT_CONSTEXPRTYPES_HPP
