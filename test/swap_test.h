#ifndef SWAP_TEST_H
#define SWAP_TEST_H
#include "ordered_map.h"
#include <catch.hpp>
#include <string>

auto fOrdered_Map_Swap = []() {
    using ordered_map = stppp::ordered_map<int32_t, std::string>;

    ordered_map swapped_map;
    //scope for delete org_map
    {
        ordered_map org_map = {{1, "1"}, {2, "2"}, {3, "3"}};
        REQUIRE(swapped_map.empty());
        REQUIRE_FALSE(org_map.empty());

        REQUIRE_NOTHROW(org_map.swap(swapped_map));

        REQUIRE_FALSE(swapped_map.empty());
        REQUIRE(org_map.empty());
    }
    //scope for delete org_map

    REQUIRE(swapped_map.size() == 3);
    swapped_map.emplace_back(99, "99");
    REQUIRE(swapped_map.size() == 4);
};

auto fOrdered_Map_STD_Swap = []() {
    using ordered_map = stppp::ordered_map<int32_t, std::string>;

    ordered_map swapped_map;
    //scope for delete org_map
    {
        ordered_map org_map = {{1, "1"}, {2, "2"}, {3, "3"}};
        REQUIRE(swapped_map.empty());
        REQUIRE_FALSE(org_map.empty());

        REQUIRE_NOTHROW(std::swap(org_map, swapped_map));

        REQUIRE_FALSE(swapped_map.empty());
        REQUIRE(org_map.empty());
    }
    //scope for delete org_map

    REQUIRE(swapped_map.size() == 3);
    swapped_map.emplace_back(99, "99");
    REQUIRE(swapped_map.size() == 4);
};

auto fOrdered_Map_Copy = []() {
    using ordered_map = stppp::ordered_map<int32_t, std::string>;

    ordered_map copied_map;
    //scope for delete org_map
    {
        ordered_map org_map = {{1, "1"}, {2, "2"}, {3, "3"}};
        REQUIRE(copied_map.empty());
        REQUIRE_FALSE(org_map.empty());

        copied_map = org_map;

        REQUIRE_FALSE(copied_map.empty());
        REQUIRE_FALSE(org_map.empty());
    }
    //scope for delete org_map
    REQUIRE(copied_map.size() == 3);

    int32_t i = 1;
    for(auto iter : copied_map)
    {
        REQUIRE(iter.first == i++);
    }
};

TEST_CASE("ordered_map swap test", "[ordered_map]")
{
    SECTION("swap test")
    {
        REQUIRE_NOTHROW(fOrdered_Map_Swap());
        REQUIRE_NOTHROW(fOrdered_Map_STD_Swap());
    }
} //TEST_CASE

TEST_CASE("operator=", "[ordered_map]")
{
    SECTION("copy ordered_map")
    {
        REQUIRE_NOTHROW(fOrdered_Map_Copy());
    }
} //TEST_CASE
#endif  // SWAP_TEST_H