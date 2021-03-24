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

TEST_CASE("ordered_map swap test")
{
    SECTION("swap test")
    {
        REQUIRE_NOTHROW(fOrdered_Map_Swap());
        REQUIRE_NOTHROW(fOrdered_Map_STD_Swap());
    }
}

#endif  // SWAP_TEST_H