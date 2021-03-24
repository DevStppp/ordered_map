#ifndef LOOKUP_TEST_H
#define LOOKUP_TEST_H
#include "ordered_map.h"
#include <catch.hpp>
#include <string>

TEST_CASE("lookup test", "[ordered_map]")
{
    using ordered_map = stppp::ordered_map<int32_t, std::string>;
    ordered_map org_map = {{1, "1"}, {2, "2"}, {3, "3"}};

    SECTION("at(key)")
    {
        REQUIRE(org_map.at(2) == "2");
        REQUIRE_THROWS(org_map.at(4));
    }
    SECTION("const at(key)")
    {
        auto constTest = [](const ordered_map& map) {
            const std::string& result = map.at(1);
            REQUIRE(result == "1");
        };
        constTest(org_map);
    }
    SECTION("operator[key]")
    {
        REQUIRE(org_map[3] == "3");
        REQUIRE_NOTHROW(org_map[4] == "");
    }
    SECTION("count()")
    {
        REQUIRE(org_map.count(3) == 1);
        REQUIRE(org_map.count(4) == 0);
    }
    SECTION("find(key)")
    {
        REQUIRE(org_map.find(3)->second == "3");
        REQUIRE_NOTHROW(org_map.find(4) == org_map.end());
    }
    SECTION("contains()")
    {
        REQUIRE(org_map.contains(3));
        REQUIRE_FALSE(org_map.contains(5));
    }
}

TEST_CASE("capacity test", "[ordered_map]")
{
    using ordered_map = stppp::ordered_map<int32_t, std::string>;
    ordered_map size0;
    ordered_map size3 = {{1, "1"}, {2, "2"}, {3, "3"}};

    SECTION("empty()")
    {
        REQUIRE(size0.empty());
        REQUIRE_FALSE(size3.empty());
    }
    SECTION("size()")
    {
        REQUIRE(size0.size() == 0);
        REQUIRE(size3.size() == 3);
    }
    SECTION("max_size()")
    {
        REQUIRE_FALSE(size0.max_size() == 0);
    }
}

#endif  //LOOKUP_TEST_H