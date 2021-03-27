#ifndef FIFOMAP_SWAP_TEST_H
#define FIFOMAP_SWAP_TEST_H
#include "fifo_map.hpp"
#include <catch.hpp>
#include <string>

auto fFifo_Map_Swap = []() {
    using fifo_map = nlohmann::fifo_map<int32_t, std::string>;

    fifo_map swapped_map;
    //scope for delete org_map
    {
        fifo_map org_map = {{1, "1"}, {2, "2"}, {3, "3"}};
        REQUIRE(swapped_map.empty());
        REQUIRE_FALSE(org_map.empty());

        REQUIRE_NOTHROW(org_map.swap(swapped_map));

        REQUIRE_FALSE(swapped_map.empty());
        REQUIRE(org_map.empty());
    }
    //scope for delete org_map
    REQUIRE(swapped_map.size() == 3);
    REQUIRE_NOTHROW(swapped_map.emplace(1, "222"));
    REQUIRE(swapped_map.size() == 4);
};

auto fFifo_Map_STD_Swap = []() {
    using fifo_map = nlohmann::fifo_map<int32_t, std::string>;

    fifo_map swapped_map;
    //scope for delete org_map
    {
        fifo_map org_map = {{1, "1"}, {2, "2"}, {3, "3"}};
        REQUIRE(swapped_map.empty());
        REQUIRE_FALSE(org_map.empty());

        REQUIRE_NOTHROW(std::swap(org_map, swapped_map));

        REQUIRE_FALSE(swapped_map.empty());
        REQUIRE(org_map.empty());
    }
    //scope for delete org_map
    REQUIRE(swapped_map.size() == 3);
    REQUIRE_NOTHROW(swapped_map.emplace(1, "222"));
    REQUIRE(swapped_map.size() == 4);
};

TEST_CASE("fifo_map swap test", "[fifo_map]")
{
    SECTION("swap test")
    {
        REQUIRE_NOTHROW(fFifo_Map_Swap());
        REQUIRE_NOTHROW(fFifo_Map_STD_Swap());
    }
}  //TEST_CASE
#endif  // FIFOMAP_SWAP_TEST_H