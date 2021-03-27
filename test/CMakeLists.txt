
add_executable(main main.cpp)

# fifo_map testcase' on/off
# crash testcase (default = off)
option(FIFO_MAP_TEST_OPTION "include nlohmann::fifo_map testcast" OFF)
if(FIFO_MAP_TEST_OPTION)
    add_definitions(-DTEST_FIFO_MAP)
endif()


#enable c++ exception
if(MSVC)
    add_compile_options(/EHsc)
endif()

#thread link lib
find_package(Threads REQUIRED)
target_link_libraries(main PRIVATE ${CMAKE_THREAD_LIBS_INIT})

target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(main PRIVATE thirdparty)