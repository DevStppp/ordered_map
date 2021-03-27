#ifndef FIFOMAP_MULTI_THREAD_TEST_H
#define FIFOMAP_MULTI_THREAD_TEST_H
#include "fifo_map.hpp"
#include <catch.hpp>
#include <string>
#include <thread>

auto fFifoMapMutiThreadSyncTest = []() {
    using fifo_map = nlohmann::fifo_map<int32_t, int32_t>;
    std::size_t spin_count = 3000;
    fifo_map map;

    std::thread producer([&]() {
        while (spin_count)
        {
            if (true == map.emplace(1, 1).second)
                spin_count--;
        }
    });

    std::thread consumer([&]() {
        while (spin_count)
        {
            if (map.find(1) != map.end())
                map.erase(1);
        }
    });

    if (producer.joinable())
        producer.join();
    if (consumer.joinable())
        consumer.join();
};

TEST_CASE("fifo_map multi thread test", "[fifo_map]")
{
    REQUIRE_NOTHROW(fFifoMapMutiThreadSyncTest());
}

#endif  //FIFOMAP_MULTI_THREAD_TEST_H