
add_executable(main main.cpp)

#enable c++ exception
if(MSVC)
    add_compile_options(/EHsc)
endif()

#thread link lib
find_package(Threads REQUIRED)
target_link_libraries(main PRIVATE ${CMAKE_THREAD_LIBS_INIT})

target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(main PRIVATE thirdparty)