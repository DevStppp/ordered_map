#ifndef MODIFIER_TEST_H
#define MODIFIER_TEST_H
#include "ordered_map.h"
#include <catch.hpp>
#include <string>

//TODO : insert begin-end, initlist등 한꺼번에 여러개 넣는 거 result값 확인필요

TEST_CASE("modifier test", "[ordered_map]")
{
    using ordered_map = stppp::ordered_map<int32_t, std::string>;
    ordered_map org_map = {{1, "1"}, {2, "2"}, {3, "3"}};
    SECTION("clear test")
    {
        REQUIRE_FALSE(org_map.empty());
        REQUIRE_NOTHROW(org_map.clear());
        REQUIRE(org_map.empty());
    }
    SECTION("insert test")
    {
        auto target = org_map.begin();
        std::advance(target, 1);
        REQUIRE(target->first == 2);
        auto result = org_map.insert(target, {99, "99"});

        REQUIRE(result.first->first == 99);
        REQUIRE(result.second);
        REQUIRE((++result.first)->first == 2);
    }
    SECTION("push_back test")
    {
        REQUIRE_FALSE(org_map.rbegin()->first == 99);
        auto result = org_map.push_back({99, "99"});

        REQUIRE(result.first->first == 99);
        REQUIRE(result.first->second == "99");

        REQUIRE(result.second);
        REQUIRE(org_map.rbegin()->first == 99);
    }
    SECTION("push_front test")
    {
        REQUIRE_FALSE(org_map.begin()->first == 99);
        auto result = org_map.push_front({99, "99"});

        REQUIRE(result.first->first == 99);
        REQUIRE(result.first->second == "99");

        REQUIRE(result.second);
        REQUIRE(org_map.begin()->first == 99);
    }
    SECTION("emplace_front")
    {
        REQUIRE_FALSE(org_map.begin()->first == 99);
        auto result = org_map.emplace_front(99, "99");

        REQUIRE(result.first->first == 99);
        REQUIRE(result.first->second == "99");

        REQUIRE(result.second);
        REQUIRE(org_map.begin()->first == 99);
    }
    SECTION("emplace_back test")
    {
        REQUIRE_FALSE(org_map.rbegin()->first == 99);
        auto result = org_map.emplace_back(99, "99");

        REQUIRE(result.first->first == 99);
        REQUIRE(result.first->second == "99");

        REQUIRE(result.second);
        REQUIRE(org_map.rbegin()->first == 99);
    }
    SECTION("emplace test")
    {
        auto target = org_map.begin();
        std::advance(target, 1);
        REQUIRE(target->first == 2);
        auto result = org_map.emplace(target, 99, "99");

        REQUIRE(result.first->first == 99);
        REQUIRE(result.second);
        REQUIRE((++result.first)->first == 2);
    }
    SECTION("erase test")
    {
        //no exception
        ordered_map::iterator result;
        REQUIRE(org_map.begin()->first == 1);
        REQUIRE_NOTHROW(result = org_map.erase(org_map.begin()));
        REQUIRE_FALSE(org_map.begin()->first == 1);

        //throw Exception
        REQUIRE_THROWS_AS(org_map.erase(org_map.end()),std::out_of_range);
    }

    SECTION("erase using key")
    {
        //no exception
        constexpr int32_t TARGET_KEY = 2;
        REQUIRE(org_map.count(TARGET_KEY) == 1);
        REQUIRE_NOTHROW(org_map.erase(TARGET_KEY) == 1);
        REQUIRE(org_map.count(TARGET_KEY) == 0);

        //throw Exception
        REQUIRE_NOTHROW(org_map.erase(999) == 0);
    }
}

#endif  // MODIFIER_TEST_H