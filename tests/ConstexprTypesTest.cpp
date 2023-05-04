#include <gtest/gtest.h>

#include "parser/ConstexprTypes.hpp"

TEST(static_string, isConstexpr)
{
    constexpr static_string string("1234");
    static_assert(string.size() == 5);
    static_assert(*string.c_str() == '1');
    EXIT_SUCCESS;
}

TEST(static_vector, isConstexpr)
{
    constexpr static_vector<int> vec;
    EXIT_SUCCESS;
}


TEST(static_map, isConstexpr)
{
    constexpr static_map<static_string, int, 5> map;
    static_assert(map.size() == 0);
    EXIT_SUCCESS;
}
