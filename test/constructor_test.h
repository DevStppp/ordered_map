#ifndef CONSTRUCTOR_TEST_H
#define CONSTRUCTOR_TEST_H
#include "ordered_map.h"
#include <catch.hpp>
#include <string>

TEST_CASE("constructor/destructor test", "[ordered_map]")
{
    using ordered_map = stppp::ordered_map<int32_t, std::string>;
    ordered_map org_map = {{1, "1"}, {2, "2"}, {3, "3"}};
    SECTION("default constructor")
    {
        ordered_map map;
        map.emplace_back(1, "1");
        map.emplace_back(2, "2");
        map.emplace_back(3, "3");
        REQUIRE(map.size() == 3);
    }
    SECTION("initlist constructor")
    {
        ordered_map map = {{1, "1"}, {2, "2"}, {3, "3"}};
        REQUIRE(map.size() == 3);
    }
    SECTION("insert duplicated key using constructor")
    {
        ordered_map map = {{1, "1"}, {1, "2"}, {3, "3"}};
        REQUIRE(map.size() == 2);
        auto iterator = map.begin();
        REQUIRE(iterator->first == 1);
        std::advance(iterator, 1);
        REQUIRE(iterator->first == 3);
    }
    SECTION("copy constructor")
    {
        ordered_map map(org_map);
        REQUIRE(map.size() == 3);
    }
    SECTION("move constructor")
    {
        REQUIRE_FALSE(org_map.empty());
        ordered_map map(std::move(org_map));
        REQUIRE(org_map.empty());
        REQUIRE(map.size() == 3);
    }
}  //TEST_CASE

#endif  //CONSTRUCTOR_TEST_H