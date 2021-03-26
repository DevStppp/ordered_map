#ifndef MULTI_THREAD_TEST_H
#define MULTI_THREAD_TEST_H
#include "ordered_map.h"
#include <catch.hpp>
#include <string>
#include <thread>

auto fMutiThreadSyncTest = []() {
    using ordered_map = stppp::ordered_map<int32_t, int32_t>;
    std::size_t spin_count = 3000;
    ordered_map map;

    std::thread producer([&]() {
        while (spin_count)
        {
            if (true == map.emplace_back(1, 1).second)
                spin_count--;
        }
    });

    std::thread consumer([&]() {
        while (spin_count)
        {
            if (map.contains(1) == true)
                map.erase(1);
        }
    });

    if (producer.joinable())
        producer.join();
    if (consumer.joinable())
        consumer.join();
};

TEST_CASE("ordered_map multi thread test", "[ordered_map]")
{
    REQUIRE_NOTHROW(fMutiThreadSyncTest());
}

#endif  //MULTI_THREAD_TEST_H