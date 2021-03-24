#ifndef ITERATOR_TEST_H
#define ITERATOR_TEST_H
#include "ordered_map.h"
#include <catch.hpp>
#include <string>

TEST_CASE("iterator test", "[ordered_map]")
{
    using ordered_map = stppp::ordered_map<int32_t, std::string>;
    ordered_map org_map = {{1, "1"}, {2, "2"}, {3, "3"}};
    SECTION("range based for using iterator")
    {
        int32_t i = 0;
        for (auto iter : org_map)
        {
            REQUIRE(iter.first == ++i);
        }
    }
    SECTION("iterator")
    {
        ordered_map::iterator iter = org_map.begin();
        REQUIRE_FALSE(org_map.begin()->second == "99");
        iter->second = "99";
        REQUIRE(org_map.begin()->second == "99");
    }
    SECTION("const_iterator")
    {
        ordered_map::const_iterator iter = org_map.cbegin();
        REQUIRE(iter->first == 1);
        std::advance(iter, 2);
        REQUIRE(iter->first == 3);

        //const => build Error
        //iter->second = "99";
    }
    SECTION("reverse_iterator")
    {
        ordered_map::reverse_iterator iter = org_map.rbegin();
        REQUIRE(iter->first == 3);
        REQUIRE_FALSE(org_map.rbegin()->second == "99");
        iter->second = "99";
        REQUIRE(org_map.rbegin()->second == "99");
        std::advance(iter, 2);
        REQUIRE(iter->first == 1);
    }
    SECTION("const_reverse_iterator")
    {
        ordered_map::const_reverse_iterator iter = org_map.crbegin();
        REQUIRE(iter->first == 3);
        std::advance(iter, 2);
        REQUIRE(iter->first == 1);

        //const => build Error
        //iter->second = "99";
    }
}  //TEST_CASE

#endif  //ITERATOR_TEST_H